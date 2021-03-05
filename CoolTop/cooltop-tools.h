//
// Created by bernard on 02/03/2021.
//

#include <nuklear.h>
#ifndef COOLTOP_COLTOP_TOOLS_H
#define COOLTOP_COLTOP_TOOLS_H

typedef struct {
  nk_bool show_app_about;
  nk_bool (*fill_me)(struct nk_context *ctx);
} sub_window_behavior;

nk_bool new_sub_window(struct nk_context *ctx,
                       const char* title,
                       struct nk_rect bounds,
                       sub_window_behavior *window_behavior);
extern sub_window_behavior unames_behavior;
extern sub_window_behavior memory_behavior;

#endif // COOLTOP_COLTOP_TOOLS_H
