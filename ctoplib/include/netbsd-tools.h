//
// Created by bernard on 23/05/2021.
//

#if !defined(COOLTOP_NETBSD_TOOLS_H)
#define COOLTOP_NETBSD_TOOLS_H

#include <sys/sysctl.h>

#define _WITH_NBPROCS

static inline int get_sysctl_int(int mib0, int mib1, int *value) {
       int mib[2];
       size_t len;

       mib[0] = mib0;
       mib[1] = mib1;
       len = sizeof(sizeof(int));
       return sysctl(mib, 2, value, &len, NULL, 0);
}
#endif // COOLTOP_NETBSD_TOOLS_H


