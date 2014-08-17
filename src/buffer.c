#include "buffer.h"

CglBuffer*
cgl_buffer_init(const void* vertex, uint count)
{
  CglBuffer* b = calloc(1, sizeof *b);
  b->target = GL_ARRAY_BUFFER;

  glGenBuffers(1, &b->id);
  glBindBuffer(b->target, b->id);
  glBufferData(
        b->target,
        //b->size,
        count * sizeof(GLfloat), //TODO size of f32
        vertex,
        GL_DYNAMIC_DRAW);

  return b;
}

