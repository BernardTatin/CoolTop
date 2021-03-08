// ======================================================================
// cooltop-common.h
// Created by bernard on 03/03/2021.
// ======================================================================
/*
MIT License

Copyright (c) 2021 Bernard Tatin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
// ======================================================================
// Includes and definitions for the CoolTop application.
// ======================================================================

#ifndef COOLTOP_COOLTOP_COMMON_H
#define COOLTOP_COOLTOP_COMMON_H

#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <gnu/libc-version.h>

#include "common.h"

#if !defined(WINDOW_WIDTH )
#define WINDOW_WIDTH 1200
#endif
#if !defined(WINDOW_HEIGHT )
#define WINDOW_HEIGHT 800
#endif

#if !defined(MAX_VERTEX_BUFFER )
#define MAX_VERTEX_BUFFER (512 * 1024)
#endif
#if !defined(MAX_ELEMENT_BUFFER )
#define MAX_ELEMENT_BUFFER (128 * 1024)
#endif

#include "cooltop-tools.h"
#include "environment.h"
#include "nuke-tools.h"
#include "static-system-data.h"
#include "dynamic-system-data.h"

#endif // COOLTOP_COOLTOP_COMMON_H
