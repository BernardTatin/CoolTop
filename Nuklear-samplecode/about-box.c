//
// Created by bernard on 5/14/21.
//

#include "about-box.h"

void show_about_box(struct nk_context *ctx) {
    /* about popup */
    static struct nk_rect s = {20, 100, 300, 190};
    if (nk_popup_begin(ctx, NK_POPUP_STATIC, "About", NK_WINDOW_CLOSABLE,
                       s)) {
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Nuklear", NK_TEXT_LEFT);
        nk_label(ctx, "By Micha Mettke", NK_TEXT_LEFT);
        nk_label(ctx, "nuklear is licensed under the public domain License.",
                 NK_TEXT_LEFT);
        nk_popup_end(ctx);
    } else
        global_environment.app_states.show_popup = nk_false;
}

