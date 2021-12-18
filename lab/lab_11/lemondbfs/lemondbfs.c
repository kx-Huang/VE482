/*
*
* Author: Mr. Frown
* Creation date: 2020.12.23
*
*/

#define FUSE_USE_VERSION 26

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fuse/fuse.h>

#define LM_DATA ((struct lemondb_state *) fuse_get_context()->private_data)

// FUSE function implementations.
static int lemonDBfs_getattr(const char *path, struct stat *stbuf)
{
	char path[PATH_MAX] = {0};
}

static int lemonDBfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	printf("readdir(\"%s\"\n", path);
	(void) offset;
	(void) fi;

	// root
	if (strcmp(path, "/") == 0) {
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		for (int i = 0;i < LM_DATA->num_tbl;++i)
			filler(buf, LM_DATA->table_name[i], NULL, 0);
		return 0;
	}

	// dir for each table
	char tmp_path[PATH_MAX] = {0};
	for (int i = 0;i < LM_DATA->num_tbl;++i) {
		strcpy(tmp_path, "/");
		strcat(tmp_path, LM_DATA->table_name[i]); // tmp_path := /mtable0 (directory)
		if (strcmp(path, tmp_path) == 0) {
			filler(buf, ".", NULL, 0);
			filler(buf, "..", NULL, 0);
			filler(buf, "orig.tbl", NULL, 0);
			filler(buf, ".query", NULL, 0);
			if (LM_DATA->M_bit[i])
				filler(buf, "res.tbl", NULL, 0);
			return 0;
		}
	}

	fprintf(stderr, "no match path for readdir(%s)", path);
	return -1;
}


static int lemonDBfs_open(const char *path, struct fuse_file_info *fi)
{

}

static int lemonDBfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	(void) fi;

}

int lemonDBfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	(void) fi;

}

static int lemonDBfs_flush(const char *path, struct fuse_file_info *fi)
{
	printf("flush(\"%s\"\n", path);
	return 0;
}

static int lemonDBfs_truncate(const char *path, off_t newsize)
{
	printf("truncate(\"%s\"\n", path);
	return 0;
}

static void lemonDBfs_destroy(void *userdata)
{
	printf("lemonDBfs destroy!\n");
	char dpath[PATH_MAX];
	for (int i = 0;i < LM_DATA->num_tbl;++i) {
		if (LM_DATA->M_bit[i]) {
			char tmp_path[PATH_MAX] = {0};
			strcpy(tmp_path, "/");
			strcat(tmp_path, LM_DATA->table_name[i]); // tmp_path := /mtable0 (directory)
			db_fullpath(dpath, tmp_path); // dpath := *db_dir*/mtable0
			strcat(dpath, "_dump.tbl"); // dpath := *db_dir*/mtable0_dump.tbl

			if (access(dpath, F_OK) != -1) remove(dpath);
		}
	}
}


static struct fuse_operations lemonDBfs_oper = {
	.init = lemonDBfs_init,
	.getattr = lemonDBfs_getattr,
	.readdir = lemonDBfs_readdir,
	.open = lemonDBfs_open,
	.read = lemonDBfs_read,
	.write = lemonDBfs_write,
	.flush = lemonDBfs_flush,
	.truncate = lemonDBfs_truncate,
	.destroy = lemonDBfs_destroy,
};

int main(int argc, char **argv)
{
	return fuse_main(argc, argv, &lemonDBfs_oper, NULL);
}

