//
// Created by bernard on 03/03/2021.
//

#include "cooltop-common.h"

static_data global_static_data;

nk_bool load_unames(void) {
  if (uname(&global_static_data.unames)) {
    memset(&global_static_data.unames, 0, sizeof(struct utsname));
    strcpy(global_static_data.unames.sysname, "ERROR!");
    return nk_false;
  }
  sprintf(global_static_data.str_processors, "%d/%d", get_nprocs(), get_nprocs_conf());
  sprintf(global_static_data.str_libc_version, "%s %s", gnu_get_libc_release(), gnu_get_libc_version());
  return nk_true;
}
