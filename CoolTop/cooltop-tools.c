// ======================================================================
// cooltop-tools.c
// Created by bernard on 02/03/2021.
// ======================================================================
/*
MIT License

Copyright (c) 2021 Bernard Tatin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
// ======================================================================
// High level UI tools which can be moved to the library
// ======================================================================

#include "cooltop-common.h"

static nk_bool fill_unames(struct nk_context *ctx);
static nk_bool fill_memory(struct nk_context *ctx);

sub_window_behavior unames_behavior = {
    nk_false,
    fill_unames
};
sub_window_behavior memory_behavior = {
    nk_false,
    fill_memory
};

static void show_about_box(struct nk_context *ctx, sub_window_behavior *window_behavior) {
  /* about popup */
  static struct nk_rect s = {20, 100, 300, 190};
  if (nk_popup_begin(ctx, NK_POPUP_STATIC, "About", NK_WINDOW_CLOSABLE, s)) {
    nk_layout_row_dynamic(ctx, 20, 1);
    nk_label(ctx, "CoolTop", NK_TEXT_CENTERED);
    nk_label(ctx, "By Bernard Tatin", NK_TEXT_CENTERED);
    nk_label(ctx, "With love", NK_TEXT_CENTERED);
    nk_label(ctx, "and with nuklear", NK_TEXT_CENTERED);
    nk_label(ctx, "which is licensed under", NK_TEXT_CENTERED);
    nk_label(ctx, "the public domain License.", NK_TEXT_CENTERED);
    nk_popup_end(ctx);
  } else {
    window_behavior->show_app_about = nk_false;
    global_environment.app_states.show_app_about = nk_false;
  }
}

nk_bool new_sub_window(struct nk_context *ctx,
                       const char *title,
                       struct nk_rect bounds,
                       sub_window_behavior *window_behavior) {
  nk_bool result = nk_false;
  if (nk_begin(ctx, title, bounds,
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                   NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
    nk_menubar_begin(ctx);
    /* menu #1 */
    nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
    nk_layout_row_push(ctx, 45);
    if (nk_menu_begin_label(ctx, "MENU", NK_TEXT_LEFT, nk_vec2(120, 200))) {
      nk_layout_row_dynamic(ctx, 25, 1);
      if (nk_menu_item_label(ctx, "About", NK_TEXT_LEFT)) {
        if (!global_environment.app_states.show_app_about) {
          window_behavior->show_app_about = nk_true;
          global_environment.app_states.show_app_about = nk_true;
        }
      }
      if (nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT)) {
        global_environment.app_states.ready_to_exit = nk_true;
      }
      nk_menu_end(ctx);
    }
    nk_layout_row_end(ctx);
    nk_layout_row_dynamic(ctx, 20, 2);
    window_behavior->fill_me(ctx);
    result = nk_true;
  }
  if (window_behavior->show_app_about) {
    show_about_box(ctx, window_behavior);
  }
  nk_end(ctx);
  return result;
}
static nk_bool fill_unames(struct nk_context *ctx) {
  add_2_cols_label(ctx, "System name", global_static_data.unames.sysname, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Node name", global_static_data.unames.nodename, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Release", global_static_data.unames.release, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Version", global_static_data.unames.version, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Machine", global_static_data.unames.machine, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Processors avail/configured", global_static_data.str_processors,
                   NK_TEXT_RIGHT);
  add_2_cols_label(ctx, "Libc version", global_static_data.str_libc_version, NK_TEXT_RIGHT);
  return 0;
}
static nk_bool fill_memory(struct nk_context *ctx) {
  add_2_cols_label(ctx, "RAM: free/total",
                   global_dynamic_data.str_RAM, NK_TEXT_RIGHT);
  add_2_cols_label(ctx, "SWAP: free/total",
                   global_dynamic_data.str_SWAP, NK_TEXT_RIGHT);
  add_2_cols_label(ctx, "Shared memory",
                   global_dynamic_data.str_SHARED, NK_TEXT_RIGHT);
  add_2_cols_label(ctx, "Buffers",
                   global_dynamic_data.str_BUFFERS, NK_TEXT_RIGHT);
  return 0;
}
