#include "common.h"


typedef struct OffsetPair {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern s16 D_80083228;
extern s32 D_8008346C;
extern OffsetTable D_80170884;
extern s32 D_80171728;
extern u8 D_80174DEC[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801745BC(void *, s32, s32, s32);
extern void func_80174800(void *, s32, s32, s32);


typedef struct S_80174A28_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174A28_0;   /* arg0 in func_80174A28 */

typedef struct S_80174A28_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A28_1;   /* arg1 in func_80174A28 */

typedef struct S_80174A28_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174A28_2;   /* arg2 in func_80174A28 */

typedef struct S_80174A28_3 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_80174A28_3;   /* arg3 in func_80174A28 */

void func_80174A28(void *arg0, void *arg1, void *arg2, void *arg3)
{
    OffsetTable offsets = D_80170884;

    switch (((S_80174A28_0 *)arg0)->unk_9B) {
    case 0:
        ((S_80174A28_1 *)arg1)->unk_14 = 0;
        ((S_80174A28_1 *)arg1)->unk_10 = 0;
        ((S_80174A28_1 *)arg1)->unk_0C = 0;
        ((S_80174A28_0 *)arg0)->unk_96 = 0x14;
        ((S_80174A28_0 *)arg0)->unk_9B++;
        break;

    case 1:
        if ((--((S_80174A28_0 *)arg0)->unk_96 == 0x12) ||
            (((S_80174A28_2 *)arg2)->unk_14 & 0x8000)) {
            OffsetPair *offset;
            u16 flags;
            s32 height;
            s32 x;
            s32 x_sum;
            s32 x_raw;
            s32 off_x;
            register s32 y_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 scratch ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register void *call_arg0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            flags = ((S_80174A28_2 *)arg2)->unk_14;
            call_arg0 = arg3;
            ((S_80174A28_2 *)arg2)->unk_14 = flags | 0x0800;
            height = ((S_80174A28_1 *)arg1)->unk_0A;
            x_raw = ((S_80174A28_2 *)arg2)->unk_24;
            offset = &offsets.entries[(((S_80174A28_3 *)arg3)->unk_2A.u >> 9) & 7];
            off_x = offset->x;
            x_sum = x_raw + off_x;
            y_offset = offset->y;
            ASM_USE(y_offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            x = x_sum & 0xFFFF;
            scratch = ((S_80174A28_2 *)arg2)->unk_25 + y_offset;
            func_80174800(call_arg0, x, scratch & 0xFFFF, height);
        }
        if ((((S_80174A28_0 *)arg0)->unk_96 == 0x0A) ||
            (((S_80174A28_2 *)arg2)->unk_14 & 0x8000)) {
            ((S_80174A28_2 *)arg2)->unk_14 &= 0xF7FF;
            func_800A56E0(0x605);
        }
        if ((((S_80174A28_0 *)arg0)->unk_96 == 9) ||
            (((S_80174A28_2 *)arg2)->unk_14 & 0x8000)) {
            OffsetPair *offset;
            u16 angle;
            s32 height;
            s32 x_raw;
            s32 x;
            s32 x_sum;
            s32 y_offset;
            s32 scratch;

            angle = ((S_80174A28_3 *)arg3)->unk_2A.u;
            offset = offsets.entries + ((angle >> 9) & 7);
            height = ((S_80174A28_1 *)arg1)->unk_0A;
            x_raw = ((S_80174A28_2 *)arg2)->unk_24;
            scratch = offset->x;
            x_sum = x_raw + scratch;
            y_offset = offset->y;
            scratch = ((S_80174A28_2 *)arg2)->unk_25 + y_offset;
            x = x_sum & 0xFFFF;
            func_801745BC(arg3, x, scratch & 0xFFFF, height);
        }
        if ((((S_80174A28_0 *)arg0)->unk_96 <= 0) ||
            (((S_80174A28_2 *)arg2)->unk_14 & 0x8000)) {
            ((S_80174A28_0 *)arg0)->unk_96 = 0;
            ((S_80174A28_0 *)arg0)->unk_9B++;
        }
        break;

    case 2:
        if (((S_80174A28_2 *)arg2)->unk_14 & 0xE000) {
            ((S_80174A28_1 *)arg1)->unk_14 = 0;
            ((S_80174A28_1 *)arg1)->unk_10 = 0;
            ((S_80174A28_1 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1,
                ((S_80174A28_2 *)arg2)->unk_24, ((S_80174A28_2 *)arg2)->unk_25);
            if (((S_80174A28_2 *)arg2)->unk_2C != D_80174DEC) {
                ((S_80174A28_2 *)arg2)->unk_2C = D_80174DEC;
                ((S_80174A28_2 *)arg2)->unk_14 &= 0xF7FF;
                func_80047784(arg2,
                    ((S_80174A28_2 *)arg2)->unk_2C[((D_80083228 +
                        ((S_80174A28_3 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                ((S_80174A28_0 *)arg0)->unk_9B++;
            }
        }
        break;

    case 3:
        func_800AD594(arg3, 0x400);
        ((S_80174A28_0 *)arg0)->unk_8C = &D_80171728;
        D_8008346C = 0;
        (*(u16 *)((u8 *)arg3 + (0x46))) &= 0x7FFF;
        break;
    }
}
