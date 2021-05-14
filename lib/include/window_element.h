//
// Created by bernard on 5/13/21.
//

#ifndef COOLTOP_WINDOW_ELEMENT_H
#define COOLTOP_WINDOW_ELEMENT_H

#include <stdlib.h>
#include <nuklear.h>

typedef void (*DrawWindow)(struct nk_context *ctx);

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
    DrawWindow draw_window;

} Window;

typedef struct _WindowElement {
    Window *window;
    struct _WindowElement *next;
} WindowElement;

static inline Window *new_window(DrawWindow draw_window) {
    Window *we = (Window *)calloc(1, sizeof(Window));
    we->draw_window = draw_window;
    return we;
}
static inline WindowElement *new_window_element(Window *window) {
    WindowElement *we = (WindowElement *)calloc(1, sizeof(WindowElement));
    we->window = window;
    return we;
}
#endif //COOLTOP_WINDOW_ELEMENT_H
