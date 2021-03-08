/* nuklear - 1.32.0 - public domain */

#include "cooltop-common.h"
#include "environment.h"

/* =============================================================== */
/* ===============================================================
 *
 *                          CoolTop
 *
 * ===============================================================*/
int main(void) {
  /* Platform */
  static float last_t = 0.0f;
  float current_time;


  init_environment(&global_environment,
                   "Cooltop",
                   NULL);
  init_application(&global_environment);

  global_environment.app_configuration.bg.r = 0.10f;
  global_environment.app_configuration.bg.g = 0.18f;
  global_environment.app_configuration.bg.b = 0.24f;
  global_environment.app_configuration.bg.a = 1.0f;
  load_unames();
  load_dynamic_data();
  last_t = glfwGetTime();
  while (!glfwWindowShouldClose(global_environment.glfw_states.win) &&
         !global_environment.app_states.ready_to_exit) {
    glfwWaitEventsTimeout(global_environment.app_configuration.delta_t);
    current_time = glfwGetTime();
    if (current_time - last_t >= global_environment.app_configuration.delta_t) {
      load_dynamic_data();
      last_t = glfwGetTime();
    }
    nk_glfw3_new_frame(&global_environment.glfw_states.glfw);
    /* GUI */
    new_sub_window(global_environment.nuklear_states.ctx,
                   "Unames",
                   nk_rect (5, 5, 430, 250),
                   &unames_behavior);
    new_sub_window(global_environment.nuklear_states.ctx,
                   "Memory",
                   nk_rect(440, 5, 430, 250),
                   &memory_behavior);

    /* ----------------------------------------- */
    draw_and_render(&global_environment);
  }
  application_terminate(&global_environment);
  return 0;
}
