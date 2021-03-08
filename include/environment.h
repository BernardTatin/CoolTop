//
// Created by bernard on 28/02/2021.
//

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
  // backgroud color
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
