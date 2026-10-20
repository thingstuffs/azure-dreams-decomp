#include "common.h"

typedef unsigned long uptr;

extern u8 D_800D2EA4[];

/* Copy the final two bytes of 34 records and clear the four destination flags. */
void copy_record_tail_bytes(void)
{
    s32 entry_index;
    u8 *source_record;
    u8 *page;

    source_record = D_800D2EA4;
    page = (u8 *)0x80010000;
    for (entry_index = 0; entry_index < 0x22; entry_index++) {
        page[0x33A4 + entry_index * 2] = source_record[entry_index * 8 + 6];
        page[0x33A5 + entry_index * 2] = source_record[entry_index * 8 + 7];
    }

    entry_index = 0;
    page = (u8 *)0x80010000;
    do {
        u8 *flag_slot = (u8 *)((uptr)entry_index + (uptr)page);
        entry_index++;
        flag_slot[0x3608] = 0;
        flag_slot[0x360A] = 0;
    } while (entry_index < 2);
}
