//
// Created by bernard on 03/03/2021.
//

#ifndef COOLTOP_STATIC_SYSTEM_DATA_H
#define COOLTOP_STATIC_SYSTEM_DATA_H

typedef struct {
  struct utsname unames;
  char str_processors[64];
  char str_libc_version[64];
} static_data;

extern static_data global_static_data;

nk_bool load_unames(void);


#endif // COOLTOP_STATIC_SYSTEM_DATA_H
