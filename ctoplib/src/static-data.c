//
// Created by bernard on 23/05/2021.
//

#include <stdio.h>
#include <sys/param.h>
#include <sys/sysctl.h>

#include "static-data.h"

static_data *get_static_data(void) {
    static bool is_loaded = false;
    static static_data data;

    if (!is_loaded) {
        is_loaded = true;
        memset(&data, 0, sizeof(static_data));
        if (uname(&data.unames)) {
            memset(&data.unames, 0, sizeof(struct utsname));
            strcpy(data.unames.sysname, "ERROR!");
        } else {
#if defined(__linux__)
#define _WITH_NBPROCS
            data.nb_procs = get_nprocs();
            data.nb_procs_conf = get_nprocs_conf();
#elif defined(__NetBSD__)
#define _WITH_NBPROCS
            {
               int mib[2];
               size_t len;

               mib[0] = CTL_HW;
               mib[1] = HW_NCPU;
               len = sizeof(data.nb_procs);
               sysctl(mib, 2, &data.nb_procs, &len, NULL, 0);
               data.nb_procs_conf = data.nb_procs;
            }
#endif
#if defined(_WITH_NBPROCS)
            sprintf(data.str_processors, "%d/%d",
                    data.nb_procs,
                    data.nb_procs_conf);
#endif
#if defined(__linux__)
            sprintf(data.str_libc_version, "%s %s",
                    gnu_get_libc_release(),
                    gnu_get_libc_version());
#endif
        }
    }
    return &data;
}
