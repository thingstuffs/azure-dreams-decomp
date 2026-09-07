#include "common.h"

typedef struct S_800DA014_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_800DA014_0;   /* in_arg0 in func_800DA014 */

typedef struct S_800DA014_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_800DA014_1;   /* in_arg2 in func_800DA014 */

typedef struct S_800DA014_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_800DA014_2;   /* in_arg3 in func_800DA014 */

typedef struct S_800DA014_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800DA014_3;   /* system_base in func_800DA014 */

typedef struct S_800DA014_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_800DA014_4;   /* D_800814A8 in func_800DA014 */

typedef struct S_800DA014_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_800DA014_5;   /* origin in func_800DA014 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_8003DB94(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_800DA660(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800D8C64[];
extern u8 D_800E262C[];

void func_800DA014(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    s32 state;

    state = ((S_800DA014_0 *)in_arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (((S_800DA014_1 *)in_arg2)->unk_14 & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_800E262C;
        (*(void * *)((u8 *)in_arg2 + 0x2C)) = table;
        func_8003DB94(in_arg2,
            *(void **)(table + (((D_80083228 + ((S_800DA014_2 *)in_arg3)->unk_2A + 0x100) >> 7) & 28)),
            0);
        system_base = (u8 *)&D_80083460;
        ((S_800DA014_3 *)system_base)->unk_0A--;
        ((S_800DA014_0 *)in_arg0)->unk_9B++;
    }
    return;

state_one:
    {
        s32 flags;
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        if (((S_800DA014_3 *)system_base)->unk_02 & 0x1000) {
            return;
        }

        if ((((S_800DA014_2 *)in_arg3)->unk_64 != 0) &&
            (func_800AA6B4(in_arg0, in_arg1, in_arg2, 0) != 0)) {
            return;
        }

        if (((S_800DA014_2 *)in_arg3)->unk_25 == 0) {
            if (((S_800DA014_3 *)system_base)->unk_02 & 0x2008) {
                return;
            }
            func_800AA79C(in_arg0, in_arg1, in_arg2, in_arg3);
            return;
        }

        if ((func_800A2C34(in_arg3) << 16) != 0) {
            return;
        }

        flags = ((S_800DA014_2 *)in_arg3)->unk_1C;
        if (flags & 0x100) {
            func_800AA258(in_arg0, in_arg1, in_arg2, in_arg3);
            return;
        }

        if (flags & 0x80000) {
            func_800AA888(in_arg0, in_arg1, in_arg2, in_arg3);
            func_800DA660(in_arg0, in_arg1, in_arg2, in_arg3);
            return;
        }

        if (((S_800DA014_2 *)in_arg3)->unk_6D == 0) {
            return;
        }

        if ((func_800A2C34(in_arg3) << 16) != 0) {
            if ((func_8009A180(in_arg3,
                    (u8 *)((S_800DA014_4 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(in_arg3);
        func_800A9A04(in_arg3);

        if ((func_80042900(in_arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = ((S_800DA014_1 *)in_arg2)->unk_26;
            if ((((coordinate == ((S_800DA014_5 *)origin)->unk_26) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, in_arg2) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(in_arg3, 1);
            }
        }

        if ((func_80042900(in_arg3, 1) << 16) == 0) {
        u8 *table;

        table = D_800E262C;
        (*(void * *)((u8 *)in_arg2 + 0x2C)) = table;
        func_8003DB94(in_arg2,
            *(void **)(table + (((D_80083228 + ((S_800DA014_2 *)in_arg3)->unk_2A + 0x100) >> 7) & 28)),
            0);
        } else {
            return;
        }
    }

    if (!(((S_800DA014_1 *)in_arg2)->unk_14 & 0x8000)) {
        u8 *system_base = (u8 *)&D_80083460;

        ((S_800DA014_3 *)system_base)->unk_0A++;
        ((S_800DA014_0 *)in_arg0)->unk_9B++;
        return;
    }
    goto finish;

state_two:
    if (!(((S_800DA014_1 *)in_arg2)->unk_14 & 0xE000)) {
        return;
    }
    {
        u8 *system_base = (u8 *)&D_80083460;
        ((S_800DA014_3 *)system_base)->unk_0A--;
    }

finish:
    ((S_800DA014_2 *)in_arg3)->unk_1C &= ~0x200;
    ((S_800DA014_0 *)in_arg0)->unk_8C = D_800D8C64;
}
