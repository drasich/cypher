#include "shader.h"
#include "log.h"

CglShader*
cgl_shader_init_string(const char* vert, const char* frag)
{
  CglShader* s = calloc(1, sizeof *s);
  //TODO factorize this by creating a function that get the shader id
  s->vert_shader = glCreateShader(GL_VERTEX_SHADER);
  if (s->vert_shader == 0) 
    ERR("there was en error creating this vertex shader :\n%s\n", vert);

  s->frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  if (s->frag_shader == 0) 
    ERR("there was en error creating this fragment shader :\n%s\n", frag);

  glShaderSource(s->vert_shader, 1, &vert, 0);
  glCompileShader(s->vert_shader);

  GLint status;
  GLint info_length;
  GLchar* message;

  glGetShaderiv(s->vert_shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    ERR("There was an error compiling this vertex shader :\n%s\n", vert);
    glGetShaderiv(s->vert_shader, GL_INFO_LOG_LENGTH, &info_length);
    message = malloc(info_length);
    glGetShaderInfoLog(s->vert_shader, info_length, 0, message);
    ERR("Message was : '%s'",message);
    free(message);
  }

  glShaderSource(s->frag_shader, 1, &frag, 0);
  glCompileShader(s->frag_shader);

  glGetShaderiv(s->frag_shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    ERR("There was an error compiling this fragment shader:\n%s\n", frag);
    glGetShaderiv(s->frag_shader, GL_INFO_LOG_LENGTH, &info_length);
    message = malloc(info_length);
    glGetShaderInfoLog(s->frag_shader, info_length, 0, message);
    ERR("Message was : '%s'",message);
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
    printf("cypher: TODO attributes check type \n");
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
cgl_draw(uint vertex_count)
{
  //TODO
  glDrawArrays(GL_TRIANGLES, 0, vertex_count );
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
cgl_draw_lines(uint vertex_count)
{
  //TODO
  //printf("lines %d\n", vertex_count);
  glDrawArrays(GL_LINES, 0, vertex_count );
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void
cgl_draw_faces(const CglBuffer* buffer, uint index_count)
{
  //TODO
  glBindBuffer(buffer->target, buffer->id);
  glDrawElements(
        GL_TRIANGLES, 
        index_count,
        GL_UNSIGNED_INT,
        0);

  glBindBuffer(buffer->target, 0);
}

void
cgl_draw_end()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
cgl_shader_uniform_int_set(CglShaderUniform* uni, int i)
{
  glUniform1i(uni->location, i);
}

void
cgl_shader_uniform_float_set(CglShaderUniform* uni, float f)
{
  glUniform1f(uni->location, f);
}

void
cgl_shader_uniform_vec2_set(CglShaderUniform* uni, float x, float y)
{
  glUniform2f(uni->location, x, y);
}

void
cgl_shader_uniform_vec3_set(CglShaderUniform* uni, float x, float y, float z)
{
  glUniform3f(uni->location, x, y , z);
}

void
cgl_shader_uniform_vec4_set(CglShaderUniform* uni, float x, float y, float z, float w)
{
  glUniform4f(uni->location, x, y , z, w);
}

void
cgl_shader_uniform_mat4_set(CglShaderUniform* uni, const float* matrix)
{
  glUniformMatrix4fv(uni->location, 1, GL_FALSE, matrix);
}

void
cgl_shader_uniform_texture_set(CglShaderUniform* uni, const CglTexture* texture, uint i)
{
  glUniform1i(uni->location, i);
  glActiveTexture(GL_TEXTURE0 + i);
  glBindTexture(GL_TEXTURE_2D, texture->id);
}

void
cgl_shader_uniform_fbo_depth_set(CglShaderUniform* uni, const CglFbo* fbo, uint i)
{
  glUniform1i(uni->location, i);
  glActiveTexture(GL_TEXTURE0 + i);
  glBindTexture(GL_TEXTURE_2D, fbo->texture_depth_stencil_id);
  //printf("uniform fbo send  id %d, index %d \n", fbo->texture_depth_stencil_id, i);
}

void
cgl_shader_uniform_fbo_color_set(CglShaderUniform* uni, const CglFbo* fbo, uint i)
{
  glUniform1i(uni->location, i);
  glActiveTexture(GL_TEXTURE0 + i);
  glBindTexture(GL_TEXTURE_2D, fbo->texture_color);
  //printf("uniform fbo send  id %d, index %d \n", fbo->texture_depth_stencil_id, i);
}

void 
cgl_shader_uniforms_init(CglShader* s, uniform_set_cb cb, void* data)
{
  GLint num_uniforms;
  glGetProgramiv(s->program, GL_ACTIVE_UNIFORMS, &num_uniforms);
  GLchar uniform_name[256];
  GLsizei length;
  GLint size;
  GLenum type;
  for (int i = 0; i < num_uniforms; i++){
    glGetActiveUniform(s->program, i, sizeof(uniform_name), &length, &size, &type, uniform_name);

    CglShaderUniform* uni = cgl_shader_uniform_new(s, uniform_name);
    cb(data, uniform_name, uni);
   }
}

void 
cgl_shader_attributes_init(CglShader* s, attribute_set_cb cb, void* data)
{
  GLint num_attributes;
  glGetProgramiv(s->program, GL_ACTIVE_ATTRIBUTES, &num_attributes);
  GLchar attribute_name[256];
  GLsizei length;
  GLint size;
  GLenum type;
  for (int i = 0; i < num_attributes; i++) {
    glGetActiveAttrib(s->program, i, sizeof(attribute_name), &length, &size, &type, attribute_name);

    printf("cypher: TODO attributes check size \n");
    if (type == GL_FLOAT_VEC2){
      size *= 2;
    }
    else if (type == GL_FLOAT_VEC3){
      size *= 3;
    }
    else if (type == GL_FLOAT_VEC4){
      size *= 4;
    }

    CglShaderAttribute* att = cgl_shader_attribute_new(s, attribute_name, size);
    cb(data, attribute_name, att);
   }
}







