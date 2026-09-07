#include "common.h"

typedef struct {
    s32 words[0x15];
} Record84;

extern s32 func_8009F970(void *, s32);
extern u8 *func_800B2344(void);
extern Record84 D_80100AF8;

void func_8009FA14(s32 index, void *input) {
    u8 *record;
    s32 tag;
    s32 slot;
    u8 *entry_base;

    record = func_800B2344();
    record[0] = ((u8 *)input)[0];
    record[1] = ((u8 *)input)[1];
    record[2] = ((u8 *)input)[2];
    tag = record[1];
    record[3] = ((u8 *)input)[3];
    switch (tag) {
    case 0x13:
        slot = func_8009F970((void *)0x800102F0, 0x14);
        *(Record84 *)(0x800102F0 + slot * 0x54) = D_80100AF8;
        record[3] = (record[3] & 0xC0) | slot;
        goto set_tail_page;
    default:
        entry_base = (u8 *)0x80010000;
        goto store_record;
    }

set_tail_page:
    entry_base = (u8 *)0x80010000;
store_record:
    *(void **)(entry_base + index * 4 + 0x29C) = record;
    *(s32 *)(entry_base + index * 4 + 0x2A0) = 0;
}
