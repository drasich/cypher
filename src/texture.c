#include "texture.h"

CglTexture*
cgl_texture_init(const void* data, int internal_format, int width, int height)
{

  CglTexture* t = calloc(1, sizeof *t);

  GLuint idtex;
  glGenTextures(1, &idtex);
  t->id = idtex;

	glBindTexture(GL_TEXTURE_2D, idtex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(
        GL_TEXTURE_2D,
        0,
        //GL_RGBA, //4,
        internal_format,
        width,
        height,
        0,
        GL_RGBA, //TODO tex->format,
        GL_UNSIGNED_BYTE,
        data);


  /*
  void glTexImage2D(	GLenum target,
 	GLint level,
 	GLint internalFormat,
 	GLsizei width,
 	GLsizei height,
 	GLint border,
 	GLenum format,
 	GLenum type,
 	const GLvoid * data);
  */

  return t;
}
