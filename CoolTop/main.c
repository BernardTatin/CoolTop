/* nuklear - 1.32.0 - public domain */

#include "cooltop-common.h"

struct sysinfo info;
struct utsname unames;
/* =============================================================== */
void show_about_box(struct nk_context *ctx) {
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
    global_environment.show_app_about = nk_false;
  }
}

/* ===============================================================
 *
 *                          CoolTop
 *
 * ===============================================================*/
static void error_callback(int e, const char *d) {
  printf("Error %d: %s\n", e, d);
}

int main(void) {
  /* Platform */
  struct nk_glfw glfw = {0};
  static GLFWwindow *win;
  int width = 0, height = 0;
  struct nk_context *ctx;
  struct nk_colorf bg;

  init_environment(&global_environment);
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
  win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CoolTop", NULL, NULL);
  glfwMakeContextCurrent(win);
  glfwGetWindowSize(win, &width, &height);

  /* OpenGL */
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glewExperimental = 1;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to setup GLEW\n");
    exit(1);
  }

  ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);
  /* Load Fonts: if none of these are loaded a default font will be used  */
  /* Load Cursor: if you uncomment cursor loading please hide the cursor */
  {
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
#if defined(NUKEFONT) && defined(FONT_HEIGHT)
    struct nk_font *nukefont =
        nk_font_atlas_add_from_file(atlas, NUKEFONT, FONT_HEIGHT, 0);
#endif
    nk_glfw3_font_stash_end(&glfw);
#if defined(NUKEFONT)
    nk_style_set_font(ctx, &nukefont->handle);
#endif
  }

  bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
  while (!glfwWindowShouldClose(win) && !global_environment.ready_to_exit) {
    /* Input */
    // glfwPollEvents();
    static float last_t = 0.0;
    float current_time;

    glfwWaitEventsTimeout(global_environment.delta_t);
    current_time = glfwGetTime();
    if (current_time - last_t >= global_environment.delta_t) {
      if (uname(&unames)) {
        memset(&unames, 0, sizeof(struct utsname));
        strcpy(unames.sysname, "ERROR!");
      }
      if (sysinfo(&info) < 0) {
        memset(&info, 0, sizeof(struct sysinfo));
      }
      last_t = glfwGetTime();
    }
    nk_glfw3_new_frame(&glfw);
    /* GUI */
    new_sub_window(ctx, "Unames", nk_rect(5, 5, 430, 250), fill_unames);
    new_sub_window(ctx, "Memory", nk_rect(440, 5, 430, 250), fill_memory);

    /* ----------------------------------------- */

    /* Draw */
    glfwGetWindowSize(win, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg.r, bg.g, bg.b, bg.a);
    /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state
     * after rendering the UI. */
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER,
                    MAX_ELEMENT_BUFFER);
    glfwSwapBuffers(win);
  }
  nk_glfw3_shutdown(&glfw);
  glfwTerminate();
  return 0;
}
