//
// Created by bernard on 02/03/2021.
//
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <gnu/libc-version.h>


#include "common.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include "coltop-tools.h"
#include "environment.h"
#include "nuke-tools.h"

extern struct sysinfo info;
extern struct utsname unames;

nk_bool new_sub_window(struct nk_context *ctx,
                       const char *title,
                       struct nk_rect bounds,
                       nk_bool (*fill_me)(struct nk_context *)) {
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
      if (nk_menu_item_label(ctx, "About", NK_TEXT_LEFT))
        global_environment.show_app_about = nk_true;
      if (nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT))
        global_environment.ready_to_exit = nk_true;
      nk_menu_end(ctx);
    }
    nk_layout_row_end(ctx);
    nk_layout_row_dynamic(ctx, 20, 2);
//    nk_layout_row_begin(ctx, NK_DYNAMIC, 20, 2);
//    nk_layout_row_push(ctx, 0.75f);
    fill_me(ctx);
    result = nk_true;
  }
  if (global_environment.show_app_about) {
    show_about_box(ctx);
  }
  nk_end(ctx);
  return result;
}
nk_bool fill_unames(struct nk_context *ctx) {
  static char str_buffer[64];
  add_2_cols_label(ctx, "System name", unames.sysname, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Node name", unames.nodename, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Release", unames.release, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Version", unames.version, NK_TEXT_LEFT);
  add_2_cols_label(ctx, "Machine", unames.machine, NK_TEXT_LEFT);
  sprintf(str_buffer, "%d/%d", get_nprocs(), get_nprocs_conf());
  add_2_cols_label(ctx, "Processors avail/configured", str_buffer,
                   NK_TEXT_RIGHT);
  sprintf(str_buffer, "%s %s", gnu_get_libc_release(), gnu_get_libc_version());
  add_2_cols_label(ctx, "Libc version", str_buffer, NK_TEXT_RIGHT);

  return 0;
}
nk_bool fill_memory(struct nk_context *ctx) {
  static char str_buffer[64];
  sprintf(str_buffer, "%lu/%lu", info.freeram/(1024*1024),
          info.totalram/(1024*1024));
  add_2_cols_label(ctx, "RAM: free/total", str_buffer, NK_TEXT_RIGHT);
  sprintf(str_buffer, "%lu/%lu", info.freeswap/MEGA_BYTES,
          info.totalswap/MEGA_BYTES);
  add_2_cols_label(ctx, "SWAP: free/total", str_buffer, NK_TEXT_RIGHT);
  sprintf(str_buffer, "%lu", info.sharedram/MEGA_BYTES);
  add_2_cols_label(ctx, "Shared memory", str_buffer, NK_TEXT_RIGHT);
  sprintf(str_buffer, "%lu", info.bufferram/MEGA_BYTES);
  add_2_cols_label(ctx, "Buffers", str_buffer, NK_TEXT_RIGHT);
  return 0;
}
