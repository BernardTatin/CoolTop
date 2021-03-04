//
// Created by bernard on 04/03/2021.
//

#include "cooltop-common.h"

dynamic_data global_dynamic_data;

nk_bool load_dynamic_data() {
  if (sysinfo(&global_dynamic_data.system_infos) < 0) {
    memset(&global_dynamic_data.system_infos, 0, sizeof(struct sysinfo));
    return nk_false;
  }
  sprintf(global_dynamic_data.str_RAM,
          "%lu/%lu",
          global_dynamic_data.system_infos.freeram/MEGA_BYTES,
          global_dynamic_data.system_infos.totalram/MEGA_BYTES);
  sprintf(global_dynamic_data.str_SWAP,
          "%lu/%lu",
          global_dynamic_data.system_infos.freeswap/MEGA_BYTES,
          global_dynamic_data.system_infos.totalswap/MEGA_BYTES);
  sprintf(global_dynamic_data.str_SHARED,
          "%lu",
          global_dynamic_data.system_infos.sharedram/MEGA_BYTES);
  sprintf(global_dynamic_data.str_BUFFERS,
          "%lu",
          global_dynamic_data.system_infos.bufferram/MEGA_BYTES);
  return nk_true;
}
