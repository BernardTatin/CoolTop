//
// Created by bernard on 04/03/2021.
//

#ifndef COOLTOP_DYNAMIC_SYSTEM_DATA_H
#define COOLTOP_DYNAMIC_SYSTEM_DATA_H

typedef struct {
  struct sysinfo system_infos;
  char str_RAM[64];
  char str_SWAP[64];
  char str_SHARED[64];
  char str_BUFFERS[64];
} dynamic_data;

extern dynamic_data global_dynamic_data;
nk_bool load_dynamic_data();

#endif // COOLTOP_DYNAMIC_SYSTEM_DATA_H
