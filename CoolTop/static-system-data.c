// ======================================================================
// static-system-data.c
// Created by bernard on 03/03/2021.
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
// Load the static system data (OS name, OS version, ...)
// ======================================================================

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
