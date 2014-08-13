#include "drawable.h"

static rust_drawdata_callback _draw_data_cb = NULL;
static void* _draw_data = NULL;

void draw_data_set(rust_drawdata_callback cb, void* data)
{
  _draw_data_cb = cb;
  _draw_data = data;
}

rust_drawdata_callback draw_data_get()
{

}

const void* getZADATA()
{
  if (_draw_data_cb == NULL) return NULL;
  if (_draw_data == NULL) return NULL;

  return _draw_data_cb(_draw_data);
}

