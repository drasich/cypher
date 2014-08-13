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

typedef const void* (*rust_drawdata_callback)(void* data);

void draw_data_set(rust_drawdata_callback cb, void* data);

rust_drawdata_callback draw_data_get();
const void* getZADATA();

typedef struct _List CypherList;

struct _List
{
  void *data;
  CypherList* next;
};


#endif
