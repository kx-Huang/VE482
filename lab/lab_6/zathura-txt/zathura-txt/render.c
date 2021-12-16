#include "plugin.h"

zathura_error_t txt_page_render_cairo(zathura_page_t *page, void *txt_page,
                                      cairo_t *cairo, bool UNUSED(printing)) {
  if (page == NULL || cairo == NULL)
    return ZATHURA_ERROR_INVALID_ARGUMENTS;
  zathura_document_t *document = zathura_page_get_document(page);
  if (document == NULL)
    return ZATHURA_ERROR_UNKNOWN;
  cairo_move_to(cairo, 50, 60);
  cairo_show_text(cairo, ((txt_page_t *)txt_page)->data[0]);
  return ZATHURA_ERROR_OK;
}
