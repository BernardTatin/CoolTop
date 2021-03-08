// ======================================================================
// environment.h
// Created by bernard on 28/02/2021.
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
// Global environment management.
// ======================================================================

#ifndef COOLTOP_ENVIRONNEMENT_H
#define COOLTOP_ENVIRONNEMENT_H


#if !defined(WINDOW_WIDTH )
#define WINDOW_WIDTH 1200
#endif
#if !defined(WINDOW_HEIGHT )
#define WINDOW_HEIGHT 800
#endif

#if !defined(MAX_VERTEX_BUFFER )
#define MAX_VERTEX_BUFFER 512 * 1024
#endif
#if !defined(MAX_ELEMENT_BUFFER )
#define MAX_ELEMENT_BUFFER 128 * 1024
#endif

typedef struct {
  // delay between 2 events reads
  float delta_t;
  // main window title
  char *title;
  // global font and size
  char *font_name;
  float font_size;
  // background color
  struct nk_colorf bg;

} AppConfiguration;

typedef struct {
  // global init done
  int init_done;
  // when we are ready o exit
  int ready_to_exit;
  // the about popup is on
  // NOTE: must be extended to every popup?
  int show_app_about;
} AppStates;

typedef struct {
  struct nk_glfw glfw;
  GLFWwindow *win;
} GLFwStates;

typedef struct {
  int width;
  int height;
  struct nk_context *ctx;
  struct nk_colorf bg;
} NuklearStates;

typedef struct {
  AppConfiguration app_configuration;
  AppStates app_states;
  GLFwStates glfw_states;
  NuklearStates nuklear_states;
} GlobalEnvironment;

extern GlobalEnvironment global_environment;
void init_environment(GlobalEnvironment *env,
                      char *title,
                      char *font_name);

nk_bool init_application(GlobalEnvironment *env);
void draw_and_render(GlobalEnvironment *env);
void application_terminate(GlobalEnvironment *env);

#endif // COOLTOP_ENVIRONNEMENT_H
