#ifndef __buffer__
#define __buffer__
#include "gl.h"

typedef struct _CglBuffer CglBuffer;

struct _CglBuffer
{
  GLuint id;
  GLenum target;
};

CglBuffer* cgl_buffer_init(const void* vertex, uint count);

#endif
