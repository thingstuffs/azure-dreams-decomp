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

void func_8008AE4C(s32 arg0) {
    DungeonEntry *base;
    DungeonEntry *entry;
    DungeonState *state;
    s32 field_0;
    s32 field_1;
    s32 field_2;
    s32 field_4;
    s32 resource;

    base = D_800CF720;
    entry = &base[arg0];
    field_0 = entry->field_0;
    field_1 = entry->field_1;
    field_2 = entry->field_2;
    field_4 = entry->field_4;
    resource = func_80040574(0x8000);
    func_80069ED8(resource, D_801131B8.field_2C + func_8008ACE8(arg0), field_4);
    func_8008AD90(arg0, field_4);
    state = &D_801131B8;
    func_80069ED8(state->field_2C, resource, field_4);
    D_800CF720[0].field_0 = field_0;
    base->field_1 = field_1;
    base->field_2 = field_2;
    base->field_4 = field_4;
}
