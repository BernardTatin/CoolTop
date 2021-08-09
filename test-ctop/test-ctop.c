//
// Created by bernard on 23/05/2021.
//

#include <stdio.h>
#include "static-data.h"

int main(int argn, char *argv[]) {
    static_data *sdata = get_static_data();
    printf("System: %s\n",
           sdata->unames.sysname);
#if defined(_WITH_NBPROCESSORS)
    printf("Processors: %d/%d\n",
           sdata->nb_procs, sdata->nb_procs_conf);
#endif
    printf("Total RAM: %lu Mb, %lu Gb\n",
           sdata->total_ram/MEGAB, sdata->total_ram/GIGAB);
    printf("Total swap: %lu Mb, %lu Gb\n",
           sdata->total_swap/MEGAB, sdata->total_swap/GIGAB);
    return 0;
}
