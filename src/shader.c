#include "shader.h"

#define ERR(str,...) printf("ERROR : %s\n", str, ## __VA_ARGS__)

CglShader*
cgl_shader_init_string(const char* vert, const char* frag)
{
  CglShader* s = calloc(1, sizeof *s);
  //TODO factorize this by creating a function that get the shader id
  s->vert_shader = glCreateShader(GL_VERTEX_SHADER);
  if (s->vert_shader == 0) 
    ERR("there was en error creating the vertex shader.");

  s->frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  if (s->frag_shader == 0) 
    ERR("there was en error creating the fragment shader.");

  glShaderSource(s->vert_shader, 1, &vert, 0);
  glCompileShader(s->vert_shader);

  GLint status;
  GLint info_length;
  GLchar* message;

  glGetShaderiv(s->vert_shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    ERR("There was an error compiling the vertex shader");
    glGetShaderiv(s->vert_shader, GL_INFO_LOG_LENGTH, &info_length);
    message = malloc(info_length);
    glGetShaderInfoLog(s->vert_shader, info_length, 0, message);
    ERR("%s",message);
    free(message);
  }

  glShaderSource(s->frag_shader, 1, &frag, 0);
  glCompileShader(s->frag_shader);

  glGetShaderiv(s->frag_shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    ERR("There was an error compiling the fragment shader");
    glGetShaderiv(s->frag_shader, GL_INFO_LOG_LENGTH, &info_length);
    message = malloc(info_length);
    glGetShaderInfoLog(s->frag_shader, info_length, 0, message);
    ERR("message : %s", message);
    free(message);
  }

  s->program = glCreateProgram();
  glAttachShader(s->program, s->vert_shader);
  glAttachShader(s->program, s->frag_shader);
  glLinkProgram(s->program);

  glGetProgramiv(s->program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    ERR("There was an error in linking the program");
    glGetProgramiv(s->program, GL_INFO_LOG_LENGTH, &info_length);
    message = malloc(info_length);
    glGetProgramInfoLog(s->program, info_length, 0, message);
    ERR("%s",message);
    free(message);
  }

  return s;
}

CglShaderAttribute*
cgl_shader_attribute_new(CglShader *s, const char* name, uint size)
{
  GLint att_tmp = glGetAttribLocation(s->program, name);
  if (att_tmp == -1) {
    ERR("Error in getting attribute '%s' at line %d", name, __LINE__);
    return NULL;
  }
  else{
    CglShaderAttribute* cgl_att = calloc(1, sizeof *cgl_att);
    cgl_att->location = att_tmp;
    //TODO
    cgl_att->size = size;
    cgl_att->type = GL_FLOAT;

    return cgl_att;
  }
}

CglShaderUniform*
cgl_shader_uniform_new(CglShader *s, const char* name)
{
  GLint uni_tmp = glGetUniformLocation(s->program, name);
  if (uni_tmp == -1) {
    ERR("Error in getting uniform '%s' at line %d", name, __LINE__);
    return NULL;
  }
  else{
    CglShaderUniform* cgl_uni = calloc(1, sizeof *cgl_uni);
    cgl_uni->location = uni_tmp;
    return cgl_uni;
  }
}


void
cgl_shader_use(CglShader* s)
{
  glUseProgram(s->program);
}

void
cgl_shader_attribute_send(CglShaderAttribute* att,  CglBuffer* buf)
{
  glBindBuffer(buf->target, buf->id);
  glEnableVertexAttribArray(att->location);

  glVertexAttribPointer(
        att->location,
        att->size,
        att->type,
        GL_FALSE,
        0,//buf->stride, //TODO
        0);

}

void
cgl_draw()
{
  //TODO
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


void
cgl_shader_uniform_float_set(CglShaderUniform* uni, float f)
{
  glUniform1f(uni->location, f);
}

void
cgl_shader_uniform_vec4_set(CglShaderUniform* uni, float x, float y, float z, float w)
{
  glUniform4f(uni->location, x, y , z, w);
}


