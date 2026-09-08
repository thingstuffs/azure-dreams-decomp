#include "common.h"

extern u8 *D_800DCF60;

/* Copies encoded text, expanding table indices into two-byte characters. */
u8 *func_80099194(u8 *src, u8 *dst)
{
    u8 *table_page;
    u8 raw_byte;
    u32 table_mode;
    u32 table_marker;
    u32 byte_test;

    table_mode = 0;
    table_marker = 0x51;
    table_page = (u8 *)0x800E0000;
    for (;;) {
        if ((table_mode == 0) && (*src == table_marker)) {
            table_mode = 1;
            src++;
            continue;
        }

        raw_byte = *src;
        byte_test = raw_byte;
        if (byte_test != 0) {
            goto nonzero;
        }
        if (table_mode == 0) {
            goto done;
        }
        table_mode = 0;
        src++;
        continue;

nonzero:
        byte_test = byte_test < 0x80;
        if (table_mode != 0) {
            raw_byte = *(volatile u8 *)src;
            *dst++ = (*(u8 **)(table_page - 0x30A0))[((u32)raw_byte * 2) - 2];
            src++;
            *dst++ = (*(u8 **)(table_page - 0x30A0))[((u32)raw_byte * 2) - 1];
        } else {
            if (!byte_test) {
                *dst = raw_byte;
                src++;
                dst++;
            }
            *dst++ = *src++;
        }
    }

done:
    return dst;
}
