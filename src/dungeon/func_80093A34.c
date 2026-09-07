#include "common.h"

extern u8 *D_800DCF60;

u8 *func_80099194(u8 *src, u8 *dst)
{
    u8 *page;
    u8 raw;
    u32 mode;
    u32 marker;
    u32 c;

    mode = 0;
    marker = 0x51;
    page = (u8 *)0x800E0000;
    for (;;) {
        if ((mode == 0) && (*src == marker)) {
            mode = 1;
            src++;
            continue;
        }

        raw = *src;
        c = raw;
        if (c != 0) {
            goto nonzero;
        }
        if (mode == 0) {
            goto done;
        }
        mode = 0;
        src++;
        continue;

nonzero:
        c = c < 0x80;
        if (mode != 0) {
            raw = *(volatile u8 *)src;
            *dst++ = (*(u8 **)(page - 0x30A0))[((u32)raw * 2) - 2];
            src++;
            *dst++ = (*(u8 **)(page - 0x30A0))[((u32)raw * 2) - 1];
        } else {
            if (!c) {
                *dst = raw;
                src++;
                dst++;
            }
            *dst++ = *src++;
        }
    }

done:
    return dst;
}

/* MECHANISM: True-space targets are local loop/join edges, yielding a frameless leaf
   with mode in a2 and a held 0x800e page in a3.  Separate raw/promoted byte lifetimes
   plus one volatile table-path reload reproduce v1/v0; explicit src-then-dst increments
   close the final two-word reorder. */
