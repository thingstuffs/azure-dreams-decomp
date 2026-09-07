#include "common.h"

typedef struct S_80174898_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174898_0;   /* arg0 in func_80174898 */

typedef struct S_80174898_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174898_1;   /* arg1 in func_80174898 */

typedef struct S_80174898_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174898_2;   /* arg2 in func_80174898 */

typedef struct S_80174898_3 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
} S_80174898_3;   /* arg3 in func_80174898 */



typedef struct OffsetPair {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern s16 D_80083228;
extern s32 D_8008346C;
extern OffsetTable D_80170854;
extern s32 D_801717F4;
extern u8 D_80175988[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8017442C(void *, s32, s32, s32);
extern void func_80174670(void *, s32, s32, s32);

void func_80174898(void *arg0, void *arg1, void *arg2, void *arg3)
{
    OffsetTable offsets = D_80170854;
    s32 scratch;

    switch (((S_80174898_0 *)arg0)->unk_9B) {
    case 0:
        ((S_80174898_1 *)arg1)->unk_14 = 0;
        ((S_80174898_1 *)arg1)->unk_10 = 0;
        ((S_80174898_1 *)arg1)->unk_0C = 0;
        ((S_80174898_0 *)arg0)->unk_96 = 0x14;
        ((S_80174898_0 *)arg0)->unk_9B++;
        break;

    case 1:
        if ((--((S_80174898_0 *)arg0)->unk_96 == 0x11) ||
            (((S_80174898_2 *)arg2)->unk_14 & 0x8000)) {
            OffsetPair *offset;
            u16 flags;
            s32 height;
            s32 x_sum;
            s32 x_raw;
            s32 y_offset;
            s32 ox;

            flags = ((S_80174898_2 *)arg2)->unk_14;
            ((S_80174898_2 *)arg2)->unk_14 = flags | 0x0800;
            height = ((S_80174898_1 *)arg1)->unk_0A;
            x_raw = ((S_80174898_2 *)arg2)->unk_24;
            offset = &offsets.entries[(((S_80174898_3 *)arg3)->unk_2A.s >> 9) & 7];
            ox = offset->x;
            x_sum = x_raw + ox;
            y_offset = offset->y;
            scratch = ((S_80174898_2 *)arg2)->unk_25 + y_offset;
            x_sum = x_sum & 0xFFFF;
            func_80174670(arg3, x_sum, scratch & 0xFFFF, height);
        }
        if ((((S_80174898_0 *)arg0)->unk_96 == 0x0A) ||
            (((S_80174898_2 *)arg2)->unk_14 & 0x8000)) {
            ((S_80174898_2 *)arg2)->unk_14 &= 0xF7FF;
            func_800A56E0(0x606);
        }
        if ((((S_80174898_0 *)arg0)->unk_96 == 9) ||
            (((S_80174898_2 *)arg2)->unk_14 & 0x8000)) {
            OffsetPair *offset;
            u16 angle;
            s32 height;
            s32 x_raw;
            s32 x;
            s32 x_sum;
            s32 y_offset;

            angle = ((S_80174898_3 *)arg3)->unk_2A.s;
            offset = offsets.entries + ((angle >> 9) & 7);
            height = ((S_80174898_1 *)arg1)->unk_0A;
            x_raw = ((S_80174898_2 *)arg2)->unk_24;
            scratch = offset->x;
            x_sum = x_raw + scratch;
            y_offset = offset->y;
            scratch = ((S_80174898_2 *)arg2)->unk_25 + y_offset;
            x = x_sum & 0xFFFF;
            func_8017442C(arg3, x, scratch & 0xFFFF, height);
        }
        if ((((S_80174898_0 *)arg0)->unk_96 <= 0) ||
            (((S_80174898_2 *)arg2)->unk_14 & 0x8000)) {
            ((S_80174898_0 *)arg0)->unk_96 = 0;
            ((S_80174898_0 *)arg0)->unk_9B++;
        }
        break;

    case 2:
        if (((S_80174898_2 *)arg2)->unk_14 & 0xE000) {
            ((S_80174898_1 *)arg1)->unk_14 = 0;
            ((S_80174898_1 *)arg1)->unk_10 = 0;
            ((S_80174898_1 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1,
                ((S_80174898_2 *)arg2)->unk_24, ((S_80174898_2 *)arg2)->unk_25);
            if (((S_80174898_2 *)arg2)->unk_2C != D_80175988) {
                ((S_80174898_2 *)arg2)->unk_2C = D_80175988;
                ((S_80174898_2 *)arg2)->unk_14 &= 0xF7FF;
                func_80047784(arg2,
                    ((S_80174898_2 *)arg2)->unk_2C[((D_80083228 +
                        ((S_80174898_3 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
                    0);
                ((S_80174898_0 *)arg0)->unk_9B++;
            }
        }
        break;

    case 3:
        func_800AD594(arg3, 0x400);
        ((S_80174898_0 *)arg0)->unk_8C = &D_801717F4;
        D_8008346C = 0;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        break;
    }
}

