//
// Created by bernard on 5/13/21.
//

#include "window_element.h"

void wrapped_draw_window(struct _Window *w,
                         struct nk_context *ctx) {
    if (nk_begin(ctx, w->title,
                 nk_rect(w->x, w->y, w->width, w->height),
                 w->window_flags)) {

        w->draw_window(w, ctx);
    }
    nk_end(ctx);
}
