#include "cypher.h"
#include "gl.h"

void cypher_init(rust_callback cb_init, void* data)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_STENCIL_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepthf(1.0f);
  glClearStencil(0);

  if (cb_init && data) {
    cb_init(data);
  }
}

void cypher_draw(rust_callback cb_draw, void* data, int w, int h)
{
  glViewport(0, 0, w, h);

  glClearColor(0.2, 0.4, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (cb_draw && data) {
    cb_draw(data);
  }

  glFinish();

}

void cypher_del()
{

}

void cypher_resize(resize_callback cb_resize, void* data, int w, int h)
{
  // GL Viewport stuff. you can avoid doing this if viewport is all the
  // same as last frame if you want
  glViewport(0, 0, w, h);

  if (cb_resize && data) {
    cb_resize(data, w, h);
  }
}

void cgl_clear()
{
  glClear(GL_DEPTH_BUFFER_BIT);
}
