#include "common.h"


/* Copies encoded text, expanding table indices into two-byte characters. */
u8 *func_80099194(u8 *src, u8 *dst)
{
    u8 *table_page;
    u8 raw_byte;
    u32 table_mode;
    u32 table_marker;
    u32 byte_test;
    s32 index;

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
        if (byte_test == 0) {
            if (table_mode == 0) {
                break;
            }
            table_mode = 0;
            src++;
            continue;
        }

        byte_test = byte_test < 0x80;
        if (table_mode != 0) {
            index = *src;
            *dst++ = (*(u8 **)(table_page - 0x30A0))[(index * 2) - 2];
            src++;
            *dst++ = (*(u8 **)(table_page - 0x30A0))[(index * 2) - 1];
        } else {
            if (!byte_test) {
                *dst = raw_byte;
                src++;
                dst++;
            }
            *dst++ = *src++;
        }
    }
    return dst;
}
