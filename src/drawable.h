#ifndef __drawable__
#define __drawable__
#include "buffer.h"
#include "shader.h"

typedef struct _Drawable Drawable;

struct _Drawable
{
  Shader* shader;
  Buffer* buffer;
};

typedef const void* (*rust_drawdata_callback)();

void draw_data_set(rust_drawdata_callback cb);

rust_drawdata_callback draw_data_get();

#endif
