// ======================================================================
// cooltop-tools.h
// Created by bernard on 02/03/2021.
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
// High level UI tools which can be moved to the library
// ======================================================================

#ifndef COOLTOP_COLTOP_TOOLS_H
#define COOLTOP_COLTOP_TOOLS_H
#include <nuklear.h>

typedef struct {
  nk_bool show_app_about;
  nk_bool (*fill_me)(struct nk_context *ctx);
} sub_window_behavior;

nk_bool new_sub_window(struct nk_context *ctx,
                       const char* title,
                       struct nk_rect bounds,
                       sub_window_behavior *window_behavior);
extern sub_window_behavior unames_behavior;
extern sub_window_behavior memory_behavior;

#endif // COOLTOP_COLTOP_TOOLS_H
