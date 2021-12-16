#include "plugin_utility.h"

#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *get_plugin_name(char *filename) {
  char *extension = strrchr(filename, '.');
  if (!extension || strcmp(extension, ".so") != 0)
    return NULL;
  return filename;
}

static void *load_plugin(char *plugin_name, char *path, manager_t *m) {
  // add "./" to plugin path
  char slashed_path[MAX_PATH_LEN];
  strcpy(slashed_path, "./");
  strcat(slashed_path, path);

  // open plugin
  void *fd = dlopen(slashed_path, RTLD_NOW);

  // error open plugin
  if (!fd) {
    fprintf(stderr, "[Error] cannot open dynamic library: %s\n", dlerror());
    return NULL;
  }

  // call initialize funtion "init_plugin_name"
  char init_fn_name[MAX_PATH_LEN];
  strcpy(init_fn_name, "init_");
  plugin_name[strlen(plugin_name) - 3] = 0;
  strcat(init_fn_name, plugin_name);
  reg_fn_t init_func = (reg_fn_t)dlsym(fd, init_fn_name);

  // error load initialize function
  if (!init_func) {
    fprintf(stderr, "[Error] cannot load initialize function: %s\n", dlerror());
    dlclose(fd);
    return NULL;
  }

  // error return value from initialize funciton
  int ret = init_func(m);
  if (ret < 0) {
    fprintf(stderr, "[Error] plugin initialize function returned: %d\n", ret);
    dlclose(fd);
    return NULL;
  }

  // success and return file descriptor
  fprintf(stderr, "[Success] load plugin from: '%s'\n", path);
  return fd;
}

void *discover_plugins(manager_t *m, char *dir_name) {
  // open directory
  DIR *dir = opendir(dir_name);

  // error open directory
  if (!dir) {
    fprintf(stderr, "[Error] cannot open directory: %s\n", dir_name);
    return NULL;
  }

  // initialize file desciptor list
  fd_list_t *fd_list = malloc(sizeof(fd_node_t));
  fd_list->head = NULL;

  // scan all files to load dynamic library
  struct dirent *dp;
  while ((dp = readdir(dir)) != NULL) {
    // get plugin name
    char *plugin_name = get_plugin_name(dp->d_name);
    if (!plugin_name)
      continue;

    // concatenate plugin name to directory name
    char full_path[MAX_PATH_LEN];
    strcpy(full_path, dir_name);
    strcat(full_path, "/");
    strcat(full_path, dp->d_name);

    // load plugin
    void *plugin_dl = load_plugin(plugin_name, full_path, m);
    if (plugin_dl) {
      // create node and connect to front
      fd_node_t *fd_node = malloc(sizeof(fd_node_t));
      fd_node->fd = plugin_dl;
      fd_node->next = fd_list->head;
      fd_list->head = fd_node;
    }
  }

  // close directory
  closedir(dir);

  // return fd_list if any plugin exists and loaded
  if (fd_list->head) {
    return (void *)fd_list;
  } else {
    free(fd_list);
    return NULL;
  }
}

void close_all_plugins(void *list) {
  fd_list_t *fd_list = (fd_list_t *)list;
  if (fd_list == NULL)
    return;
  fd_node_t *node_it = fd_list->head;
  while (node_it != NULL) {
    fd_node_t *node_tmp = node_it;
    dlclose(node_it->fd);
    node_it = node_it->next;
    free(node_tmp);
  }
  free(fd_list);
}
