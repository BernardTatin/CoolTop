//
// Created by bernard on 02/03/2021.
//

#include <nuklear.h>
#ifndef COOLTOP_COLTOP_TOOLS_H
#define COOLTOP_COLTOP_TOOLS_H

nk_bool new_sub_window(struct nk_context *ctx,
                       const char* title,
                       struct nk_rect bounds,
                       nk_bool (fill_me)(struct nk_context *ctx) );
nk_bool fill_unames(struct nk_context *ctx);
nk_bool fill_memory(struct nk_context *ctx);

#endif // COOLTOP_COLTOP_TOOLS_H
