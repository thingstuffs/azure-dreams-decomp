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

/* Move the selected entry and its data to the first slot. */
void func_8008AE4C(s32 entry_index)
{
    TownEntry *entries;
    TownEntry *entry;
    TownState *state;
    void *scratch;
    s32 saved_field0;
    s32 saved_field1;
    s32 saved_field2;
    s32 data_size;
    s32 data_offset;

    entries = D_800CF720;
    entry = &entries[entry_index];
    saved_field0 = entry->field0;
    saved_field1 = entry->field1;
    saved_field2 = entry->field2;
    data_size = entry->field4;

    scratch = func_80040574(0x8000);
    data_offset = func_8008ACE8(entry_index);
    state = &D_801131B8;
    memcpy(scratch, state->field2C + data_offset, data_size);
    func_8008AD90(entry_index, data_size);
    memcpy(state->field2C, scratch, data_size);

    D_800CF720[0].field0 = saved_field0;
    entries[0].field1 = saved_field1;
    entries[0].field2 = saved_field2;
    entries[0].field4 = data_size;
}
