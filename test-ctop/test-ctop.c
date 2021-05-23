//
// Created by bernard on 23/05/2021.
//

#include <stdio.h>
#include "static-data.h"

int main(int argn, char *argv[]) {
    static_data *sdata = get_static_data();
    printf("System: %s\n",
           sdata->unames.sysname);
    printf("Processors: %s\n",
           sdata->str_processors);
    return 0;
}
