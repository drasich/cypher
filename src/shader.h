#ifndef __shader__
#define __shader__
#include "gl.h"
#include "buffer.h"

typedef struct _CglShaderAttribute CglShaderAttribute;

struct _CglShaderAttribute
{
  GLuint location;
  GLint size;
  GLenum type;
};

typedef struct _CglShaderUniform CglShaderUniform;
struct _CglShaderUniform{
  GLuint location;
  //UniformType type;
};

typedef struct _CglShader CglShader;

struct _CglShader
{
  GLuint vert_shader;
  GLuint frag_shader;
  GLuint program;
  GLuint att_location;
};

CglShader* shader_init_string(const char* vert, const char* frag, const char* att);

void shader_use(CglShader* s);
void shader_draw(CglShader* s, CglBuffer* buf);

#endif
