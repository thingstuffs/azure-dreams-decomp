#include "common.h"

typedef struct S_80172830_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172830_0;   /* arg0 in func_80172830 */

typedef struct S_80172830_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172830_1;   /* arg2 in func_80172830 */

typedef struct S_80172830_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172830_2;   /* arg3 in func_80172830 */

typedef struct S_80172830_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172830_3;   /* arg1 in func_80172830 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8[];
extern u8 D_80170E7C;
extern u8 D_80174C34[];
extern u8 D_80174C64[];
extern u8 D_80174C6C[];

void func_80172830(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 offset;
    s32 value;
    u16 timer;

    state = ((S_80172830_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    if (((S_80172830_1 *)arg2)->unk_14 & 0x8000) {
        ((S_80172830_0 *)arg0)->unk_9B = 3;
        ((S_80172830_0 *)arg0)->unk_96 = 0;
        ((S_80172830_1 *)arg2)->unk_14 |= 0x6000;
        goto end;
    }

    offset = (((((S_80172830_2 *)arg3)->unk_2A.s >> 9) & 7) + 4) % 8;
    ((S_80172830_3 *)arg1)->unk_0C =
        D_8006CCD8[offset] * 3 << 16;
    ((S_80172830_3 *)arg1)->unk_10 =
        D_8006CCE8[offset] * 3 << 16;
    ((S_80172830_3 *)arg1)->unk_14 = 0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174C34;
    func_80047784(arg2,
        D_80174C34[((D_80083228 + ((S_80172830_2 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    {
        s32 post_state;

        post_state = ((S_80172830_0 *)arg0)->unk_9B;
        ((S_80172830_0 *)arg0)->unk_96 = 0;
        post_state++;
        ((S_80172830_0 *)arg0)->unk_9B = post_state;
        goto end;
    }

state_1:
    ((S_80172830_3 *)arg1)->unk_0C -= ((S_80172830_3 *)arg1)->unk_0C >> 2;
    ((S_80172830_3 *)arg1)->unk_10 -= ((S_80172830_3 *)arg1)->unk_10 >> 2;
    if (!(((S_80172830_1 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174C64;
    func_80047784(arg2,
        D_80174C64[((D_80083228 + ((S_80172830_2 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    {
        s32 post_state;

        post_state = ((S_80172830_0 *)arg0)->unk_9B;
        ((S_80172830_0 *)arg0)->unk_96 = 4;
        post_state++;
        ((S_80172830_0 *)arg0)->unk_9B = post_state;
        goto end;
    }

state_2:
    if (!(((S_80172830_1 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    func_800A56E0(0x808);
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174C6C;
    func_80047784(arg2,
        D_80174C6C[((D_80083228 + ((S_80172830_2 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    ((S_80172830_0 *)arg0)->unk_96 = 0x14;
    ((S_80172830_3 *)arg1)->unk_14 = 0;
    ((S_80172830_3 *)arg1)->unk_10 = 0;
    ((S_80172830_3 *)arg1)->unk_0C = 0;
    {
        s32 post_state;

        post_state = ((S_80172830_0 *)arg0)->unk_9B;
        post_state++;
        ((S_80172830_0 *)arg0)->unk_9B = post_state;
        goto end;
    }

state_3:
    timer = ((S_80172830_0 *)arg0)->unk_96;
    value = ((S_80172830_3 *)arg1)->unk_14;
    timer--;
    ((S_80172830_0 *)arg0)->unk_96 = timer;
    if ((s16)timer < 12) {
        value += 0x1400;
    } else {
        value += 0x20000;
    }
    ((S_80172830_3 *)arg1)->unk_14 = value;
    ((S_80172830_0 *)arg0)->unk_90 += value;

    if ((s16)((S_80172830_0 *)arg0)->unk_96 == 0x11) {
        s32 sample;
        s16 *first_base;
        s16 *first_entry;
        s16 *entry;

        offset = ((S_80172830_2 *)arg3)->unk_2A.s >> 8;
        first_base = D_8006CCD8;
        first_entry = (s16 *)((u8 *)first_base + (offset & 0xE));
        sample = *first_entry;
        ((S_80172830_3 *)arg1)->unk_0C =
            (sample * 3 << 16) + ((sample * 3 << 16) >> 2);
        entry = (s16 *)((u8 *)&D_8006CCE8 + (offset & 0xE));
        sample = *entry;
        ((S_80172830_3 *)arg1)->unk_14 = 0xFFF70000;
        ((S_80172830_3 *)arg1)->unk_10 =
            (sample * 3 << 16) + ((sample * 3 << 16) >> 2);
        ((S_80172830_0 *)arg0)->unk_90 = 0;
        ((S_80172830_0 *)arg0)->unk_98 |= 8;
    }

    if (((((S_80172830_1 *)arg2)->unk_04 == 3) &&
         (((S_80172830_1 *)arg2)->unk_14 & 0x1000)) ||
        (((S_80172830_1 *)arg2)->unk_14 & 0x8000)) {
        func_8009C12C(arg3, arg2, ((S_80172830_2 *)arg3)->unk_2A.u, 1);
    }

    if (((((S_80172830_1 *)arg2)->unk_04 == 5) &&
         (((S_80172830_1 *)arg2)->unk_14 & 0x1000)) ||
        (((S_80172830_1 *)arg2)->unk_14 & 0x8000)) {
        ((S_80172830_3 *)arg1)->unk_0C =
            ((((((S_80172830_1 *)arg2)->unk_24 << 6) + 0x20) << 16) -
             ((S_80172830_3 *)arg1)->unk_00) / (s16)((S_80172830_0 *)arg0)->unk_96;
        ((S_80172830_3 *)arg1)->unk_10 =
            ((((((S_80172830_1 *)arg2)->unk_25 << 6) + 0x20) << 16) -
             ((S_80172830_3 *)arg1)->unk_04) / (s16)((S_80172830_0 *)arg0)->unk_96;
    }

    if (((s16)((S_80172830_0 *)arg0)->unk_96 > 0) &&
        !(((S_80172830_1 *)arg2)->unk_14 & 0x8000)) {
        goto end;
    }
    ((S_80172830_3 *)arg1)->unk_14 = 0;
    ((S_80172830_3 *)arg1)->unk_10 = 0;
    ((S_80172830_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172830_1 *)arg2)->unk_24, ((S_80172830_1 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    (*(u8 * *)((u8 *)arg0 + 0x8C)) = &D_80170E7C;
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg0 + 0x98)) &= 0xFFF7;
    func_800A4ACC(arg3);
    if (((S_80172830_2 *)arg3)->unk_6D == 0) {
        ((S_80172830_2 *)arg3)->unk_46 &= 0x7FFF;
        goto end;
    }
    D_800E3DE8[0] = (u8 *)arg3 - 0x20;

end:
    return;
}
