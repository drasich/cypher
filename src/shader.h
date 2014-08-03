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

Shader* shader_init_string(const char* vert, const char* frag, const char* att);

typedef struct _ShaderRequest ShaderRequest;
struct _ShaderRequest
{
  const char* vert;
  const char* frag;
  const char* att;
};

int shader_request_add(const char* vert, const char* frag, const char* att);
Eina_List* shader_request_get();
void shader_request_clean();

void shader_request_init();

void shader_use(Shader* s);
void shader_draw(Shader* s, Buffer* buf);

#endif
