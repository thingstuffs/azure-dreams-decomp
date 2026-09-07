#include "common.h"

#include "common.h"

typedef struct Entry {
    u8 unk0;
    u8 kind;
    u8 unk2;
    u8 index;
} Entry;

extern Entry *D_8001029C[];
extern void func_800A0150(s32, Entry *, void *, s32);

void func_8003B714(void) {
    Entry **cursor;
    Entry *entry;
    s32 offset;
    u32 page;
    s32 value;

    if (D_8001029C[0] != 0) {
        page = 0x80010000;
        cursor = (Entry **)0x8001029C;
loop:
        entry = *cursor;
        if (entry->kind == 0x13) {
            offset = (entry->index & 0x1F) * 0x54;
            value = *(s8 *)(offset + page + 0x333);
            if (value >= 0) {
                func_800A0150(value & 0x3F, entry,
                              (void *)(offset + 0x800102F0), 1);
            }
        }
        cursor++;
        if (*cursor != 0) {
            goto loop;
        }
    }
}
