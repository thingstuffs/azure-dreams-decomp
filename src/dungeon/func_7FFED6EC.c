#include "common.h"

typedef struct {
    s8 field_0;
    s8 field_1;
    s16 field_2;
    s32 field_4;
} DungeonEntry;

typedef struct {
    u8 pad_0[0x2C];
    s32 field_2C;
} DungeonState;

extern DungeonEntry D_800CF720[];
extern DungeonState D_801131B8;
extern s32 func_80040574(s32 arg0);
extern s32 func_8008ACE8(s32 arg0);
extern void func_80069ED8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8008AD90(s32 arg0, s32 arg1);

/* Move the selected entry data to the start and copy its metadata to entry zero. */
void func_8008AE4C(s32 entry_index) {
    DungeonEntry *entries;
    DungeonEntry *entry;
    DungeonState *state;
    s32 saved_field_0;
    s32 saved_field_1;
    s32 saved_field_2;
    s32 data_size;
    s32 scratch_buffer;

    entries = D_800CF720;
    entry = &entries[entry_index];
    saved_field_0 = entry->field_0;
    saved_field_1 = entry->field_1;
    saved_field_2 = entry->field_2;
    data_size = entry->field_4;
    scratch_buffer = func_80040574(0x8000);
    func_80069ED8(scratch_buffer, D_801131B8.field_2C + func_8008ACE8(entry_index), data_size);
    func_8008AD90(entry_index, data_size);
    state = &D_801131B8;
    func_80069ED8(state->field_2C, scratch_buffer, data_size);
    D_800CF720[0].field_0 = saved_field_0;
    entries->field_1 = saved_field_1;
    entries->field_2 = saved_field_2;
    entries->field_4 = data_size;
}
