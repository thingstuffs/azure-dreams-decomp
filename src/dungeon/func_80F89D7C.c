#include "common.h"

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    u16 unk_A0;
} S_8017357C_0;   /* arg0 in func_8017357C */

typedef struct S_8017357C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_8017357C_1;   /* arg2 in func_8017357C */

typedef struct S_8017357C_2 {
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
} S_8017357C_2;   /* arg3 in func_8017357C */

typedef struct S_8017357C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017357C_3;   /* counter_base in func_8017357C */

typedef struct S_8017357C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8017357C_4;   /* global_base in func_8017357C */

typedef struct S_8017357C_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017357C_5;   /* owner in func_8017357C */

typedef struct S_8017357C_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8017357C_6;   /* origin in func_8017357C */

typedef struct S_8017357C_7 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8017357C_7;   /* arg1 in func_8017357C */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173D38(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174AFC[];
extern u8 D_80174B04[];

void func_8017357C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 flags;
    s32 counter_value;
    register u8 *counter_base ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *global_base;
    s32 state;

    state = ((S_8017357C_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((S_8017357C_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AFC;
    func_80047784(arg2,
        D_80174AFC[((D_80083228 + ((S_8017357C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    counter_base = (u8 *)&D_80083460;
    counter_value = ((S_8017357C_3 *)counter_base)->unk_0A - 1;
    goto store_counter;

state_one:
    if ((func_80042900(arg3, 1) << 16) == 0) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174B04;
        func_80047784(arg2,
            D_80174B04[((D_80083228 + ((S_8017357C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        flags = ((S_8017357C_2 *)arg3)->unk_1C | 0x40000;
        ((S_8017357C_2 *)arg3)->unk_1C = flags;
        if (((S_8017357C_1 *)arg2)->unk_14 & 0x8000) {
            ((S_8017357C_2 *)arg3)->unk_1C = flags & ~0x200;
            goto set_callback;
        }
        goto increment_state;
    }
    global_base = (u8 *)&D_80083460;
    if (((S_8017357C_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (((S_8017357C_2 *)arg3)->unk_64 != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if (((S_8017357C_2 *)arg3)->unk_25 == 0) {
        if (((S_8017357C_4 *)global_base)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, arg1, arg2, arg3);
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = ((S_8017357C_2 *)arg3)->unk_1C;
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        ((S_8017357C_0 *)arg0)->unk_A0 = 0;
        func_80173D38(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (((S_8017357C_2 *)arg3)->unk_6D == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        void *owner = D_800814A8;

        if ((func_8009A180(arg3,
                (u8 *)((S_8017357C_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 tile = ((S_8017357C_1 *)arg2)->unk_26;

        if (((tile == ((S_8017357C_6 *)origin)->unk_26) && (tile >= 0)) ||
            ((s16)func_8009FD40(origin, arg2) < 2)) {
            if (!(func_800A6D30() & 7)) {
                func_80042B68(arg3, 1);
            }
        }
    }
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174B04;
    func_80047784(arg2,
        D_80174B04[((D_80083228 + ((S_8017357C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    flags = ((S_8017357C_2 *)arg3)->unk_1C | 0x40000;
    ((S_8017357C_2 *)arg3)->unk_1C = flags;
    if (((S_8017357C_1 *)arg2)->unk_14 & 0x8000) {
        ((S_8017357C_2 *)arg3)->unk_1C = flags & ~0x200;
        goto set_callback;
    }

increment_state:
    counter_value = 3;
    counter_base = (u8 *)&D_80083460;
    ((S_8017357C_0 *)arg0)->unk_96.s = counter_value;
    counter_value = ((S_8017357C_3 *)counter_base)->unk_0A + 1;

store_counter:
    ((S_8017357C_3 *)counter_base)->unk_0A = counter_value;
    ((S_8017357C_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    ((S_8017357C_0 *)arg0)->unk_96.s--;
    if (((S_8017357C_0 *)arg0)->unk_96.u <= 0) {
        ((S_8017357C_7 *)arg1)->unk_14 = 0xFFF00000;
    }
    if (!(((S_8017357C_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_8017357C_7 *)arg1)->unk_14 = 0;
    ((S_8017357C_0 *)arg0)->unk_A0 = 0;
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AD4;
    func_80047784(arg2,
        D_80174AD4[((D_80083228 + ((S_8017357C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_8017357C_3 *)counter_base)->unk_0A--;
    }
    ((S_8017357C_2 *)arg3)->unk_1C &= ~0x200;

set_callback:
    ((S_8017357C_0 *)arg0)->unk_8C = D_80171138;

done:
    return;
}
