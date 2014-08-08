#ifndef __buffer__
#define __buffer__
#include "gl.h"

typedef struct _Buffer Buffer;

struct _Buffer
{
  GLuint id;
  GLenum target;
};

typedef struct _BufferRequest BufferRequest;
struct _BufferRequest
{
  const void* vertex;
  int count;
};

Buffer* buffer_init(const void* vertex, int count);

typedef void (*rust_mesh_callback)(void* mesh, int32_t, const Buffer*);

int buffer_request_add(void* mesh, const void* vertex, int count, rust_mesh_callback cb);
Eina_List* buffer_request_get();

#endif
