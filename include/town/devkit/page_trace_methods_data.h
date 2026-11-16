#ifndef TOWN_DEVKIT_PAGE_TRACE_METHODS_DATA_H
#define TOWN_DEVKIT_PAGE_TRACE_METHODS_DATA_H

#include "common.h"

/* Callback table in the KSEG1-linked town devkit image. */
typedef struct {
    u8 pad64[0x64];
    void (*print)(char *format, char *name, s32 value);
    u8 pad68[4];
    void (*flush)(s32 mode);
    void (*callback70)(s32);
} DevkitPageTraceMethods;

extern DevkitPageTraceMethods *devkit_page_trace_methods;

#endif
