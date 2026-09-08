#include "common.h"

typedef struct {
    s32 words[0x15];
} Record84;

extern s32 func_8009F970(void *, s32);
extern u8 *func_800B2344(void);
extern Record84 D_80100AF8;

/* Copies a record into the pointer table and initializes extra data for tag 0x13. */
void func_8009FA14(s32 entry_index, void *source) {
    u8 *record;
    s32 tag;
    s32 data_slot;
    u8 *table_base;

    record = func_800B2344();
    record[0] = ((u8 *)source)[0];
    record[1] = ((u8 *)source)[1];
    record[2] = ((u8 *)source)[2];
    tag = record[1];
    record[3] = ((u8 *)source)[3];
    switch (tag) {
    case 0x13:
        data_slot = func_8009F970((void *)0x800102F0, 0x14);
        *(Record84 *)(0x800102F0 + data_slot * 0x54) = D_80100AF8;
        record[3] = (record[3] & 0xC0) | data_slot;
        goto set_tail_page;
    default:
        table_base = (u8 *)0x80010000;
        goto store_record;
    }

set_tail_page:
    table_base = (u8 *)0x80010000;
store_record:
    *(void **)(table_base + entry_index * 4 + 0x29C) = record;
    *(s32 *)(table_base + entry_index * 4 + 0x2A0) = 0;
}
