#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80082E94;
extern s32 D_800814A0[3];
extern M2C_UNK D_800DD140;
extern void func_80048AC8(void *, s32);

void func_80093A94(void *arg0, void *arg1, void *arg2) {
    u8 *obj = (u8 *)arg0;
    u8 *state = (u8 *)arg2;
    s16 temp_v1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 mode_next;
    u8 temp_v0_3;
    u8 temp_v1_4;

    func_80048AC8(state, *(s16 *)(obj + 8) + 2);
    if (D_80082E94 & 1) {
        *(u16 *)(state + 0x14) |= 1;
    } else {
        *(u16 *)(state + 0x14) &= 0xFFFE;
    }
    temp_v1 = *(s16 *)(obj + 4);
    if (temp_v1 == 1) {
        goto mode_one;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto mode_zero;
        }
        goto epilogue;
    }
    if (temp_v1 == 2) {
        goto mode_two;
    }
    if (temp_v1 == 3) {
        goto set_high;
    }
    goto epilogue;

mode_zero:
    temp_v1_2 = *(u16 *)(state + 0x1C);
    *(u16 *)(state + 0x1C) = (u16)(temp_v1_2 + ((s32)(0x1000 - temp_v1_2) / 4));
    temp_v0 = *(u16 *)(obj + 6) - 1;
    *(u16 *)(obj + 6) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        *(u16 *)(state + 0x1C) = 0x1000;
        goto increment_mode;
    }
    goto epilogue;

mode_one:
    if (*(s16 *)(obj + 8) == 0) {
        temp_v1_4 = *(u8 *)(state + 0xC);
        if (temp_v1_4 >= 0x81U) {
            temp_v0_3 = temp_v1_4 - 8;
            *(u8 *)(state + 0xC) = temp_v0_3;
            *(u8 *)(state + 0xE) = temp_v0_3;
            *(u8 *)(state + 0xD) = temp_v0_3;
        }
    }
    if (*(s32 *)(*(u8 **)obj + 0x2C) != (s32)&D_800DD140) {
        goto epilogue;
    }
    if (*(s16 *)(obj + 8) == 0) {
        temp_v1_3 = 8;
        mode_next = *(u16 *)(obj + 4);
        *(u16 *)(obj + 6) = temp_v1_3;
        goto increment_tail;
    }
    goto set_high;

mode_two:
    temp_v1_3 = *(u16 *)(state + 0x1C);
    *(u16 *)(state + 0x1C) = (u16)(temp_v1_3 + ((s32)(0 - temp_v1_3) / 4));
    temp_v0_2 = *(u16 *)(obj + 6) - 1;
    *(u16 *)(obj + 6) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        *(u16 *)(state + 0x1C) = 0;
        goto increment_mode;
    }
    goto epilogue;

increment_mode:
    mode_next = *(u16 *)(obj + 4);
increment_tail:
    mode_next += 1;
    *(u16 *)(obj + 4) = mode_next;
    goto epilogue;
set_high:
    *(u16 *)(obj - 2) |= 0x8000;
    D_800814A0[0] = D_800814A0[0] | 0x8000;
epilogue:
    return;
}
