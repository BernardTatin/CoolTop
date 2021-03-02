//
// Created by bernard on 02/03/2021.
//

#include "common.h"

void add_2_cols_label(struct nk_context *ctx, char *name, char *value,
                      nk_flags value_alignment) {
  nk_label(ctx, name, NK_TEXT_LEFT);
  nk_label(ctx, value, value_alignment);
}
