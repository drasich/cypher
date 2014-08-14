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

static rust_draw_callback _draw_callback_cb = NULL;
static void* _draw_callback_data = NULL;

void draw_callback_set(rust_draw_callback cb, void* data)
{
  _draw_callback_cb = cb;
  _draw_callback_data = data;
}

bool draw_callback_call()
{
  printf("c : %s \n", __FUNCTION__);
  if (_draw_callback_cb && _draw_callback_data) {
    printf("c : %s, There is data and cb \n", __FUNCTION__);
    _draw_callback_cb(_draw_callback_data);
    return true;
  }

  return false;
}

