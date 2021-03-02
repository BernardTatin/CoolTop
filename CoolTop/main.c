/* nuklear - 1.32.0 - public domain */

#include <sys/utsname.h>
#include <sys/sysinfo.h>

#include "common.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include "environment.h"
#include "nuke-tools.h"

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
    static struct sysinfo info;
    static struct utsname unames;
    static char str_buffer[64];
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
        memset(&info, 0, sizeof (struct sysinfo));
      }
      last_t = glfwGetTime();
    }
    nk_glfw3_new_frame(&glfw);

    /* GUI */
    if (nk_begin(ctx, "CoolTop: unames", nk_rect(5, 5, 430, 250),
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
      nk_layout_row_dynamic(ctx, 20, 2);
      add_2_cols_label(ctx, "System name", unames.sysname, NK_TEXT_LEFT);
      add_2_cols_label(ctx, "Node name", unames.nodename, NK_TEXT_LEFT);
      add_2_cols_label(ctx, "Release", unames.release, NK_TEXT_LEFT);
      add_2_cols_label(ctx, "Version", unames.version, NK_TEXT_LEFT);
      add_2_cols_label(ctx, "Machine", unames.machine, NK_TEXT_LEFT);
      sprintf(str_buffer, "%ul/%ul", info.freeram/(1024*1024),
                                                                     info
                                                                      .totalram/(1024*1024));
      add_2_cols_label(ctx, "RAM: free/total", str_buffer, NK_TEXT_RIGHT);

      if (global_environment.show_app_about) {
        show_about_box(ctx);
      }
    }
    nk_end(ctx);

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
