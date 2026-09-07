#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80053DA8(s32 code);
extern s32 func_800231E4(s32 mode);
extern s32 func_80049E1C(s32 current, s32 direction, u8 entry);
extern void func_80022488(void *arg0);
extern s32 D_80083160[];
extern u8 D_800280B4[];

void func_80022524(void *arg0)
{
    s32 action;
    s32 flags8;
    s32 flags10;
    s32 value;
    s32 side;
    volatile s32 *input;

    input = D_80083160;
    action = 0;
    flags8 = input[2];
    if (flags8 == 0) {
        return;
    }
    flags10 = input[4];
    if (flags10 & 0x20) {
        s32 *owner20;

        func_80053DA8(0x515);
        func_800231E4(1);
        owner20 = FIELD(arg0, s32 *, 0x20);
        if (owner20 != 0) {
            *owner20 = 1;
        }
        goto common;
    }
    if (flags10 & 0x40) {
        s32 *owner40;
        s32 *owner_after;

        func_80053DA8(0x514);
        owner40 = FIELD(arg0, s32 *, 0x20);
        if (owner40 != 0) {
            value = func_800231E4(1);
            owner_after = FIELD(arg0, s32 *, 0x20);
            *owner_after = value;
            goto common;
        }
        func_800231E4(1);
        goto common;
    }
    if ((flags8 & 0xA000) != 0 && (flags10 & 0xA000) != 0) {
        FIELD(arg0, s32, 0x10) = 0;
        flags10 = input[4];
        if (flags10 & 0x8000) {
            goto negative_tail;
        }
        side = flags10 & 0x2000;
        goto side_check;
    }
    if (flags8 & 0xA000) {
        value = FIELD(arg0, s32, 0x10);
        if (value < 3) {
            side = value + 1;
            goto store_counter;
        }
        if (flags8 & 0x8000) {
            goto negative_tail;
        }
        side = flags8 & 0x2000;
        goto side_check;
    }
    goto common;

negative_tail:
    action = -1;
    goto common;

side_check:
    if (side == 0) {
        goto common;
    }
    action = 1;
    goto common;

store_counter:
    FIELD(arg0, s32, 0x10) = side;

common:
    if (action != 0) {
        s32 new_value;

        new_value = func_80049E1C(
            FIELD(arg0, s32, 0),
            action,
            D_800280B4[FIELD(arg0, s32, 8) * 0x18 + 0x14]);
        if (new_value != FIELD(arg0, s32, 0)) {
            FIELD(arg0, s32, 0) = new_value;
            func_80053DA8(0x502);
        }
        func_80022488(arg0);
    }
}
