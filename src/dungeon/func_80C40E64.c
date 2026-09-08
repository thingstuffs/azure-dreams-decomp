#include "common.h"

typedef struct S_80172664_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172664_0;   /* arg3 in func_80172664 */

typedef struct S_80172664_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172664_1;   /* arg0 in func_80172664 */

typedef struct S_80172664_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172664_2;   /* arg2 in func_80172664 */

typedef struct S_80172664_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172664_3;   /* arg1 in func_80172664 */



extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170E7C;
extern u8 D_80174D7C;
extern u8 D_80174D84;
extern u8 D_80174D8C;

void func_80172664(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 table_x;
    s32 table_y;
    s32 table_offset;
    s32 state;
    register s32 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    table_offset = ((u16)((S_80172664_0 *)arg3)->unk_2A >> 8) & 0xE;
    table_x = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    table_y = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    ((S_80172664_1 *)arg0)->unk_96.s--;
    state = ((S_80172664_1 *)arg0)->unk_9B;

    if (state == 2) {
        goto state_2;
    }
    if ((s32)state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        goto end;
    }
    if (state == 4) {
        goto state_4;
    }
    if ((s32)state < 4) {
        goto state_3;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto end;

state_0:
    if (((S_80172664_2 *)arg2)->unk_14 & 0x8000) {
        ((S_80172664_1 *)arg0)->unk_9B = 0xFF;
        ((S_80172664_2 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80172664_0 *)arg3)->unk_2A, 1);
        goto end;
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = &D_80174D7C;
    func_80047784(
        arg2,
        *(&D_80174D7C +
          (((D_80083228 + ((S_80172664_0 *)arg3)->unk_2A + 0x100) >> 9) & 7)),
        0);
    {
        s32 shifted_x = table_x << 19;
        ((S_80172664_3 *)arg1)->unk_0C = (table_x << 17) - shifted_x;
    }
    {
        s32 shifted_y = table_y << 19;
        ((S_80172664_3 *)arg1)->unk_10 = (table_y << 17) - shifted_y;
    }
    ((S_80172664_1 *)arg0)->unk_98 |= 8;
    ((S_80172664_0 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_80172664_1 *)arg0)->unk_96.s = 4;
    ((S_80172664_3 *)arg1)->unk_14 = (s32)0xFFFC0000;
    goto increment_state;

state_1:
    ((S_80172664_1 *)arg0)->unk_90 += ((S_80172664_3 *)arg1)->unk_14;
    ((S_80172664_3 *)arg1)->unk_14 += ((S_80172664_3 *)arg1)->unk_14 >> 2;
    if (((S_80172664_1 *)arg0)->unk_96.u > 0) {
        goto end;
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = &D_80174D84;
    func_80047784(
        arg2,
        *(&D_80174D84 +
          (((D_80083228 + ((S_80172664_0 *)arg3)->unk_2A + 0x100) >> 9) & 7)),
        0);
    next_state = ((S_80172664_1 *)arg0)->unk_9B;
    ((S_80172664_1 *)arg0)->unk_96.s = 8;
    goto increment_loaded_state;

state_2:
    {
        s32 value_x = ((S_80172664_3 *)arg1)->unk_0C;
        s32 value_y = ((S_80172664_3 *)arg1)->unk_10;
        s32 value_z = ((S_80172664_3 *)arg1)->unk_14;

        ((S_80172664_3 *)arg1)->unk_0C = value_x - (value_x >> 3);
        ((S_80172664_3 *)arg1)->unk_10 = value_y - (value_y >> 3);
        ((S_80172664_3 *)arg1)->unk_14 = value_z - (value_z >> 3);
    }
    if (((S_80172664_1 *)arg0)->unk_96.u == 4) {
        ((S_80172664_3 *)arg1)->unk_0C = 0;
        ((S_80172664_3 *)arg1)->unk_10 = 0;
        ((S_80172664_3 *)arg1)->unk_14 = 0;
    }
    if (((S_80172664_1 *)arg0)->unk_96.u > 0) {
        goto end;
    }
    ((S_80172664_1 *)arg0)->unk_96.s = 4;
    ((S_80172664_3 *)arg1)->unk_0C = table_x << 18;
    ((S_80172664_3 *)arg1)->unk_10 = table_y << 18;
    func_800A56E0(0x809);
    goto increment_state;

state_3:
    ((S_80172664_1 *)arg0)->unk_90 += 0xC0000;
    ((S_80172664_3 *)arg1)->unk_0C += table_x << 18;
    ((S_80172664_3 *)arg1)->unk_10 += table_y << 18;
    if (((S_80172664_1 *)arg0)->unk_96.u > 0) {
        goto end;
    }
    func_8009C12C(arg3, arg2, ((S_80172664_0 *)arg3)->unk_2A, 1);

increment_state:
    next_state = ((S_80172664_1 *)arg0)->unk_9B;
increment_loaded_state:
    ((S_80172664_1 *)arg0)->unk_9B = next_state + 1;
    goto end;

state_4:
    ((S_80172664_1 *)arg0)->unk_90 += 0xC0000;
    if (!(((S_80172664_2 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = &D_80174D8C;
    func_80047784(
        arg2,
        *(&D_80174D8C +
          (((D_80083228 + ((S_80172664_0 *)arg3)->unk_2A + 0x100) >> 9) & 7)),
        0);
    ((S_80172664_3 *)arg1)->unk_14 = 0;
    ((S_80172664_1 *)arg0)->unk_90 = 0;
    ((S_80172664_1 *)arg0)->unk_98 &= 0xFFF7;
    ((S_80172664_0 *)arg3)->unk_1C |= 0x08000000;
    ((S_80172664_1 *)arg0)->unk_9B = 0xFF;
    goto end;

state_ff:
    {
        s32 coord = ((S_80172664_2 *)arg2)->unk_24 << 6;
        s32 current = ((S_80172664_3 *)arg1)->unk_02 - 0x20;
        ((S_80172664_3 *)arg1)->unk_0C = ((coord - current) << 15) >> 1;
    }
    {
        s32 coord = ((S_80172664_2 *)arg2)->unk_25 << 6;
        s32 current = ((S_80172664_3 *)arg1)->unk_06 - 0x20;
        ((S_80172664_3 *)arg1)->unk_10 = ((coord - current) << 15) >> 1;
    }
    if (!(((S_80172664_2 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    ((S_80172664_3 *)arg1)->unk_10 = 0;
    ((S_80172664_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172664_2 *)arg2)->unk_24, ((S_80172664_2 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_80172664_1 *)arg0)->unk_8C = &D_80170E7C;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (((S_80172664_0 *)arg3)->unk_6D == 0) {
        ((S_80172664_0 *)arg3)->unk_46 &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

end:
    return;
}
