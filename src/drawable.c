#include "drawable.h"

static rust_drawdata_callback _draw_data_cb = NULL;

void draw_data_set(rust_drawdata_callback cb)
{
  _draw_data_cb = cb;
}

rust_drawdata_callback draw_data_get()
{

}
