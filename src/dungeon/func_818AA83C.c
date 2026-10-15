#include "modules/dungeon_ovl_18ca83c.h"

void func_8002403C(void *target, s32 amount_input, void *owner) {
    s32 base_amount;
    register s32 adjusted_amount;

    if (func_8009D218(target, 2) == 0) {
        base_amount = func_800A6870(amount_input & 0xFF) + 16;
        adjusted_amount = base_amount;
        if (*(u8 *)((u8 *)target + 0x28) & 2) {
            adjusted_amount = base_amount + ((s32)(base_amount << 16) >> 19);
        }
        *(u16 *)((u8 *)target + 0x64) += adjusted_amount;
        func_800AD568(target);
        base_amount = 0x8004;
        func_800B4C7C(base_amount, target, (s16)*(u16 *)((u8 *)target + 0x64), 1);
        func_800AD4D0(target);
    }
}

