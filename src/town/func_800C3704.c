#include "common.h"

/* koya_mon_status_open: returns the indexed table byte. */
u8 func_800C0E64(s32 entry_index) {
    u8 *table_page = (u8 *)0x80010000;
    return *(u8 *)(table_page + entry_index * 2 + 0x33A4);
}
