//
// Created by bernard on 5/13/21.
//

#ifndef COOLTOP_WINDOW_ELEMENT_H
#define COOLTOP_WINDOW_ELEMENT_H

#include <stdlib.h>
#include <nuklear.h>

typedef struct _Window {
    // can we show the window?
    nk_bool enabled;
    // is it closed ?
    nk_bool closed;
    // title, NULL if no title
    char *title;
    // position
    int x, y;
    // dimensions
    int width, height;
    // function which draw the window
    void (*draw_window)(struct _Window *w,
                        struct nk_context *ctx);

} Window;

typedef struct _WindowElement {
    Window *window;
    struct _WindowElement *next;
} WindowElement;

static inline Window *new_window(void (*draw_window)(struct _Window *w,
                                                     struct nk_context *ctx)) {
    Window *w = (Window *)calloc(1, sizeof(Window));
    w->draw_window = draw_window;
    w->enabled = nk_true;
    w->closed = nk_false;
    return w;
}
static inline WindowElement *new_window_element(Window *window) {
    WindowElement *we = (WindowElement *)calloc(1, sizeof(WindowElement));
    we->window = window;
    return we;
}
#endif //COOLTOP_WINDOW_ELEMENT_H
