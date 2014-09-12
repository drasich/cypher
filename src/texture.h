#ifndef __texture__
#define __texture__
#include "gl.h"

typedef struct _CglTexture CglTexture;

struct _CglTexture
{
  GLuint id;
};

CglTexture* cgl_texture_init(const void* data, int internal_format, int width, int height);

#endif
