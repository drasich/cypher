#ifndef __buffer__
#define __buffer__
#include "gl.h"

typedef struct _Buffer Buffer;

struct _Buffer
{
  GLuint id;
  GLenum target;
};

typedef void (*rust_buffer_callback)(void*, int32_t, const Buffer*);

typedef struct _BufferRequest BufferRequest;
struct _BufferRequest
{
  const void* vertex;
  int count;
  void* mesh;
  rust_buffer_callback cb;
};

Buffer* buffer_init(const void* vertex, uint count);

int buffer_request_add(void* mesh, const void* vertex, int count, rust_buffer_callback cb);
Eina_List* buffer_request_get();

#endif
