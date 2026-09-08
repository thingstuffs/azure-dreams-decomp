#include "common.h"

s32 func_80094B58(s32 arg0) {
    if (arg0 & 0x1000) {
        s32 temp_v0;
        s32 temp_v1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        temp_v0 = arg0 & 0x8000;
        if (temp_v0 != 0) {
            return 0xA00;
        }
        temp_v1 = arg0 & 0x2000;
        if (temp_v1 != 0) {
            return 0x600;
        }
        return 0x800;
    } else {
        s32 temp_v0;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        temp_v0 = arg0 & 0x4000;
        if (temp_v0 != 0) {
            temp_v0 = arg0 & 0x8000;
            if (temp_v0 != 0) {
                return 0xE00;
            }
            temp_v0 = arg0 & 0x2000;
            temp_v0 = temp_v0 != 0;
               /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            return temp_v0 << 9;
        } else {
            temp_v0 = arg0 & 0x8000;
            if (temp_v0 != 0) {
                return 0xC00;
            }
            if (arg0 & 0x2000) {
                return 0x400;
            }
            return -1;
        }
    }
}

/* MECHANISM: Disjoint block-local $v0 masks encode the frameless destructive reuse,
   while a short $v1 mask preserves the first arm's pending return constant.
   Split mask/boolean operations expose retail's andi+sltu and three SHAPE-C tails. */
