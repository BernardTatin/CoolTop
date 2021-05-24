//
// Created by bernard on 23/05/2021.
//

#ifndef COOLTOP_STATIC_DATA_H
#define COOLTOP_STATIC_DATA_H

#if defined(__linux__) && !defined(__Linux__)
#define __Linux__
#endif

#include <stdbool.h>
#include <string.h>
#if !defined(__NetBSD__)
#include <sys/sysinfo.h>    // deprecated ...
#include <gnu/libc-version.h>
#endif
#include <sys/utsname.h>

#define KILOB   1024
#define MEGAB   (1024 * KILOB)
#define GIGAB   (1024 * MEGAB)

typedef struct {
    struct utsname unames;
#if defined(__linux__) || defined(__NetBSD__)
    int nb_procs;
    int nb_procs_conf;
    char str_processors[64];
#endif
#if defined(__linux__)
    char str_libc_version[64];
#endif
    unsigned long total_ram;
    unsigned long total_swap;
} static_data;

static_data *get_static_data(void);

#endif //COOLTOP_STATIC_DATA_H
