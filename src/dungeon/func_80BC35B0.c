#include "common.h"

typedef struct S_80172DB0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    u8 pad_A8[0x4];
    s32 unk_AC;
    s32 unk_B0;
} S_80172DB0_0;   /* arg0 in func_80172DB0 */

typedef struct S_80172DB0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172DB0_1;   /* arg2 in func_80172DB0 */

typedef struct S_80172DB0_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172DB0_2;   /* arg3 in func_80172DB0 */

typedef struct S_80172DB0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172DB0_3;   /* arg1 in func_80172DB0 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_801719DC;
extern u8 D_8017464C[8];
extern u8 D_80174654[8];
extern u8 D_8017465C[8];
extern u8 D_80174664[8];

void func_80172DB0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = ((S_80172DB0_0 *)arg0)->unk_9B;
    if ((u32)state >= 6) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    if (((S_80172DB0_1 *)arg2)->unk_14 & 0x8000) {
        ((S_80172DB0_0 *)arg0)->unk_9B = 5;
        ((S_80172DB0_0 *)arg0)->unk_96.s = 0;
        ((S_80172DB0_1 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80172DB0_2 *)arg3)->unk_2A, 1);
        return;
    }
    ((S_80172DB0_3 *)arg1)->unk_14 = 0;
    ((S_80172DB0_3 *)arg1)->unk_10 = 0;
    ((S_80172DB0_3 *)arg1)->unk_0C = 0;
    if (((S_80172DB0_0 *)arg0)->unk_A4 != 0) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017464C;
    func_80047784(arg2,
        D_8017464C[((D_80083228 + ((S_80172DB0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172DB0_0 *)arg0)->unk_96.s = 8;
    ((S_80172DB0_0 *)arg0)->unk_9B++;
    return;

L1:
    {
        u16 timer = ((S_80172DB0_0 *)arg0)->unk_96.s;

        ((S_80172DB0_0 *)arg0)->unk_96.s = timer - 1;
        if ((s16)timer > 0 && !(((S_80172DB0_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174654;
    func_80047784(arg2,
        D_80174654[((D_80083228 + ((S_80172DB0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x707);
    ((S_80172DB0_0 *)arg0)->unk_96.s = 6;
    ((S_80172DB0_0 *)arg0)->unk_AC = 0x80000;
    ((S_80172DB0_0 *)arg0)->unk_B0 = (s32)0xFFFE0000;
    ((S_80172DB0_0 *)arg0)->unk_9B++;
    ((S_80172DB0_3 *)arg1)->unk_0C =
        -*(s16 *)(&D_8006CCD8 + (((u16)((S_80172DB0_2 *)arg3)->unk_2A >> 8) & 0xE)) << 18;
    ((S_80172DB0_3 *)arg1)->unk_10 =
        -*(s16 *)(&D_8006CCE8 + (((u16)((S_80172DB0_2 *)arg3)->unk_2A >> 8) & 0xE)) << 18;
    return;

L2:
    ((S_80172DB0_0 *)arg0)->unk_A4 += ((S_80172DB0_0 *)arg0)->unk_AC;
    ((S_80172DB0_0 *)arg0)->unk_AC += ((S_80172DB0_0 *)arg0)->unk_B0;
    if (((S_80172DB0_0 *)arg0)->unk_96.u < 2) {
        ((S_80172DB0_3 *)arg1)->unk_0C =
            *(s16 *)(&D_8006CCD8 + (((u16)((S_80172DB0_2 *)arg3)->unk_2A >> 8) & 0xE)) << 19;
        ((S_80172DB0_3 *)arg1)->unk_10 =
            *(s16 *)(&D_8006CCE8 + (((u16)((S_80172DB0_2 *)arg3)->unk_2A >> 8) & 0xE)) << 19;
    }
    {
        u16 timer = ((S_80172DB0_0 *)arg0)->unk_96.s;

        ((S_80172DB0_0 *)arg0)->unk_96.s = timer - 1;
        if ((s16)timer > 0 && !(((S_80172DB0_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
    }
    func_8009C12C(arg3, arg2, ((S_80172DB0_2 *)arg3)->unk_2A, 1);
    ((S_80172DB0_0 *)arg0)->unk_9B++;
    func_800A56E0(0x804);
    return;

L3:
    ((S_80172DB0_0 *)arg0)->unk_A4 += ((S_80172DB0_0 *)arg0)->unk_AC;
    ((S_80172DB0_0 *)arg0)->unk_AC += ((S_80172DB0_0 *)arg0)->unk_B0;
    if (!(((S_80172DB0_1 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017465C;
    func_80047784(arg2,
        D_8017465C[((D_80083228 + ((S_80172DB0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172DB0_0 *)arg0)->unk_9B++;
    ((S_80172DB0_3 *)arg1)->unk_10 = 0;
    ((S_80172DB0_3 *)arg1)->unk_0C = 0;
    ((S_80172DB0_0 *)arg0)->unk_A4 = 0;
    return;

L4:
    if (!(((S_80172DB0_1 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174664;
    func_80047784(arg2,
        D_80174664[((D_80083228 + ((S_80172DB0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172DB0_0 *)arg0)->unk_96.s = 4;
    ((S_80172DB0_0 *)arg0)->unk_A4 = 0;
    ((S_80172DB0_0 *)arg0)->unk_9B++;
    {
        s32 coord = ((S_80172DB0_1 *)arg2)->unk_24 << 6;
        s32 current = ((S_80172DB0_3 *)arg1)->unk_02 - 0x20;

        ((S_80172DB0_3 *)arg1)->unk_0C = ((coord - current) << 16)
            / ((S_80172DB0_0 *)arg0)->unk_96.u;
    }
    {
        s32 coord = ((S_80172DB0_1 *)arg2)->unk_25 << 6;
        s32 current = ((S_80172DB0_3 *)arg1)->unk_06 - 0x20;

        ((S_80172DB0_3 *)arg1)->unk_10 = ((coord - current) << 16)
            / ((S_80172DB0_0 *)arg0)->unk_96.u;
    }
    return;

L5:
    {
        s16 timer = ((S_80172DB0_0 *)arg0)->unk_96.u;

        if (timer != 0) {
            {
                s32 coord = ((S_80172DB0_1 *)arg2)->unk_24 << 6;
                s32 current = ((S_80172DB0_3 *)arg1)->unk_02 - 0x20;

                ((S_80172DB0_3 *)arg1)->unk_0C = ((coord - current) << 16) / timer;
            }
            {
                s32 coord = ((S_80172DB0_1 *)arg2)->unk_25 << 6;
                s32 current = ((S_80172DB0_3 *)arg1)->unk_06 - 0x20;

                ((S_80172DB0_3 *)arg1)->unk_10 = ((coord - current) << 16)
                    / ((S_80172DB0_0 *)arg0)->unk_96.u;
            }
        }
    }
    ((S_80172DB0_0 *)arg0)->unk_96.s--;
    if (!(((S_80172DB0_1 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    func_800AD594(arg3, 0x100);
    ((S_80172DB0_0 *)arg0)->unk_8C = &D_801719DC;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    ((S_80172DB0_3 *)arg1)->unk_10 = 0;
    ((S_80172DB0_3 *)arg1)->unk_0C = 0;
    ((S_80172DB0_3 *)arg1)->unk_02 = (((S_80172DB0_1 *)arg2)->unk_24 << 6) + 0x20;
    ((S_80172DB0_3 *)arg1)->unk_06 = (((S_80172DB0_1 *)arg2)->unk_25 << 6) + 0x20;
    ((S_80172DB0_2 *)arg3)->unk_46 &= 0x7FFF;
}
