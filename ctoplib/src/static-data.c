//
// Created by bernard on 23/05/2021.
//

#include <stdio.h>
#include <sys/param.h>

#include "static-data.h"

static_data *get_static_data(void) {
    static bool is_loaded = false;
    static static_data data;

    if (!is_loaded) {
        is_loaded = true;
        memset(&data, 0, sizeof(static_data));
#if defined(__linux__)
        struct sysinfo system_infos;
        if (sysinfo(&system_infos) < 0) {
            memset(&system_infos, 0, sizeof(struct sysinfo));
        }
        data.total_ram = system_infos.totalram;
        data.total_swap = system_infos.totalswap;
#elif defined(__NetBSD__)
		{
			int total_ram;

			get_sysctl_int(CTL_HW, HW_PHYSMEM, &total_ram);
			data.total_ram = total_ram;
		}
#endif
        if (uname(&data.unames)) {
            memset(&data.unames, 0, sizeof(struct utsname));
            strcpy(data.unames.sysname, "ERROR!");
        } else {
#if defined(__linux__)
            data.nb_procs = get_nprocs();
            data.nb_procs_conf = get_nprocs_conf();
#elif defined(__NetBSD__)
//             {
//                int mib[2];
//                size_t len;
//
//                mib[0] = CTL_HW;
//                mib[1] = HW_NCPU;
//                len = sizeof(data.nb_procs);
//                sysctl(mib, 2, &data.nb_procs, &len, NULL, 0);
//                data.nb_procs_conf = data.nb_procs;
//             }
             get_sysctl_int(CTL_HW, HW_NCPU, &data.nb_procs);
             get_sysctl_int(CTL_HW, HW_NCPUONLINE, &data.nb_procs_conf);
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
