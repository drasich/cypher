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

typedef enum _CglUniformType CglUniformType;
enum _CglUniformType {
  CGL_UNIFORM_UNKNOWN,
  CGL_UNIFORM_TEXTURE,
  CGL_UNIFORM_INT,
  CGL_UNIFORM_FLOAT,
  CGL_UNIFORM_VEC2,
  CGL_UNIFORM_VEC3,
  CGL_UNIFORM_VEC4,
  CGL_UNIFORM_MAT3,
  CGL_UNIFORM_MAT4
};


typedef struct _CglShader CglShader;

struct _CglShader
{
  GLuint vert_shader;
  GLuint frag_shader;
  GLuint program;
  //GLuint att_location; //TODO remove
};

CglShader* shader_init_string(const char* vert, const char* frag);

void shader_use(CglShader* s);


CglShaderAttribute* cgl_shader_attribute_get(CglShader *s, const char* name, uint size);

void cgl_shader_attribute_send(CglShaderAttribute* att,  CglBuffer* buf);
void cgl_draw();

#endif
