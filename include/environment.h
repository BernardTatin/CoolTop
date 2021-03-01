//
// Created by bernard on 28/02/2021.
//

#ifndef COOLTOP_ENVIRONNEMENT_H
#define COOLTOP_ENVIRONNEMENT_H

typedef struct {
  int init_done;
  int ready_to_exit;
  int show_app_about;
  float delta_t;
} environment;

extern environment global_environment;
void init_environment(environment *env);

#endif // COOLTOP_ENVIRONNEMENT_H
