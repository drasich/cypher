#ifndef __shader__
#define __shader__
#include "gl.h"
#include "buffer.h"


typedef struct _Shader Shader;

struct _Shader
{
  GLuint vert_shader;
  GLuint frag_shader;
  GLuint program;
  GLuint att_location;
};

typedef void (*rust_callback)(void*, int32_t, const Shader*);
//rust_callback cb;

Shader* shader_init_string(const char* vert, const char* frag, const char* att);

typedef struct _ShaderRequest ShaderRequest;
struct _ShaderRequest
{
  void* material;
  const char* vert;
  const char* frag;
  const char* att;
  rust_callback cb;
};

int shader_request_add(void* material, const char* vert, const char* frag, const char* att, rust_callback cb);
Eina_List* shader_request_get();
void shader_request_clean();

void shader_request_init();

void shader_use(Shader* s);
void shader_draw(Shader* s, Buffer* buf);


typedef struct _DrawRequest DrawRequest;
struct _DrawRequest
{
  Shader* shader;
  Buffer* buffer;
};

Eina_List* draw_equest_get();


#endif
