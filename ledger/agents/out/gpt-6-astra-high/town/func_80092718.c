#include "common.h"

/* Checks whether the low 12-bit values differ by at most 511. */
s32 func_8008FE78(s32 value_a, s32 value_b) {
    return (u32) (((value_a & 0xFFF) - (value_b & 0xFFF)) + 0x1FF) < 0x3FFU;
}
