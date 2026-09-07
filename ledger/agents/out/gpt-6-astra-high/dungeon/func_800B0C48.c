#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B63A8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B63A8_0;   /* arg1 in func_800B63A8 */

typedef struct S_800B63A8_1_pre {
    u16 unk_00;
} S_800B63A8_1_pre;   /* the 0x2 bytes before arg0 in func_800B63A8, addressed as arg0[-1] */

typedef struct S_800B63A8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x2];
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    u8 unk_14;
    u8 pad_15[0x1];
    u8 unk_16;
    u8 pad_17[0x1];
    u8 unk_18;
} S_800B63A8_1;   /* arg0 in func_800B63A8 */

typedef struct S_800B63A8_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800B63A8_2;   /* arg2 in func_800B63A8 */


M2C_UNK func_800478B8();            /* extern */
extern M2C_UNK D_800814A0;

/* Advance effect motion, fade its color, and flag it when its lifetime expires. */
void func_800B63A8(void *effect, void *motion, void *primitive) {
    s32 velocity_y;
    s32 velocity_z;
    s32 accel_z_step;
    u16 life_left;
    u8 faded_red;
    u8 faded_green;
    u8 faded_blue;
    u8 red;
    u8 green;
    u8 blue;

    ((S_800B63A8_0 *)motion)->unk_0C = (s32) (((S_800B63A8_0 *)motion)->unk_0C + ((S_800B63A8_1 *)effect)->unk_00);
    ((S_800B63A8_0 *)motion)->unk_10 = (s32) (((S_800B63A8_0 *)motion)->unk_10 + ((S_800B63A8_1 *)effect)->unk_04);
    accel_z_step = ((S_800B63A8_1 *)effect)->unk_08 * ((S_800B63A8_1 *)effect)->unk_10;
    ((S_800B63A8_0 *)motion)->unk_14 = (s32) (((S_800B63A8_0 *)motion)->unk_14 + accel_z_step);
    ((S_800B63A8_1 *)effect)->unk_10 = (s16) ((u16) ((S_800B63A8_1 *)effect)->unk_10 + 1);
    velocity_y = ((S_800B63A8_0 *)motion)->unk_10;
    velocity_z = ((S_800B63A8_0 *)motion)->unk_14;
    ((S_800B63A8_0 *)motion)->unk_00 = (s32) (((S_800B63A8_0 *)motion)->unk_00 + ((S_800B63A8_0 *)motion)->unk_0C);
    ((S_800B63A8_0 *)motion)->unk_04 = (s32) (((S_800B63A8_0 *)motion)->unk_04 + velocity_y);
    ((S_800B63A8_0 *)motion)->unk_08 = (s32) (((S_800B63A8_0 *)motion)->unk_08 + velocity_z);
    func_800478B8(primitive, motion, velocity_z);
    red = ((S_800B63A8_2 *)primitive)->unk_0C;
    if (red != 0) {
        faded_red = red - ((S_800B63A8_1 *)effect)->unk_14;
        ((S_800B63A8_2 *)primitive)->unk_0C = faded_red;
        if ((u32) (faded_red & 0xFF) >= 0x81U) {
            ((S_800B63A8_2 *)primitive)->unk_0C = 0x80U;
        }
    }
    green = ((S_800B63A8_2 *)primitive)->unk_0D;
    if (green != 0) {
        faded_green = green - ((S_800B63A8_1 *)effect)->unk_16;
        ((S_800B63A8_2 *)primitive)->unk_0D = faded_green;
        if ((u32) (faded_green & 0xFF) >= 0x81U) {
            ((S_800B63A8_2 *)primitive)->unk_0D = 0x80U;
        }
    }
    blue = ((S_800B63A8_2 *)primitive)->unk_0E;
    if (blue != 0) {
        faded_blue = blue - ((S_800B63A8_1 *)effect)->unk_18;
        ((S_800B63A8_2 *)primitive)->unk_0E = faded_blue;
        if ((u32) (faded_blue & 0xFF) >= 0x81U) {
            ((S_800B63A8_2 *)primitive)->unk_0E = 0x80U;
        }
    }
    life_left = ((S_800B63A8_1 *)effect)->unk_0E - 1;
    ((S_800B63A8_1 *)effect)->unk_0E = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B63A8_1_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 = (s32) (D_800814A0 | 0x8000);
    }
}
