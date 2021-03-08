// ======================================================================
// common.h
// Created by bernard on 28/02/2021.
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
// Include and definitions which are common to all projects
// ======================================================================

#ifndef COOLTOP_COMMON_H
#define COOLTOP_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#ifndef NK_IMPLEMENTATION
#ifndef NK_ASSERT
#include <assert.h>
#define NK_ASSERT(expr) assert(expr)
#endif
#endif

enum theme {THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK};

#define DBG()   { fprintf(stdout, "%5d %s\n", __LINE__, __FILE__); }

#define KILO_BYTES    (1024)
#define MEGA_BYTES    (KILO_BYTES * KILO_BYTES)
#define GIGA_BYTES    (MEGA_BYTES * KILO_BYTES)

#endif // COOLTOP_COMMON_H
