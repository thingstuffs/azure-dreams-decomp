#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

/* Converts directional input to an angle, optionally stepping from the current angle, and updates flags. */
s32 func_8009074C(s16 direction_offset, u16 *flags, u16 *angle) {
    s32 current_angle;
    s16 result_angle;
    s32 direction_mask;
    register s32 direction_or_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 direction_result;
    s32 angle_distance;
    u16 current_bits;
    u16 angle_bits;
    u16 updated_flags;
    u16 normalized;
    u32 input_state;
    u32 input_direction;

    input_state = ((u16)gameWork.buttons);
    result_angle = -1;
    direction_mask = input_state & 0xF000;
    if (!(input_state & 0x10)) {
        *flags &= 0xFFF;
    }
    input_direction = input_state >> 0xC;
    switch (input_direction) {
    case 2:
        if (!(*flags & direction_mask)) {
            s32 offset_angle;
            s32 relative_angle;
            offset_angle = ((s32) (direction_offset << 0x10) >> 7);
            relative_angle = 0 - offset_angle;
            result_angle = relative_angle;
        }
        goto block_19;
    case 6:
    {
        s32 relative_direction;
        s32 relative_angle;
        s32 direction_or_flags;
        direction_or_flags = (s16)direction_offset;
        relative_direction = 1 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c1;
    }
    case 4:
        if (!(*flags & direction_mask)) {
            direction_or_angle = (s16)direction_offset;
            direction_result = 2;
            direction_result = direction_result - direction_or_angle;
            result_angle = direction_result << 9;
        }
        goto block_19;
    case 12:
    {
        s32 relative_direction;
        s32 relative_angle;
        s32 direction_or_flags;
        direction_or_flags = (s16)direction_offset;
        relative_direction = 3 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c3;
    }
    case 8:
        if (!(*flags & direction_mask)) {
            direction_or_angle = (s16)direction_offset;
            direction_result = 4;
            direction_result = direction_result - direction_or_angle;
            result_angle = direction_result << 9;
        }
        goto block_19;
    case 9:
    {
        s32 relative_direction;
        s32 direction_or_flags;
        s32 relative_angle;
        direction_or_flags = (s16)direction_offset;
        relative_direction = 5 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c5;
    }
    case 1:
        if (!(*flags & direction_mask)) {
            direction_or_angle = (s16)direction_offset;
            direction_result = 6;
            direction_result = direction_result - direction_or_angle;
            result_angle = direction_result << 9;
        }
        goto block_19;
    case 3:
    {
        s32 direction_or_flags;
        s32 relative_direction;
        s32 relative_angle;
        direction_or_flags = (s16)direction_offset;
        relative_direction = 7 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c7;
    }
    default:
        updated_flags = *flags & 0xFFF;
    }
block_18_c1:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
block_18_c3:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
block_18_c5:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
block_18_c7:
block_18:
    *flags = updated_flags;
block_19:
    *flags &= 0xFBFF;
    if (angle != NULL && result_angle != -1) {
        angle_bits = *angle;
        normalized = angle_bits & 0x800;
        if (!normalized) {
            normalized = angle_bits & 0x7FF;
        } else {
            normalized = angle_bits | 0xF800;
        }
        *angle = normalized;
        normalized = result_angle & 0x800;
        if (!normalized) {
            normalized = (u16) result_angle & 0x7FF;
        } else {
            normalized = (u16) result_angle | 0xF800;
        }
        result_angle = normalized;
        current_angle = (s16) *angle;
        current_bits = *angle;
        angle_distance = current_angle - result_angle;
        if (angle_distance < 0) {
            angle_distance = 0 - angle_distance;
        }
        if (angle_distance >= 0x801) {
            u16 wrap_hi;
            u16 wrap_lo;
            wrap_hi = current_bits & 0xF000;
            wrap_lo = result_angle & 0xFFF;
            result_angle = wrap_hi | wrap_lo;
        }
        direction_result = result_angle << 0x10;
        direction_or_angle = direction_result >> 0x10;
        direction_result = current_angle < direction_or_angle;
        if (direction_result) {
            updated_flags = *flags;
            result_angle = current_bits + 0x200;
            updated_flags |= 0x400;
            *flags = updated_flags;
        } else {
            direction_result = direction_or_angle < current_angle;
            if (direction_result) {
                updated_flags = *flags;
                result_angle = current_bits - 0x200;
                updated_flags |= 0x400;
                *flags = updated_flags;
            }
        }
    }
    return result_angle & 0xFFF;
}
