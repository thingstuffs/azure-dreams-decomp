#include "common.h"

typedef struct {
    s32 unk0[3];
    s32 x;
    s32 y;
} TownObject;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s16 func_80094BC8(s32, s16);
extern u8 D_80083160[];

void func_80094DA8(TownObject *arg0) {
    u8 *base;
    s16 first;
    s32 input_y;
    s32 result_x;
    s32 scaled_x;
    register s32 magnitude_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value_x;
    s32 sign_value_x;
    s32 delta_x;
    register s32 clamp_value_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 clamp_magnitude_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result_y;
    s32 scaled_y;
    register s32 magnitude_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value_y;
    s32 sign_value_y;
    s32 delta_y;
    s32 clamp_value_y;
    register s32 clamp_magnitude_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    base = D_80083160;
    first = func_80094BC8(*(s32 *)(base + 8), *(s16 *)(base + 0xC8));
    if (first != -1) {
        result_x = func_800644B8(first);
        value_x = arg0->x;
        scaled_x = result_x << 7;
        magnitude_x = scaled_x;
        if (scaled_x < 0) {
            magnitude_x = -magnitude_x;
        }
        if (value_x < 0) {
            value_x = -value_x;
        }
#ifdef __mips__
        if (!(magnitude_x < value_x)) {
            clamp_value_x = (u32)(u16)first << 16;
            goto x_done;
        }
#else
        if (magnitude_x < value_x) {
#endif
            result_x = func_800644B8(first);
            sign_value_x = arg0->x;
            delta_x = result_x << 6;
            if (((sign_value_x < 0) && (delta_x < 0)) ||
                ((sign_value_x > 0) && (delta_x > 0))) {
                arg0->x = arg0->x - delta_x;
            }
            clamp_value_x = arg0->x;
            clamp_magnitude_x = scaled_x;
            if (scaled_x < 0) {
                clamp_magnitude_x = -clamp_magnitude_x;
            }
            if (clamp_value_x < 0) {
                clamp_value_x = -clamp_value_x;
            }
            clamp_value_x = clamp_value_x < clamp_magnitude_x;
#ifdef __mips__
            __asm__ __volatile__(".set\tnoreorder\n\t.set\tnomacro");
            if (!clamp_value_x) {
                goto x_done;
            }
            clamp_value_x = (u32)(u16)first << 16;
            arg0->x = scaled_x;
            __asm__ __volatile__(".set\tmacro\n\t.set\treorder");
#else
            if (clamp_value_x) {
                arg0->x = scaled_x;
            }
            clamp_value_x = (u32)(u16)first << 16;
#endif
#ifndef __mips__
        } else {
            clamp_value_x = (u32)(u16)first << 16;
        }
#else
x_done:
#endif

        input_y = (s32)clamp_value_x >> 16;
        result_y = func_80064584(input_y);
        value_y = arg0->y;
        scaled_y = result_y << 7;
        magnitude_y = scaled_y;
        if (scaled_y < 0) {
            magnitude_y = -magnitude_y;
        }
        if (value_y < 0) {
            value_y = -value_y;
        }
        if (magnitude_y < value_y) {
            result_y = func_80064584(input_y);
            sign_value_y = arg0->y;
            delta_y = result_y << 6;
            if (((sign_value_y < 0) && (delta_y < 0)) ||
                ((sign_value_y > 0) && (delta_y > 0))) {
                arg0->y = arg0->y - delta_y;
            }
            clamp_value_y = arg0->y;
            clamp_magnitude_y = scaled_y;
            if (scaled_y < 0) {
                clamp_magnitude_y = -clamp_magnitude_y;
            }
            if (clamp_value_y < 0) {
                clamp_value_y = -clamp_value_y;
            }
            clamp_value_y = clamp_value_y < clamp_magnitude_y;
            if (clamp_value_y) {
                arg0->y = scaled_y;
            }
        }
    }
}
