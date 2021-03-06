#ifndef __buffer__
#define __buffer__
#include "gl.h"

typedef struct _CglBuffer CglBuffer;

struct _CglBuffer
{
  GLuint id;
  GLenum target;
};

CglBuffer* cgl_buffer_init(const void* data, uint count);
void cgl_buffer_update(CglBuffer* b, const void* data, uint count);
CglBuffer* cgl_buffer_index_init(const void* data, uint count);

#endif
