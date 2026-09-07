#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C5D80_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C5D80_0;   /* arg1 in func_800C5D80 */

typedef struct S_800C5D80_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800C5D80_1;   /* arg2 in func_800C5D80 */

typedef struct S_800C5D80_2 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
} S_800C5D80_2;   /* arg0 in func_800C5D80; pointer addresses record offset 0x2 */

typedef struct S_800C5D80_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C5D80_3;   /* global in func_800C5D80 */

typedef struct S_800C5D80_4 {
    s32 unk_00;
} S_800C5D80_4;   /* &D_800814A0 in func_800C5D80 */


M2C_UNK func_800478B8();                      /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;

/* Advance effect motion, fade its color, and mark it finished when its timer expires. */
void func_800C5D80(void *effect_data, S_800C5D80_0 *motion, S_800C5D80_1 *primitive) {
    s16 ticks_left;
    u8 brightness;

    motion->unk_08 += motion->unk_14;
    motion->unk_14 += 0x2000;
    func_800478B8(primitive);
    brightness = primitive->unk_0C - ((s32) primitive->unk_0C / (s16) ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12);
    primitive->unk_0C = brightness;
    primitive->unk_0D = brightness;
    primitive->unk_0E = brightness;
    ticks_left = (u16) ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12 - 1;
    ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        if (((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_0E == 0) {
            S_800C5D80_3 *effect_counts = &D_80083460;

            effect_counts->unk_0A = (u16) (effect_counts->unk_0A - 1);
        }
        ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_00 | 0x8000);
        ((S_800C5D80_4 *)(&D_800814A0))->unk_00 = (s32) (((S_800C5D80_4 *)(&D_800814A0))->unk_00 | 0x8000);
    }
}

/* MECHANISM: Separate compound RMWs preserve retail's shared +0x14 load and v1 copy.
   A named D_80083460 base keeps +0xA as a displacement; the corrected u8 quotient
   expression restores the divide sequence, with cdk-G0 providing the retail schedule. */
