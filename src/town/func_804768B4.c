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

s32 func_800178B4(TownContext *context, s32 index) {
    s32 value;
    s32 result;

    D_80019BB0 = 2;
    if (func_800175B0() == 0) {
        return 1;
    }

    value = func_8001764C();
    if (value == 0) {
        value = func_800176D4();
    }

    result = func_80017620(value);
    D_80019BB4 = value;
    context->entries[index].unk8 = result;
    return 0;
}
