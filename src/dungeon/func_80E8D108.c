#include "common.h"


typedef struct Node Node;

typedef struct S_80172908_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172908_0;   /* arg3 in func_80172908 */

typedef struct S_80172908_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172908_1;   /* arg0 in func_80172908 */

typedef struct S_80172908_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172908_2;   /* arg2 in func_80172908 */

typedef struct S_80172908_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172908_3;   /* arg1 in func_80172908 */


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern Node *D_800E3DE8[];
extern u8 D_801710F4[];
extern u8 D_80174F30;

void func_80172908(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 one;
    s32 table_offset;
    s32 table_x;
    s32 table_y;
    u16 timer;

    table_offset = ((u16)((S_80172908_0 *)arg3)->unk_2A >> 8) & 0xE;
    table_x = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    table_y = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    state = ((S_80172908_1 *)arg0)->unk_9B;
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (!(state < 2)) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto end;

state_0:
    if (((S_80172908_2 *)arg2)->unk_14 & 0x8000) {
        ((S_80172908_1 *)arg0)->unk_9B = 0xFF;
        ((S_80172908_2 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80172908_0 *)arg3)->unk_2A, 1);
        goto end;
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = &D_80174F30;
    func_80047784(arg2,
        *(&D_80174F30 +
          (((D_80083228 + ((S_80172908_0 *)arg3)->unk_2A + 0x100) >> 9) & 7)),
        0);
    goto bump_state;

state_1:
    if ((((S_80172908_2 *)arg2)->unk_04 == state &&
         (((S_80172908_2 *)arg2)->unk_14 & 0x1000)) ||
        (((S_80172908_2 *)arg2)->unk_14 & 0x8000)) {
        func_800A56E0(0x808);
        ((S_80172908_1 *)arg0)->unk_90 = 0;
        ((S_80172908_1 *)arg0)->unk_98 |= 8;
        ((S_80172908_3 *)arg1)->unk_14 = (s32)0xFFF50000;
        ((S_80172908_1 *)arg0)->unk_96.s = 4;
        ((S_80172908_3 *)arg1)->unk_0C = (table_x << 23) / 5;
        ((S_80172908_3 *)arg1)->unk_10 = (table_y << 23) / 5;
        goto bump_state;
    }
    goto end;

bump_state:
    ((S_80172908_1 *)arg0)->unk_9B++;
    goto end;

state_2:
    timer = ((S_80172908_1 *)arg0)->unk_96.s - 1;
    ((S_80172908_1 *)arg0)->unk_96.s = timer;
    if ((s16)timer == 3) {
        func_8009C12C(arg3, arg2, ((S_80172908_0 *)arg3)->unk_2A, 1);
    }

    ((S_80172908_3 *)arg1)->unk_14 += (5 - ((S_80172908_1 *)arg0)->unk_96.u) << 16;
    if (((S_80172908_1 *)arg0)->unk_96.u < 3) {
        ((S_80172908_3 *)arg1)->unk_14 = 0;
    }
    ((S_80172908_3 *)arg1)->unk_0C -= (((S_80172908_3 *)arg1)->unk_0C << 2) / 5;
    ((S_80172908_3 *)arg1)->unk_10 -= (((S_80172908_3 *)arg1)->unk_10 << 2) / 5;
    if (((S_80172908_1 *)arg0)->unk_96.u > 0) {
        goto end;
    }
    ((S_80172908_3 *)arg1)->unk_14 = 0;
    ((S_80172908_1 *)arg0)->unk_9B = 0xFF;
    ((S_80172908_1 *)arg0)->unk_98 &= 0xFFF7;
    goto end;

state_ff:
    {
        s32 coord = ((S_80172908_2 *)arg2)->unk_24 << 6;
        s32 current = ((S_80172908_3 *)arg1)->unk_02 - 0x20;

        ((S_80172908_3 *)arg1)->unk_0C = (coord - current) << 14;
    }
    {
        s32 coord = ((S_80172908_2 *)arg2)->unk_25 << 6;
        s32 current = ((S_80172908_3 *)arg1)->unk_06 - 0x20;

        ((S_80172908_3 *)arg1)->unk_10 = (coord - current) << 14;
    }
    if (!(((S_80172908_2 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    ((S_80172908_3 *)arg1)->unk_10 = 0;
    ((S_80172908_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172908_2 *)arg2)->unk_24, ((S_80172908_2 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_80172908_1 *)arg0)->unk_8C = D_801710F4;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (((S_80172908_0 *)arg3)->unk_6D == 0) {
        ((S_80172908_0 *)arg3)->unk_46 &= 0x7FFF;
    } else {
        D_800E3DE8[0] = (Node *)((u8 *)arg3 - 0x20);
    }
end:
    return;
}
