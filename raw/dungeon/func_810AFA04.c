#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA79C(void *, s32, void *, void *);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_80173A20(void *, s32, void *, void *);

extern void *D_800814A8;
extern s32 D_80082E80;
extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_80170E54;
extern u8 D_80173C9C[];
extern u8 D_80173CA4[];

void func_80173204(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 flags;
    s8 floor;
    register u8 *status ASM_REG("$19");
    register s32 mode ASM_REG("$20");
    u8 *counter_base;
    u8 *floor_base;
    u8 *status_page;
    register u8 *table ASM_REG("$5");

    mode = arg1;
    ASM_KEEP_NV(mode);
    if (FIELD(arg0, u8, 0x9B) < 2U) {
        if (FIELD(arg2, u8, 0xC) < 0x33U) {
            goto dispatch;
        }
        FIELD(arg2, s32, 0xC) += -0x30303;
    } else if (FIELD(arg2, u8, 0xC) < 0x80U) {
        FIELD(arg2, s32, 0xC) += 0x30303;
    }

dispatch:
    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    goto done;

state_0:
    FIELD(arg3, s32, 0x1C) |= 0x10000000;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    table = D_80173C9C;
    ASM_USE(table);
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80047784(
        arg2,
        table[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    counter_base = D_80083460;
    ASM_KEEP_NV(counter_base);
    FIELD(counter_base, u16, 0xA) =
        FIELD(counter_base, u16, 0xA) - 1;
    goto increment_state;

state_1:
    if ((func_80042900(arg3, 1) << 16) == 0) {
        table = D_80173CA4;
        ASM_USE(table);
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(
            arg2,
            table[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg3, s32, 0x1C) &= ~0x200;
            FIELD(arg3, s32, 0x1C) &= 0xEFFFFFFF;
            FIELD(arg2, s32, 0xC) = 0x808080;
            FIELD(arg0, u8 *, 0x8C) = &D_80170E54;
            goto done;
        }
        goto increment_counter;
    }

    status_page = (u8 *)0x80080000;
    ASM_KEEP_NV(status_page);
    status = status_page + 0x3460;
    ASM_USE2(status_page, status);
    ASM_KEEP(status);
    if (FIELD(status, u16, 2) & 0x1000) {
        goto done;
    }
    if (FIELD(arg3, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, mode, arg2, 0) != 0) {
            goto done;
        }
    }
    if (FIELD(arg3, u8, 0x25) == 0) {
        if (FIELD(status, u16, 2) & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, mode, arg2, arg3);
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }

    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x100) {
        func_800AA258(arg0, mode, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, mode, arg2, arg3);
        func_80173A20(arg0, mode, arg2, arg3);
        goto done;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(
                 arg3,
                 FIELD(D_800814A8, s32, 0x58) + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        floor_base = (u8 *)&D_80082E80;
        ASM_KEEP_NV(floor_base);
        floor = FIELD(arg2, s8, 0x26);
        if (!((floor == FIELD(floor_base, s8, 0x26)) && (floor >= 0))) {
            if (func_8009FD40(floor_base, arg2) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(arg3, 1);
        }
    }

second_check:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }
    table = D_80173CA4;
    ASM_USE(table);
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80047784(
        arg2,
        table[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg3, s32, 0x1C) &= ~0x200;
        FIELD(arg3, s32, 0x1C) &= 0xEFFFFFFF;
        FIELD(arg2, s32, 0xC) = 0x808080;
        FIELD(arg0, u8 *, 0x8C) = &D_80170E54;
        goto done;
    }
increment_counter:
    {
        register u8 *counter ASM_REG("$2");

        counter = D_80083460;
        ASM_KEEP_NV(counter);
        FIELD(counter, u16, 0xA)++;
    }

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_2:
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        if (FIELD(arg2, u8, 0xC) < 0x80U) {
            goto done;
        }
    }
    {
        u8 *counter = D_80083460;
        FIELD(counter, u16, 0xA)--;
    }
    FIELD(arg3, s32, 0x1C) &= 0xEFFFFFFF;
    FIELD(arg2, s32, 0xC) = 0x808080;
    FIELD(arg3, s32, 0x1C) &= ~0x200;
    FIELD(arg0, u8 *, 0x8C) = &D_80170E54;

done:
    return;
}
