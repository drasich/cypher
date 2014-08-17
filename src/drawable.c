#include "drawable.h"

static rust_draw_callback _draw_callback_cb = 0;
static void* _draw_callback_data = 0;

void draw_callback_set(rust_draw_callback cb, void* data)
{
  _draw_callback_cb = cb;
  _draw_callback_data = data;
}

bool draw_callback_call()
{
  if (_draw_callback_cb && _draw_callback_data) {
    _draw_callback_cb(_draw_callback_data);
    return true;
  }

  return false;
}

