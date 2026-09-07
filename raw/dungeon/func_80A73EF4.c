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
extern void func_80173EF4(void *, s32, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_80170E54;
extern u8 D_80174140[];
extern u8 D_80174188[];
extern u8 D_80174190[];

void func_801736F4(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 *status;
    s32 flags;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto exit;
    }
    if (state == 2) {
        goto state_two;
    }
    goto exit;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto exit;
    }
    {
        FIELD(arg2, void *, 0x2C) = D_80174190;
        func_80047784(
            arg2,
            D_80174190[((D_80083228
                         + FIELD(arg3, s16, 0x2A) + 0x100)
                        >> 9) & 7],
            0);
    }
    {
        u8 *counter;
        counter = D_80083460;
        FIELD(counter, u16, 0xA)--;
    }
    FIELD(arg0, u8, 0x9B)++;
    goto exit;

state_one:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        void *current_table;
        current_table = FIELD(arg2, void *, 0x2C);
        if (current_table == D_80174140) {
            FIELD(arg2, void *, 0x2C) = D_80174188;
        } else if (current_table == D_80174188) {
            FIELD(arg2, void *, 0x2C) = D_80174190;
        }
        func_80047784(
            arg2,
            ((u8 *)FIELD(arg2, void *, 0x2C))
                [((D_80083228
                   + FIELD(arg3, s16, 0x2A) + 0x100)
                  >> 9) & 7],
            0);
    }

    if ((func_80042900(arg3, 1) << 16) == 0) {
        FIELD(arg2, void *, 0x2C) = D_80174188;
        func_80047784(
            arg2,
            D_80174188[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100)
                        >> 9) & 7],
            0);
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg3, s32, 0x1C) &= ~0x200;
            FIELD(arg0, void *, 0x8C) = &D_80170E54;
            goto exit;
        }
        {
            u8 *counter = D_80083460;
            FIELD(counter, u16, 0xA)++;
        }
        FIELD(arg0, u8, 0x9B)++;
        goto exit;
    } else {
    status = D_80083460;
    if (!(FIELD(status, u16, 2) & 0x1000)
        && ((FIELD(arg3, s16, 0x64) == 0)
            || (func_800AA6B4(arg0, arg1, arg2, 0) == 0))) {

        if (FIELD(arg3, u8, 0x25) == 0) {
            if (FIELD(status, u16, 2) & 0x2008) {
                goto exit;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto exit;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto exit;
        }
        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto exit;
        }
        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173EF4(arg0, arg1, arg2, arg3);
            goto exit;
        }
        if (FIELD(arg3, s8, 0x6D) == 0) {
            goto exit;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(
                     arg3,
                     FIELD(D_800814A8, s32, 0x58)
                         + 0x20)
                 << 16)
                != 0) {
                goto exit;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *room_base;
            s32 room_value;
            room_base = D_80082E80;
            room_value = FIELD(arg2, s8, 0x26);
            if (((room_value == FIELD(room_base, s8, 0x26))
                 && (room_value >= 0))
                || (func_8009FD40(room_base, arg2) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(arg3, 1);
                }
            }
        }
        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto exit;
        }

        FIELD(arg2, void *, 0x2C) = D_80174188;
        func_80047784(
            arg2,
            D_80174188[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100)
                        >> 9) & 7],
            0);
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg3, s32, 0x1C) &= ~0x200;
            FIELD(arg0, void *, 0x8C) = &D_80170E54;
            goto exit;
        }
        {
            u8 *counter = D_80083460;
            FIELD(counter, u16, 0xA)++;
        }
        FIELD(arg0, u8, 0x9B)++;
        goto exit;
    }
    }
    goto exit;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto exit;
    }
    {
        u8 *counter;
        counter = D_80083460;
        FIELD(counter, u16, 0xA)--;
    }
    FIELD(arg3, s32, 0x1C) &= ~0x200;
    FIELD(arg2, void *, 0x2C) = D_80174188;
    func_80047784(
        arg2,
        D_80174188[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100)
                    >> 9) & 7],
        0);
    FIELD(arg0, void *, 0x8C) = &D_80170E54;
    goto exit;

exit:
    return;
}
