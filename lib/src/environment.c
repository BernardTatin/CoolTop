// ======================================================================
// environment.c
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

#include <string.h>
#include <stdio.h>
#include "common.h"
#include "environment.h"

GlobalEnvironment global_environment;

static void on_glfw_error(const int line ) {
    const char *description = NULL;
    int code = glfwGetError(&description);

    if (code != GLFW_NO_ERROR) {
        fprintf(stderr, "Line %4d - FATAL GLFW ERROR %d: %s\n",
                line, code, description);
        exit(1);
    }
}

static void error_callback(int e, const char *d) {
  fprintf(stderr, "Error %d: %s\n", e, d);
}

void init_environment(GlobalEnvironment *env,
                      char *title,
                      char *font_name) {
  if (!env->app_states.init_done) {
    memset(env, 0, sizeof(GlobalEnvironment));
    env->app_configuration.delta_t = 0.0f;
    if (title != NULL) {
      env->app_configuration.title = strdup(title);
    }
    if (font_name != NULL) {
      env->app_configuration.font_name = strdup (font_name);
    }
    env->app_configuration.font_size = 14;
    env->app_states.init_done = nk_true;
  }
}

nk_bool init_application(GlobalEnvironment *env) {
  DBG();
  glfwSetErrorCallback(error_callback);
  DBG();
  if (glfwInit() != GLFW_TRUE) {
    fprintf(stdout, "[GFLW] failed to init!\n");
    on_glfw_error(__LINE__);
    exit(1);
  }
  DBG();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  on_glfw_error(__LINE__);
  DBG();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  on_glfw_error(__LINE__);
  DBG();
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  on_glfw_error(__LINE__);
  DBG();

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  env->glfw_states.win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "CoolTop", NULL,
                               NULL);
  if (env->glfw_states.win == NULL) {
      on_glfw_error(__LINE__);
  }
  DBG();
  glfwMakeContextCurrent(env->glfw_states.win);
  DBG();
  glfwGetWindowSize(env->glfw_states.win,
                    &env->nuklear_states.width,
                    &env->nuklear_states.height);

  /* OpenGL */
  DBG();
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  DBG();
  glewExperimental = 0;
  DBG();
  {
      GLenum err = glewInit();
      if (err != 0) {
          fprintf(stderr, "Failed to setup GLEW: %d %s\n",
                  (int)err,
                  glewGetErrorString(err));
          exit(1);
      }
  }
  DBG();
  env->nuklear_states.ctx = nk_glfw3_init(&env->glfw_states.glfw, env->glfw_states.win,
                                          NK_GLFW3_INSTALL_CALLBACKS);
  DBG();

  /* Load Fonts: if none of these are loaded a default font will be used  */
  /* Load Cursor: if you uncomment cursor loading please hide the cursor */
  {
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&env->glfw_states.glfw, &atlas);
#if defined(NUKEFONT) && defined(FONT_HEIGHT)
    struct nk_font *nukefont =
        nk_font_atlas_add_from_file(atlas, NUKEFONT, FONT_HEIGHT, 0);
#endif
    nk_glfw3_font_stash_end(&env->glfw_states.glfw);
#if defined(NUKEFONT)
    nk_style_set_font(env->nuklear_states.ctx, &nukefont->handle);
#endif
  }
  DBG();
  return nk_true;
}
void draw_and_render(GlobalEnvironment *env) {
  /* Draw */
  glfwGetWindowSize(env->glfw_states.win, &env->nuklear_states.width, &env->nuklear_states.height);
  glViewport(0, 0, env->nuklear_states.width, env->nuklear_states.height);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(env->app_configuration.bg.r, env->app_configuration.bg.g, env->app_configuration.bg.b,
               env->app_configuration.bg.a);
  /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
   * with blending, scissor, face culling, depth test and viewport and
   * defaults everything back into a default state.
   * Make sure to either a.) save and restore or b.) reset your own state
   * after rendering the UI. */
  nk_glfw3_render(&env->glfw_states.glfw, NK_ANTI_ALIASING_ON,
                  MAX_VERTEX_BUFFER,
                  MAX_ELEMENT_BUFFER);
  glfwSwapBuffers(env->glfw_states.win);
}
void application_terminate(GlobalEnvironment *env) {
  nk_glfw3_shutdown(&env->glfw_states.glfw);
  glfwTerminate();
}
