//
// Created by bernard on 28/02/2021.
//

#include "common.h"
#include "environment.h"

environment global_environment;

void init_environment(environment *env) {
  if (!env->init_done) {
    env->ready_to_exit = nk_false;
    env->show_app_about = nk_false;
    env->init_done = nk_true;
  }
}
