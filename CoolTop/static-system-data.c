//
// Created by bernard on 03/03/2021.
//

#include "cooltop-common.h"

struct utsname unames;
char str_processors[64];
char str_libc_version[64];

nk_bool load_unames(void) {
  if (uname(&unames)) {
    memset(&unames, 0, sizeof(struct utsname));
    strcpy(unames.sysname, "ERROR!");
    return nk_false;
  }
  sprintf(str_processors, "%d/%d", get_nprocs(), get_nprocs_conf());
  sprintf(str_libc_version, "%s %s", gnu_get_libc_release(), gnu_get_libc_version());
  return nk_true;
}
