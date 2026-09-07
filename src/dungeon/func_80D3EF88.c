#include "common.h"

typedef struct S_80174788_0 {
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
} S_80174788_0;   /* arg0 in func_80174788 */

typedef struct S_80174788_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80174788_1;   /* arg2 in func_80174788 */

typedef struct S_80174788_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174788_2;   /* counter_base in func_80174788 */

typedef struct S_80174788_3 {
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
} S_80174788_3;   /* arg3 in func_80174788 */

typedef struct S_80174788_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174788_4;   /* global_base in func_80174788 */

typedef struct S_80174788_5 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_80174788_5;   /* D_800814A8 in func_80174788 */

typedef struct S_80174788_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174788_6;   /* counter_base2 in func_80174788 */



extern void func_80047784();
extern s32 func_8009A180();
extern s32 func_800A2C34();
extern void func_800A9A04();
extern void func_800A9A0C();
extern void func_800AA258();
extern s32 func_800AA6B4();
extern void func_800AA888();
extern void func_80174A68();

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2428[];
extern u8 D_800E2430[];
extern u8 D_80171A80[];

void func_80174788(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 state;
    u16 old_value;
    u16 current_value;
    s32 flags;
    u8 *global_base;

    state = ((S_80174788_0 *)arg0)->unk_9B;
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
    if (!(((S_80174788_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        ((S_80174788_2 *)counter_base)->unk_0A--;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_800E2428;
    func_80047784(arg2,
                  D_800E2428[((D_80083228 + ((S_80174788_3 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                  0);
    goto increment_state;

state_one:
    global_base = (u8 *)&D_80083460;
    if (((S_80174788_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (((S_80174788_3 *)arg3)->unk_64 != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = ((S_80174788_3 *)arg3)->unk_1C;
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        current_value = ((S_80174788_0 *)arg0)->unk_92;
        old_value = ((S_80174788_0 *)arg0)->unk_A2;
        ((S_80174788_0 *)arg0)->unk_A2 = 0;
        ((S_80174788_0 *)arg0)->unk_9E = 0;
        ((S_80174788_0 *)arg0)->unk_92 = current_value - old_value;
        func_80174A68(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (((S_80174788_3 *)arg3)->unk_6D == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(arg3, ((S_80174788_5 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if (((S_80174788_3 *)arg3)->unk_25 == 0) {
        goto done;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_800E2430;
    func_80047784(arg2,
                  D_800E2430[((D_80083228 + ((S_80174788_3 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                  0);
    ((S_80174788_3 *)arg3)->unk_1C |= 0x40000;
    ((S_80174788_4 *)global_base)->unk_0A++;

increment_state:
    ((S_80174788_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (!(((S_80174788_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base2;

        counter_base2 = (u8 *)&D_80083460;
        ((S_80174788_6 *)counter_base2)->unk_0A--;
    }
    ((S_80174788_3 *)arg3)->unk_1C &= ~8;
    ((S_80174788_0 *)arg0)->unk_8C = D_80171A80;

done:
    return;
}
