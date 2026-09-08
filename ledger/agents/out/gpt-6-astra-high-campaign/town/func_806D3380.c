#include "common.h"

/* Sets flag 0x8000 on each indexed record until the 0xFF terminator. */
void func_80016B80(s32 records_base, u8 *indices) {
    s32 *record_flags;
    s32 flags;
    u8 *index_cursor;

    index_cursor = indices;
    if (*index_cursor != 0xFF) {
        do {
            record_flags = (*index_cursor * 0x1C) + records_base;
            flags = *record_flags;
            index_cursor += 1;
            *record_flags = flags | 0x8000;
        } while (*index_cursor != 0xFF);
    }
}
