//
// Created by bernard on 5/13/21.
//

#include "windows_list.h"

void del_window_list(WindowList *wlist) {

}

void draw_window_list(struct nk_context *ctx, WindowList *wlist) {
    WindowElement *welt = wlist->first;

    while (welt != NULL) {
        Window *w = welt->window;
        w->draw_window(ctx);
        welt = welt->next;
    }
}

void debug_window_list(WindowList *wlist) {
    WindowElement *welt = wlist->first;

    fprintf(stdout, "---------------------------------------------\n");
    while (welt != NULL) {
        Window *w = welt->window;
        fprintf(stdout, "debug of %s\n", w->title);
        welt = welt->next;
    }
    fprintf(stdout, "=============================================\n");
}
