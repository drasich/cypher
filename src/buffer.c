#include "buffer.h"
#include "log.h"

CglBuffer*
cgl_buffer_init(const void* data, uint count)
{
  CglBuffer* b = calloc(1, sizeof *b);
  b->target = GL_ARRAY_BUFFER;

  glGenBuffers(1, &b->id);
  glBindBuffer(b->target, b->id);
  glBufferData(
        b->target,
        //b->size,
        count * sizeof(GLfloat), //TODO size of f32
        data,
        GL_DYNAMIC_DRAW);

  return b;
}

CglBuffer*
cgl_buffer_index_init(const void* data, uint count)
{
  CglBuffer* b = calloc(1, sizeof *b);
  b->target = GL_ELEMENT_ARRAY_BUFFER;

  glGenBuffers(1, &b->id);
  glBindBuffer(b->target, b->id);
  glBufferData(
        b->target,
        //b->size,
        count * sizeof(GLuint), //TODO TODO TODO
        data,
        GL_DYNAMIC_DRAW);

  return b;
}

void
cgl_buffer_update(CglBuffer* b, const void* data, uint count)
{
  glBindBuffer(b->target, b->id);
  glBufferSubData(
        b->target,
        0,
        //b->size,
        count * sizeof(GLfloat), //TODO size of f32
        data);
}

