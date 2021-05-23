//
// Created by bernard on 23/05/2021.
//

#ifndef COOLTOP_STATIC_DATA_H
#define COOLTOP_STATIC_DATA_H

#include <stdbool.h>
#include <string.h>
#if !defined(__NetBSD__)
#include <sys/sysinfo.h>
#include <gnu/libc-version.h>
#endif
#include <sys/utsname.h>

typedef struct {
    struct utsname unames;
    char str_processors[64];
    char str_libc_version[64];
} static_data;

static_data *get_static_data(void);

#endif //COOLTOP_STATIC_DATA_H
