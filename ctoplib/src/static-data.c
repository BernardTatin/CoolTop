//
// Created by bernard on 23/05/2021.
//

#include "static-data.h"

static_data *get_static_data(void) {
    static bool is_loaded = false;
    static static_data data;

    if (!is_loaded) {
        is_loaded = true;
        if (uname(&data.unames)) {
            memset(&data.unames, 0, sizeof(struct utsname));
            strcpy(data.unames.sysname, "ERROR!");
        } else {
            sprintf(data.str_processors, "%d/%d", get_nprocs(), get_nprocs_conf());
            sprintf(data.str_libc_version, "%s %s", gnu_get_libc_release(), gnu_get_libc_version());
        }
    }
    return &data;
}
