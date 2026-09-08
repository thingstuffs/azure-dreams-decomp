#include "common.h"

/* Steps toward the target angle along the shorter 12-bit arc. */
s32 func_80094AA0(s32 angle_delta, s32 target_angle, s32 step) {
    s32 wrapped_angle;
    s32 start_angle;
    s32 scratch;

    angle_delta &= 0xFFF;
    target_angle &= 0xFFF;
    if (angle_delta == target_angle) {
        goto return_arg1;
    }

    start_angle = angle_delta;
    wrapped_angle = start_angle + 0x1000;
    angle_delta = wrapped_angle - target_angle;
    angle_delta &= 0xFFF;
    if (angle_delta < 0x800) {
        angle_delta -= step;
        if (angle_delta >= 0) {
            scratch = start_angle - step;
            ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return;
        }
    } else {
        angle_delta += step;
        if (angle_delta < 0x1001) {
            return start_angle + step;
        }
    }
return_arg1:
       /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return target_angle;
}
