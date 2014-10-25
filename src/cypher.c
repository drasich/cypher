#include "cypher.h"
#include "drawable.h"
#include "gl.h"

void cypher_init()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_STENCIL_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepthf(1.0f);
  glClearStencil(0);

  if (!cb_call_init())  {
    printf("problem with init callback \n");
  }

}

void cypher_draw(int w, int h)
{
  glViewport(0, 0, w, h);

  glClearColor(0.2, 0.4, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (!cb_call_draw())  {
    printf("problem with draw callback \n");
  }

  glFinish();

}

void cypher_del()
{

}

void cypher_resize(int w, int h)
{
  // GL Viewport stuff. you can avoid doing this if viewport is all the
  // same as last frame if you want
  glViewport(0, 0, w, h);
  if (!resize_callback_call(w,h))  {
    printf("problem with resize callback \n");
  }
}
