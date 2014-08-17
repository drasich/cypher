#include "cypher.h"
#include "drawable.h"

void cypher_init()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_STENCIL_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepthf(1.0f);
  glClearStencil(0);

}

static void
_shader_request_handle()
{
  Eina_List* shader_requests = shader_request_get();

  Eina_List *l;
  ShaderRequest *sr;
  EINA_LIST_FOREACH(shader_requests, l, sr) {
    Shader* ss = shader_init_string(sr->vert, sr->frag, sr->att);
    shader_use(ss);
    sr->cb(sr->material, 55, ss);
  }

  EINA_LIST_FREE(shader_requests, sr){
   free(sr);
  }
  eina_list_free(shader_requests);
}

/*
static void
_buffer_request_handle()
{
  Eina_List* buffer_requests = buffer_request_get();

  Eina_List *l;
  BufferRequest* br;
  EINA_LIST_FOREACH(buffer_requests, l, br) {
    //printf("init shader : %s, %s \n", request->vert, request->frag);
    Buffer* bs = buffer_init(br->vertex, br->count);
    br->cb(br->mesh, 66, bs);
  }

  EINA_LIST_FREE(buffer_requests, br){
   free(br);
  }
  eina_list_free(buffer_requests);

}
*/


void cypher_draw(int w, int h)
{
  glViewport(0, 0, w, h);

  glClearColor(0.2, 0.4, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _shader_request_handle();
  //_buffer_request_handle();

  if (!draw_callback_call())  {
    const Drawable* dr = getZADATA();
    if (dr == NULL) return;
    else
     {
      shader_draw(dr->shader, dr->buffer);
      return;
     }
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
}
