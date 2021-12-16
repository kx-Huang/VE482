#include "plugin.h"

zathura_error_t txt_document_open(zathura_document_t *document) {
  txt_document_t *txt_document = g_malloc0(sizeof(txt_document_t));
  const char *path = zathura_document_get_path(document);
  FILE *fin = fopen(path, "r");
  txt_document->pages = (txt_page_t *)malloc(sizeof(txt_page_t));
  txt_document->pages[0].data = malloc(BUFFER_SIZE * sizeof(char *));
  char buffer[BUFFER_SIZE + 1];
  fgets(buffer, BUFFER_SIZE, fin);
  txt_document->pages[0].data[0] = strdup(buffer);
  fclose(fin);
  zathura_document_set_number_of_pages(document, 1);
  zathura_document_set_data(document, txt_document);
  return ZATHURA_ERROR_OK;
}

zathura_error_t txt_document_free(zathura_document_t *document,
                                  void *txt_document) {
  if (document == NULL)
    return ZATHURA_ERROR_UNKNOWN;
  free(((txt_document_t *)txt_document)->pages);
  g_free(txt_document);
  return ZATHURA_ERROR_OK;
}

zathura_error_t txt_page_init(zathura_page_t *page) {
  zathura_document_t *document = zathura_page_get_document(page);
  if (document == NULL)
    return ZATHURA_ERROR_UNKNOWN;
  txt_document_t *txt_document = zathura_document_get_data(document);
  zathura_page_set_width(page, 500);
  zathura_page_set_height(page, 600);
  zathura_page_set_data(page, txt_document->pages);
  return ZATHURA_ERROR_OK;
}

zathura_error_t txt_page_clear(zathura_page_t *page, void *txt_page) {
  zathura_document_t *document = zathura_page_get_document(page);
  if (document == NULL)
    return ZATHURA_ERROR_UNKNOWN;
  free(((txt_page_t *)txt_page)->data);
  return ZATHURA_ERROR_OK;
}
