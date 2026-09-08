#include "common.h"

typedef struct S_80175C60_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175C60_0;   /* arg1_pinned in func_80175C60 */

typedef struct S_80175C60_1 {
    s16 * unk_00;
    u8 pad_04[0x1C];
    u16 unk_20;
} S_80175C60_1;   /* arg0 in func_80175C60 */

typedef struct S_80175C60_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80175C60_2;   /* arg2 in func_80175C60 */


extern s32 D_800814A0;
extern s16 D_80083228;


/* Advance motion and rotation, update facing, and flag the object when its timer expires. */
void func_80175C60(void *object, void *motion_data, void *rotation)
{
    register void *motion ASM_REG("$5") = motion_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 facing;
    s32 accel_x;
    s32 velocity_y;
    s32 next_velocity_y;
    s32 velocity_x;
    u16 ticks_left;

    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_80175C60_0 *)motion)->unk_00 += ((S_80175C60_0 *)motion)->unk_0C;
    ((S_80175C60_0 *)motion)->unk_04 += ((S_80175C60_0 *)motion)->unk_10;
    ((S_80175C60_0 *)motion)->unk_08 += ((S_80175C60_0 *)motion)->unk_14;
    velocity_x = ((S_80175C60_0 *)motion)->unk_0C;
    accel_x = velocity_x >> 5;
    velocity_y = ((S_80175C60_0 *)motion)->unk_10;
    next_velocity_y = velocity_y;
    ASM_KEEP(next_velocity_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80175C60_0 *)motion)->unk_0C = velocity_x + accel_x;
    ASM_KEEP(next_velocity_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    next_velocity_y += next_velocity_y >> 5;
    ((S_80175C60_0 *)motion)->unk_10 = next_velocity_y;
    ticks_left = ((S_80175C60_1 *)object)->unk_20 - 1;
    ((S_80175C60_1 *)object)->unk_20 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    ((S_80175C60_2 *)rotation)->unk_1C += 0x80;
    ((S_80175C60_2 *)rotation)->unk_1E += 0x80;
    ((S_80175C60_2 *)rotation)->unk_1A += 0x40;
    {
        s32 facing_test;

        facing = ((((s32)(D_80083228 + *((S_80175C60_1 *)object)->unk_00 + 0x100) >> 9) & 7) + 2) << 9;
        facing_test = facing;
        ASM_KEEP(facing_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_80175C60_2 *)rotation)->unk_18 = facing;
        if ((facing_test == 0x400) || (facing_test == 0xC00)) {
            ((S_80175C60_2 *)rotation)->unk_18 = facing + 0x100;
        }
    }
}
