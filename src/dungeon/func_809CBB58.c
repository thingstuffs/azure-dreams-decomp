#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80173358_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173358_0;   /* arg0 in func_80173358 */

typedef struct S_80173358_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173358_1;   /* arg2 in func_80173358 */

typedef struct S_80173358_2 {
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
} S_80173358_2;   /* arg3 in func_80173358 */

typedef struct S_80173358_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173358_3;   /* system_base in func_80173358 */


typedef struct S_80173358_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173358_5;   /* origin in func_80173358 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
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
extern void func_80173A30(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E54[];
extern u8 D_80173CDC[];
extern u8 D_80173CE4[];

void func_80173358(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    void *arg0 = in_arg0;
    void *arg1 = in_arg1;
    void *arg2 = in_arg2;
    void *arg3 = in_arg3;
    s32 state;

    state = ((S_80173358_0 *)arg0)->unk_9B;
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
    if (((S_80173358_1 *)arg2)->unk_14 & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_80173CDC;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173358_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        system_base = (u8 *)&D_80083460;
        ((S_80173358_3 *)system_base)->unk_0A--;
        ((S_80173358_0 *)arg0)->unk_9B++;
    }
    return;

state_one:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        s32 flags;
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        if (((S_80173358_3 *)system_base)->unk_02 & 0x1000) {
            return;
        }

        if ((((S_80173358_2 *)arg3)->unk_64 != 0) &&
            (func_800AA6B4(arg0, arg1, arg2, 0) != 0)) {
            return;
        }

        if (((S_80173358_2 *)arg3)->unk_25 == 0) {
            if (((S_80173358_3 *)system_base)->unk_02 & 0x2008) {
                return;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            return;
        }

        flags = ((S_80173358_2 *)arg3)->unk_1C;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173A30(arg0, arg1, arg2, arg3);
            return;
        }

        if (((S_80173358_2 *)arg3)->unk_6D == 0) {
            return;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);

        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = ((S_80173358_1 *)arg2)->unk_26;
            if ((((coordinate == ((S_80173358_5 *)origin)->unk_26) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, arg2) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(arg3, 1);
            }
        }

        if ((func_80042900(arg3, 1) << 16) != 0) {
            return;
        }
    }

    {
        u8 *table;

        table = D_80173CE4;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173358_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    if (!(((S_80173358_1 *)arg2)->unk_14 & 0x8000)) {
        u8 *system_base = (u8 *)&D_80083460;

        ((S_80173358_3 *)system_base)->unk_0A++;
        ((S_80173358_0 *)arg0)->unk_9B++;
        return;
    }
    goto finish;

state_two:
    if (!(((S_80173358_1 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    {
        u8 *system_base = (u8 *)&D_80083460;
        ((S_80173358_3 *)system_base)->unk_0A--;
    }

finish:
    ((S_80173358_2 *)arg3)->unk_1C &= ~0x200;
    ((S_80173358_0 *)arg0)->unk_8C = D_80170E54;
    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg2);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
}
