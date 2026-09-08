#include "common.h"
#include "m2c_compat.h"

typedef struct S_80AC5470_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_80AC5470_0;   /* arg1 in func_80AC5470 */

typedef struct S_80AC5470_1_pre {
    u16 unk_00;
} S_80AC5470_1_pre;   /* the 0x2 bytes before arg0 in func_80AC5470, addressed as arg0[-1] */

typedef struct S_80AC5470_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    u8 pad_38[0x8];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80AC5470_1;   /* arg0 in func_80AC5470 */


extern M2C_UNK D_800814A0;

/* Updates effect motion and color fading, flagging completion near its target or at zero brightness. */
void func_80AC5470(void *effect, void *position) {
    s16 next_brightness;
    s32 motion_or_shade;
    s32 motion_or_color;
    register s32 accel_y_or_red ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 green_product;
    register s32 accel_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 target_distance;

    ((S_80AC5470_0 *)position)->unk_00.at00.v = (s32) (((S_80AC5470_0 *)position)->unk_00.at00.v + ((S_80AC5470_1 *)effect)->unk_40);
    ((S_80AC5470_0 *)position)->unk_04 = (s32) (((S_80AC5470_0 *)position)->unk_04 + ((S_80AC5470_1 *)effect)->unk_44);
    ((S_80AC5470_0 *)position)->unk_08 = (s32) (((S_80AC5470_0 *)position)->unk_08 + ((S_80AC5470_1 *)effect)->unk_48);
    motion_or_shade = ((S_80AC5470_1 *)effect)->unk_40;
    motion_or_color = ((S_80AC5470_1 *)effect)->unk_4C;
    accel_y_or_red = ((S_80AC5470_1 *)effect)->unk_50;
    accel_z = ((S_80AC5470_1 *)effect)->unk_54;
    motion_or_shade += motion_or_color;
    ((S_80AC5470_1 *)effect)->unk_40 = motion_or_shade;
    motion_or_shade = ((S_80AC5470_1 *)effect)->unk_44;
    motion_or_color = ((S_80AC5470_1 *)effect)->unk_48;
    motion_or_shade += accel_y_or_red;
    ((S_80AC5470_1 *)effect)->unk_44 = motion_or_shade;
    motion_or_shade = ((S_80AC5470_1 *)effect)->unk_36;
    motion_or_color += accel_z;
    ((S_80AC5470_1 *)effect)->unk_48 = motion_or_color;
    motion_or_color = ((S_80AC5470_0 *)position)->unk_00.at02.v;
    target_distance = motion_or_shade - motion_or_color;
    if (target_distance < 0) {
        target_distance = 0 - target_distance;
    }
    if (target_distance < 0x10) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80AC5470_1_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
    motion_or_color = ((S_80AC5470_1 *)effect)->unk_00;
    motion_or_shade = ((S_80AC5470_1 *)effect)->unk_32;
    accel_y_or_red = motion_or_color * motion_or_shade;
    if (accel_y_or_red < 0) {
        accel_y_or_red += 0xFF;
    }
    motion_or_color = ((S_80AC5470_1 *)effect)->unk_01;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    motion_or_shade = ((S_80AC5470_1 *)effect)->unk_32;
    green_product = motion_or_color * motion_or_shade;
    motion_or_shade = accel_y_or_red >> 8;
    ((S_80AC5470_1 *)effect)->unk_04.at00.v = (s8) motion_or_shade;
    if (green_product < 0) {
        green_product += 0xFF;
    }
    motion_or_color = ((S_80AC5470_1 *)effect)->unk_02;
    motion_or_shade = ((S_80AC5470_1 *)effect)->unk_32;
    motion_or_color *= motion_or_shade;
    motion_or_shade = green_product >> 8;
    ((S_80AC5470_1 *)effect)->unk_04.at01.v = (s8) motion_or_shade;
    if (motion_or_color < 0) {
        motion_or_color += 0xFF;
    }
    motion_or_shade = motion_or_color >> 8;
    ((S_80AC5470_1 *)effect)->unk_04.at02.v = (s8) motion_or_shade;
    next_brightness = (u16) ((S_80AC5470_1 *)effect)->unk_32 - 8;
    ((S_80AC5470_1 *)effect)->unk_32 = next_brightness;
    ((S_80AC5470_1 *)effect)->unk_08 = ((S_80AC5470_1 *)effect)->unk_04.at00u.v;
    if ((next_brightness << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80AC5470_1_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
