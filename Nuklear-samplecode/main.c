// ======================================================================
// main.c
// Created by bernard on 08/03/2021
/* using nuklear version 1.32.0 - public domain */
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

#include "common.h"
#include "windows_list.h"
#include "nuke_sample.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 640

#if !defined(MAX_VERTEX_BUFFER )
#define MAX_VERTEX_BUFFER (512 * 1024)
#endif
#if !defined(MAX_ELEMENT_BUFFER )
#define MAX_ELEMENT_BUFFER (128 * 1024)
#endif

#include "environment.h"

/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the defines */


/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
void first_window_proc(Window *w, struct nk_context *ctx) {
    enum { EASY, HARD };
    static int op = EASY;
    static int property = 20;
    nk_layout_row_static(ctx, 30, 80, 1);
    if (nk_button_label(ctx, "button"))
        fprintf(stdout, "button pressed\n");

    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_option_label(ctx, "easy", op == EASY))
        op = EASY;
    if (nk_option_label(ctx, "hard", op == HARD))
        op = HARD;

    nk_layout_row_dynamic(ctx, 25, 1);
    nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

    nk_layout_row_dynamic(ctx, 20, 1);
    nk_label(ctx, "background:", NK_TEXT_LEFT);
    nk_layout_row_dynamic(ctx, 25, 1);
    if (nk_combo_begin_color(ctx, nk_rgb_cf(global_environment.app_configuration.bg),
                             nk_vec2(nk_widget_width(ctx), 400))) {
        nk_layout_row_dynamic(ctx, 120, 1);
        global_environment.app_configuration.bg = nk_color_picker(ctx, global_environment.app_configuration.bg, NK_RGBA);
        nk_layout_row_dynamic(ctx, 25, 1);
        global_environment.app_configuration.bg.r = nk_propertyf(ctx, "#R:", 0, global_environment.app_configuration.bg.r, 1.0f, 0.01f, 0.005f);
        global_environment.app_configuration.bg.g = nk_propertyf(ctx, "#G:", 0, global_environment.app_configuration.bg.g, 1.0f, 0.01f, 0.005f);
        global_environment.app_configuration.bg.b = nk_propertyf(ctx, "#B:", 0, global_environment.app_configuration.bg.b, 1.0f, 0.01f, 0.005f);
        global_environment.app_configuration.bg.a = nk_propertyf(ctx, "#A:", 0, global_environment.app_configuration.bg.a, 1.0f, 0.01f, 0.005f);
        nk_combo_end(ctx);
    }
}

static WindowList *demo_list(void) {
    WindowList *list = new_window_list();

    add_window_list(list, &first_window);
    add_window_list(list, &calculator_window);
    add_window_list(list, &overview_window);
    add_window_list(list, &node_editor_window);
    return list;
}

int main(void) {
    WindowList *wlist = demo_list();
  init_environment(&global_environment,
                   "Nuklear demo",
                   NULL);
  init_application(&global_environment);

  global_environment.app_configuration.bg.r = 0.10f;
  global_environment.app_configuration.bg.g = 0.18f;
  global_environment.app_configuration.bg.b = 0.24f;
  global_environment.app_configuration.bg.a = 1.0f;

  set_style(global_environment.nuklear_states.ctx, THEME_WHITE);
  set_style(global_environment.nuklear_states.ctx, THEME_RED);

  while (!glfwWindowShouldClose(global_environment.glfw_states.win) &&
         !global_environment.app_states.ready_to_exit) {
    /* Input */
     glfwPollEvents();
//    glfwWaitEventsTimeout(3.0);
    nk_glfw3_new_frame(&global_environment.glfw_states.glfw);

    /* GUI */
      {
          struct nk_context *ctx = global_environment.nuklear_states.ctx;

          draw_window_list(ctx, wlist);
      }
    /* ----------------------------------------- */
    draw_and_render(&global_environment);
  }
  application_terminate(&global_environment);
  return 0;
}
