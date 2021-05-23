//
// Created by bernard on 5/13/21.
//

#ifndef COOLTOP_WINDOWS_LIST_H
#define COOLTOP_WINDOWS_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include "window_element.h"

typedef struct _WindowList {
    WindowElement *first;
    WindowElement *last;
} WindowList;

static inline WindowList *new_window_list(void) {
    WindowList *wlist = (WindowList *)calloc(1, sizeof(WindowList));
    wlist->first = NULL;
    wlist->last = NULL;
    return wlist;
}

void del_window_list(WindowList *wlist);
void draw_window_list(struct nk_context *ctx, WindowList *wlist);
void debug_window_list(WindowList *wlist);

static inline void push_window_list(WindowList *wlist, WindowElement *welement) {
    welement->next = wlist->first;
    wlist->first = welement;
    if (wlist->last == NULL) {
        wlist->last = welement;
    }
}

static inline void add_window_elt_list(WindowList *wlist, WindowElement *welement) {
    if (wlist->first != NULL) {
        wlist->last->next = welement;
        wlist->last = welement;
        welement->next = NULL;
    } else {
        wlist->first = welement;
        wlist->last = welement;
    }
}

static inline void add_window_list(WindowList *wlist, Window *w) {
    add_window_elt_list(wlist, new_window_element(w));
}

#endif //COOLTOP_WINDOWS_LIST_H
