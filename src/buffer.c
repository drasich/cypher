#include "buffer.h"
#include <pthread.h>

Buffer*
buffer_init(const void* vertex, int count)
{
  Buffer* b = calloc(1, sizeof *b);
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


static Eina_List* _buffer_requests = NULL;
static pthread_mutex_t lock;

int
//buffer_request_add(const void* vertex, int count)
buffer_request_add(void* mesh, const void* vertex, int count, rust_mesh_callback cb)
{
  BufferRequest* br = calloc(1, sizeof *br);
  br->vertex = vertex;
  br->count = count;

  pthread_mutex_lock(&lock);
  _buffer_requests = eina_list_append(_buffer_requests, br);
  pthread_mutex_unlock(&lock);
}

Eina_List* buffer_request_get()
{
  pthread_mutex_lock(&lock);
  Eina_List* clone = eina_list_clone(_buffer_requests);
  eina_list_free(_buffer_requests);
  _buffer_requests = NULL;
  pthread_mutex_unlock(&lock);
  return clone;
}
