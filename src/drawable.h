#ifndef __drawable__
#define __drawable__
#include "stdbool.h"

typedef void (*rust_callback)(void* data);
typedef void (*resize_callback)(void* data, int w, int h);

void draw_callback_set(rust_callback draw, resize_callback resize, void* data);
bool draw_callback_call();

bool resize_callback_call(int w, int h);


#endif
