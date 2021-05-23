//
// Created by bernard on 23/05/2021.
//

#include <stdio.h>
#include "static-data.h"

int main(int argn, char *argv[]) {
    static_data *sdata = get_static_data();
    printf("%s - %s - %s\n",
           sdata->unames.sysname,
           sdata->str_processors,
           sdata->str_libc_version);
    return 0;
}
