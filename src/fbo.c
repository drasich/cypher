#include "fbo.h"
#include "log.h"

CglFbo* 
cgl_create_fbo()
{
  CglFbo* f = calloc(1, sizeof *f);

  glGenTextures(1, &f->texture_depth_stencil_id);
  glBindTexture(GL_TEXTURE_2D, f->texture_depth_stencil_id);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  //TODO texture resolution
  int width = 1200;
  int height = 400;
  /*
  glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT,
        width,
        height,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        NULL);
        */
  glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_STENCIL_OES,
        width,
        height,
        0,
        GL_DEPTH_STENCIL_OES,
        GL_UNSIGNED_INT_24_8_OES,
        NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

  glGenTextures(1, &f->texture_color);
  glBindTexture(GL_TEXTURE_2D, f->texture_color);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB, //GL_DEPTH_STENCIL_OES,
        GL_UNSIGNED_SHORT_5_6_5, //GL_UNSIGNED_INT_24_8_OES,
        NULL);

	glBindTexture(GL_TEXTURE_2D, 0);


  glGenRenderbuffers(1, &f->rb);
  glBindRenderbuffer(GL_RENDERBUFFER, f->rb);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
  //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glGenFramebuffers(1, &f->fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, f->fbo);

  glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        f->texture_depth_stencil_id,
        0);

  glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        f->texture_depth_stencil_id,
        0);

  glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        f->texture_color,
        0);

  /*
  glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, 
        GL_COLOR_ATTACHMENT0,
        GL_RENDERBUFFER,
        f->rb);
        */


  GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (e == GL_FRAMEBUFFER_COMPLETE) {
    printf("---->>>>>buffer complete\n");
  }
  else
    printf("---->>>>>buffer NOOOOOOOOOOOOOOOT complete\n");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return f;
}

void 
cgl_fbo_use(CglFbo* f)
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, f->fbo);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) ;
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 0x1, 0x1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  //TODO clear..
}

void
cgl_fbo_use_end()
{
  glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void
cgl_fbo_resize(CglFbo* f, int w, int h)
{
	glBindTexture(GL_TEXTURE_2D, f->texture_depth_stencil_id);

  glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_STENCIL_OES,
        w,
        h,
        0,
        GL_DEPTH_STENCIL_OES,
        GL_UNSIGNED_INT_24_8_OES,
        NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, f->texture_color);
  glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        w,
        h,
        0,
        GL_RGB,
        GL_UNSIGNED_SHORT_5_6_5,
        NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, f->rb);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, w, h);
  //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, w, h);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void
cgl_fbo_destroy(CglFbo* s)
{
  //TODO

}

