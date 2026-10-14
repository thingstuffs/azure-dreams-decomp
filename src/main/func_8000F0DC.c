#include "common.h"

s32 func_8002191C();
s32 func_800219B8();

extern s32 D_800287CC;
extern s32 D_80084120[];
extern s32 D_80084128[];

/* Store a value and its converted result in the selected state slot. */
void func_800220DC(void) {
    s32 state_index;
    s32 source_value;

    state_index = D_800287CC != 0;
    source_value = func_8002191C();
    D_80084128[state_index] = source_value;
    D_80084120[state_index] = func_800219B8(source_value);
}
