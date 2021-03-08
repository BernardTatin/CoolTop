// ======================================================================
// dynamic-system-data.c
// Created by bernard on 02/03/2021.
// ======================================================================
/*
MIT License

Copyright (c) 2021 Bernard Tatin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
// ======================================================================
// Load the dynamic system data (RAM usage, CPU load, ...)
// ======================================================================

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
