//
// Created by bernard on 03/03/2021.
//

#ifndef COOLTOP_STATIC_SYSTEM_DATA_H
#define COOLTOP_STATIC_SYSTEM_DATA_H

extern struct utsname unames;
extern char str_processors[64];
extern char str_libc_version[64];

nk_bool load_unames(void);


#endif // COOLTOP_STATIC_SYSTEM_DATA_H
