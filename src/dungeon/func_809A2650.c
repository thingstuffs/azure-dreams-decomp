#include "common.h"

typedef struct S_80173E50_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80173E50_0;   /* arg0 in func_80173E50 */

typedef struct S_80173E50_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173E50_1;   /* arg2 in func_80173E50 */

typedef struct S_80173E50_2 {
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
} S_80173E50_2;   /* arg3 in func_80173E50 */

typedef struct S_80173E50_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173E50_3;   /* counter_base in func_80173E50 */

typedef struct S_80173E50_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173E50_4;   /* global_base in func_80173E50 */

typedef struct S_80173E50_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173E50_5;   /* owner in func_80173E50 */

typedef struct S_80173E50_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173E50_6;   /* origin in func_80173E50 */



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
extern void func_80174574(void *, void *, void *, void *);
extern void func_80175060(void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801710EC[];
extern u8 D_80175EA0[];
extern u8 D_80175EC0[];

void func_80173E50(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 flags;
    u16 current_value;
    u16 old_value;
    u8 *global_base;
    s32 state;

    state = ((S_80173E50_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
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
    if (!(((S_80173E50_1 *)arg2)->unk_14 & 0xE000)) {
        goto repeat_calls;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80175EA0;
    func_80047784(arg2,
        D_80175EA0[((D_80083228 + ((S_80173E50_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_80173E50_3 *)counter_base)->unk_0A--;
    }
    ASM_USE_NV(arg0);   /* MATCH pin: load-bearing for the whole function shape */
    ((S_80173E50_0 *)arg0)->unk_9B++;
    goto done;

state_one:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        global_base = (u8 *)&D_80083460;
        if (((S_80173E50_4 *)global_base)->unk_02 & 0x1000) {
            goto done;
        }
        if (((S_80173E50_2 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }
        if (((S_80173E50_2 *)arg3)->unk_25 == 0) {
            if (((S_80173E50_4 *)global_base)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }
        flags = ((S_80173E50_2 *)arg3)->unk_1C.s;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }
        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            current_value = ((S_80173E50_0 *)arg0)->unk_92;
            old_value = ((S_80173E50_0 *)arg0)->unk_A2;
            ((S_80173E50_0 *)arg0)->unk_A2 = 0;
            ((S_80173E50_0 *)arg0)->unk_9E = 0;
            ((S_80173E50_0 *)arg0)->unk_92 = current_value - old_value;
            func_80174574(arg0, arg1, arg2, arg3);
            goto done;
        }
        if (((S_80173E50_2 *)arg3)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(arg3,
                    (u8 *)((S_80173E50_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }
        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin = D_80082E80;
            s8 tile = ((S_80173E50_1 *)arg2)->unk_26;

            if (((tile == ((S_80173E50_6 *)origin)->unk_26) && (tile >= 0)) ||
                ((s16)func_8009FD40(origin, arg2) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(arg3, 1);
                }
            }
        }
        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto done;
        }
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80175EC0;
    func_80047784(arg2,
        D_80175EC0[((D_80083228 + ((S_80173E50_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80173E50_2 *)arg3)->unk_1C.u |= 0x40000;
    if (((S_80173E50_1 *)arg2)->unk_14 & 0x8000) {
        goto set_callback;
    }
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_80173E50_0 *)arg0)->unk_9B++;
        ((S_80173E50_3 *)counter_base)->unk_0A++;
    }
    goto done;

state_two:
    ASM_USE_NV(arg0);   /* MATCH pin: load-bearing for the whole function shape */
    if (!(((S_80173E50_1 *)arg2)->unk_14 & 0xE000)) {
        goto repeat_calls;
    }
    {
        register u8 *counter_base ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

        counter_base = (u8 *)&D_80083460;
        ((S_80173E50_3 *)counter_base)->unk_0A--;
    }

set_callback:
    ((S_80173E50_0 *)arg0)->unk_8C = D_801710EC;
    goto done;

repeat_calls:
done:
    return;
}
