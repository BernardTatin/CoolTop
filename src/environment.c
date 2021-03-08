//
// Created by bernard on 28/02/2021.
//

#include <string.h>
#include "common.h"
#include "environment.h"

GlobalEnvironment global_environment;

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
  /* GLFW */
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    fprintf(stdout, "[GFLW] failed to init!\n");
    exit(1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  env->glfw_states.win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "CoolTop", NULL,
                               NULL);
  glfwMakeContextCurrent(env->glfw_states.win);
  glfwGetWindowSize(env->glfw_states.win,
                    &env->nuklear_states.width,
                    &env->nuklear_states.height);

  /* OpenGL */
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glewExperimental = 1;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to setup GLEW\n");
    exit(1);
  }
  env->nuklear_states.ctx = nk_glfw3_init(&env->glfw_states.glfw, env->glfw_states.win,
                                          NK_GLFW3_INSTALL_CALLBACKS);

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
