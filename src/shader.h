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

void shader_use(Shader* s);
void shader_draw(Shader* s, CglBuffer* buf);

#endif
