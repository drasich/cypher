#include "drawable.h"
#include "stdio.h"

static rust_callback _init_callback_cb = 0;
static rust_callback _draw_callback_cb = 0;
static void* _draw_callback_data = 0;

static resize_callback _resize_callback_cb = 0;

void draw_callback_set(
      rust_callback init,
      rust_callback draw,
      resize_callback resize,
      void* data)
{
  _init_callback_cb = init;
  _draw_callback_cb = draw;
  _draw_callback_data = data;

  _resize_callback_cb = resize;
}

bool cb_call_init()
{
  printf("init callback call\n");
  if (_init_callback_cb && _draw_callback_data) {
    printf("init callback call there is data\n");
    _init_callback_cb(_draw_callback_data);
    return true;
  }

  printf("init callback call end\n");

  return false;
}


//bool draw_callback_call()
bool cb_call_draw()
{
  if (_draw_callback_cb && _draw_callback_data) {
    _draw_callback_cb(_draw_callback_data);
    return true;
  }

  return false;
}

bool resize_callback_call(int w, int h)
{
  if (_resize_callback_cb && _draw_callback_data) {
    _resize_callback_cb(_draw_callback_data, w, h);
    return true;
  }

  return false;
}

