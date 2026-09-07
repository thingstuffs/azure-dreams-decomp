#include "common.h"

typedef struct TownEntry {
    s8 field0;
    s8 field1;
    s16 field2;
    s32 field4;
} TownEntry;

typedef struct TownState {
    u8 pad0[0x2C];
    u8 *field2C;
} TownState;

extern TownEntry D_800CF720[];
extern TownState D_801131B8;

extern void *func_80040574(s32);
extern void memcpy(void *, void *, s32);
extern s32 func_8008ACE8(s32);
extern void func_8008AD90(s32, s32);

void func_8008AE4C(s32 index)
{
    TownEntry *entries;
    TownEntry *entry;
    TownState *state;
    void *buffer;
    s32 field0;
    s32 field1;
    s32 field2;
    s32 field4;
    s32 offset;

    entries = D_800CF720;
    entry = &entries[index];
    field0 = entry->field0;
    field1 = entry->field1;
    field2 = entry->field2;
    field4 = entry->field4;

    buffer = func_80040574(0x8000);
    offset = func_8008ACE8(index);
    state = &D_801131B8;
    memcpy(buffer, state->field2C + offset, field4);
    func_8008AD90(index, field4);
    memcpy(state->field2C, buffer, field4);

    D_800CF720[0].field0 = field0;
    entries[0].field1 = field1;
    entries[0].field2 = field2;
    entries[0].field4 = field4;
}

/* MECHANISM: Typed eight-byte TownEntry indexing forces the retail sll-by-three shape.
   A held entries base plus a direct field0 store exposes both retail D_800CF720 bases;
   promoted signed field locals and the held TownState base encode the nine-value hold set. */
