#ifndef __drawable__
#define __drawable__
#include "buffer.h"
#include "shader.h"
#include "stdbool.h"

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

typedef void (*rust_draw_callback)(void* data);

void draw_callback_set(rust_draw_callback cb, void* data);
bool draw_callback_call();


#endif
