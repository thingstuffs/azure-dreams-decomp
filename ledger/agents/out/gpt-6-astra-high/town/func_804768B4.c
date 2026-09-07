#include "common.h"

typedef struct TownEntry {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} TownEntry;

typedef struct TownContext {
    u8 pad0[0x10];
    TownEntry *entries;
} TownContext;

s32 func_800175B0(void);
s32 func_80017620(s32);
s32 func_8001764C(void);
s32 func_800176D4(void);
extern s32 D_80019BB0;
extern s32 D_80019BB4;

/* Selects a value with a fallback and stores its converted result in the town entry. */
s32 func_800178B4(TownContext *context, s32 entry_index) {
    s32 selected_value;
    s32 entry_value;

    D_80019BB0 = 2;
    if (func_800175B0() == 0) {
        return 1;
    }

    selected_value = func_8001764C();
    if (selected_value == 0) {
        selected_value = func_800176D4();
    }

    entry_value = func_80017620(selected_value);
    D_80019BB4 = selected_value;
    context->entries[entry_index].unk8 = entry_value;
    return 0;
}
