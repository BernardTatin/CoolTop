//
// Created by bernard on 03/03/2021.
//

#include "cooltop-common.h"

struct utsname unames;

nk_bool load_unames(void) {
  if (uname(&unames)) {
    memset(&unames, 0, sizeof(struct utsname));
    strcpy(unames.sysname, "ERROR!");
    return nk_false;
  }
  return nk_true;
}
