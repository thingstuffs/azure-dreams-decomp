#include "common.h"

typedef struct {
    u16 values[4];
} TownValues;

extern u8 D_80010000[];
extern s8 D_80016000[];
extern s32 D_80017530;
extern s32 D_8001753C;
extern s32 D_80017598;
extern s32 D_800175A4;
extern s32 func_800198D0();

void func_80017460(void **arg0) {
    TownValues local;
    register void *result;
    s32 index;
    register TownValues *source;

    source = (TownValues *)(D_80010000 + 0x7134);
    local = *source;
    if (func_800198D0(0x1391) == 0) {
        goto second_call;
    }
    result = &D_80017530;
    goto out;
second_call:
    if (func_800198D0(0x14) == 0) {
        goto set_3c;
    }
    index = *(s32 *)(*(void **)D_80016000 + 8);
    if (func_800198D0(local.values[index]) != 0) {
        goto set_a4;
    }
    result = &D_80017598;
    goto out;
set_a4:
    result = &D_800175A4;
    goto out;
set_3c:
    result = &D_8001753C;
out:
    *arg0 = result;
}
