#include "common.h"

typedef struct TownEntry {
    u8 field0;
    u8 field1;
    u16 field2;
    s32 field4;
} TownEntry;

typedef struct TownState {
    u8 pad0[0x2C];
    u8 *field2C;
} TownState;

extern TownEntry D_800CF720[];
extern TownState D_801131B8;
extern s32 func_8008ACE8(s32 index, TownEntry *entry);
extern void func_8008ACAC(void *dst, void *src, s32 value);

void func_8008AD90(s32 count, s32 offset) {
    TownEntry *entries;
    TownState *state;
    s32 index;
    s32 value;
    u8 *src;

    if (count != 0) {
        entries = D_800CF720;
        state = &D_801131B8;
        do {
            TownEntry *dst = (TownEntry *)((count << 3) + (unsigned long)entries);
            index = count - 1;
            dst->field0 = entries[index].field0;
            dst->field1 = entries[index].field1;
            dst->field2 = entries[index].field2;
            value = entries[index].field4;
            dst->field4 = value;
            src = state->field2C + func_8008ACE8(index, dst);
            func_8008ACAC(src + offset, src, value);
            count = index;
        } while (count != 0);
    }
}
