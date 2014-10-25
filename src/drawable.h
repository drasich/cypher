#ifndef __drawable__
#define __drawable__
#include "stdbool.h"

typedef void (*rust_callback)(void* data);
typedef void (*resize_callback)(void* data, int w, int h);

void draw_callback_set(
      rust_callback init,
      rust_callback draw,
      resize_callback resize,
      void* data);
bool cb_call_draw();
bool cb_call_init();

bool resize_callback_call(int w, int h);


#endif
