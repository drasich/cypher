#include "shader.h"

#define ERR(str,...) printf("ERROR : %s\n", str, ## __VA_ARGS__)

CglShader*
cgl_shader_init_string(const char* vert, const char* frag, const char* att)
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

  GLint att_tmp = glGetAttribLocation(s->program, att);
  s->att_location = att_tmp;
  if (att_tmp == -1) {
    ERR("Error in getting attribute '%s' at line %d", att, __LINE__);
  }

  return s;
}

void
cgl_shader_use(CglShader* s)
{
  glUseProgram(s->program);
}

void
cgl_shader_draw(CglShader* ss, CglBuffer* buf)
{
  glBindBuffer(buf->target, buf->id);
  glEnableVertexAttribArray(ss->att_location);

  glVertexAttribPointer(
        ss->att_location,
        2,
        GL_FLOAT, //att->type,
        GL_FALSE,
        0,//buf->stride,
        0);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}


