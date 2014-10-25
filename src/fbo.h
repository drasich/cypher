#ifndef __fbo__
#define __fbo__
#include "gl.h"

typedef struct _CglFbo CglFbo;

struct _CglFbo {
  GLuint texture_depth_stencil_id;
  GLuint texture_color;
  GLuint fbo;
  GLuint rb;
};

CglFbo* cgl_create_fbo();
void cgl_fbo_use(CglFbo* fbo);
void cgl_fbo_use_end();
void cgl_fbo_resize(CglFbo* f, int w, int h);
void cgl_fbo_destroy(CglFbo* s);

#endif
