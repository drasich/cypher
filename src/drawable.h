#ifndef __drawable__
#define __drawable__
#include "stdbool.h"

typedef void (*rust_draw_callback)(void* data);

void draw_callback_set(rust_draw_callback cb, void* data);
bool draw_callback_call();


#endif
