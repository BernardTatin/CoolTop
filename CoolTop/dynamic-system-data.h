// ======================================================================
// dynamic-system-data.h
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
// Load the dynamic system data (RAM usage, CPU load, ...)
// ======================================================================

#ifndef COOLTOP_DYNAMIC_SYSTEM_DATA_H
#define COOLTOP_DYNAMIC_SYSTEM_DATA_H

typedef struct {
  struct sysinfo system_infos;
  char str_RAM[64];
  char str_SWAP[64];
  char str_SHARED[64];
  char str_BUFFERS[64];
} dynamic_data;

extern dynamic_data global_dynamic_data;
nk_bool load_dynamic_data();

#endif // COOLTOP_DYNAMIC_SYSTEM_DATA_H
