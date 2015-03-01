#ifndef __cypher__
#define __cypher__

typedef void (*rust_callback)(void* data);
typedef void (*resize_callback)(void* data, int w, int h);

void cypher_init(rust_callback cb_init, void* data);
void cypher_draw(rust_callback cb_draw, void* data, int w, int h);
void cypher_del();
void cypher_resize(resize_callback cb_resize, void* data, int w, int h);

void cgl_clear();

#endif
