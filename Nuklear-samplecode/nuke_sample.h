//
// Created by bernard on 5/14/21.
//

#ifndef COOLTOP_NUKE_SAMPLE_H
#define COOLTOP_NUKE_SAMPLE_H

#include "window_element.h"

extern Window calculator_window;
extern Window node_editor_window;
extern Window first_window;
extern Window overview_window;

void set_style(struct nk_context *ctx, enum theme theme);
void calculator(Window *w, struct nk_context *ctx);
void overview(Window *w, struct nk_context *ctx);
void node_editor(Window *w, struct nk_context *ctx);
void first_window_proc(Window *w, struct nk_context *ctx);

#endif //COOLTOP_NUKE_SAMPLE_H
