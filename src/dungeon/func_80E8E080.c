#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80173880_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173880_0;   /* arg0 in func_80173880 */

typedef struct S_80173880_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173880_1;   /* arg2 in func_80173880 */

typedef struct S_80173880_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173880_2;   /* arg3 in func_80173880 */

typedef struct S_80173880_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173880_3;   /* system_base in func_80173880 */

typedef struct S_80173880_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173880_4;   /* held_base in func_80173880 */


typedef struct S_80173880_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173880_6;   /* origin in func_80173880 */



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
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174060(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083460[];
extern u8 D_801710F4[];
extern u8 D_80174F40[];
extern u8 D_80174F48[];
extern u8 D_80174F50[];

void func_80173880(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    void *arg0 = in_arg0;
    void *arg1 = in_arg1;
    void *arg2 = in_arg2;
    void *arg3 = in_arg3;
    u8 *held_base;
    s32 state;

    state = ((S_80173880_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_zero:
    if (((S_80173880_1 *)arg2)->unk_14 & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_80174F50;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173880_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        system_base = (u8 *)&D_80083460;
        ((S_80173880_3 *)system_base)->unk_0A--;
        goto increment_state;
    }
    goto done;

state_one:
    if (((S_80173880_1 *)arg2)->unk_14 & 0xE000) {
        u8 *table;

        table = D_80174F48;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173880_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto state_one_long;
    }

    {
        {
            u8 *table;

            table = D_80174F50;
            (*(void * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(arg2,
                table[((D_80083228 + ((S_80173880_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        if (((S_80173880_1 *)arg2)->unk_14 & 0x8000) {
            goto finish;
        }

        {
            register u8 *system_base ASM_REG("$2") = (u8 *)&D_80083460;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            ((S_80173880_3 *)system_base)->unk_0A++;
        }
        goto increment_state;
    }

state_one_long:
    {
        s32 flags;

        held_base = (u8 *)&D_80083460;
        if (((S_80173880_4 *)held_base)->unk_02 & 0x1000) {
            goto done;
        }

        if (((S_80173880_2 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if (((S_80173880_2 *)arg3)->unk_25 == 0) {
            if (((S_80173880_4 *)held_base)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }

        flags = ((S_80173880_2 *)arg3)->unk_1C.s;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174060(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (((S_80173880_2 *)arg3)->unk_6D == 0) {
            goto done;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);

        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = ((S_80173880_1 *)arg2)->unk_26;
            if ((((coordinate == ((S_80173880_6 *)origin)->unk_26) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, arg2) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(arg3, 1);
            }
        }

        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto done;
        }
    }

    {
        u8 *table;

        table = D_80174F50;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173880_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    if (((S_80173880_1 *)arg2)->unk_14 & 0x8000) {
        goto finish;
    }

    {
        u8 *system_base = (u8 *)&D_80083460;
        register u16 val ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        val = ((S_80173880_3 *)system_base)->unk_0A;
        val++;
        ASM_KEEP(val);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        ((S_80173880_3 *)system_base)->unk_0A = val;
    }
    goto increment_state;

state_two:
    if (((S_80173880_1 *)arg2)->unk_14 & 0xE000) {
        u8 *table;

        table = D_80174F40;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80173880_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }
    goto done;

increment_state:
    ((S_80173880_0 *)arg0)->unk_9B++;
    goto done;

state_three:
    if (!(((S_80173880_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        ((S_80173880_3 *)system_base)->unk_0A--;
    }

finish:
    ((S_80173880_2 *)arg3)->unk_1C.u &= ~0x200;
    ((S_80173880_0 *)arg0)->unk_8C = D_801710F4;

done:
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    return;
}
