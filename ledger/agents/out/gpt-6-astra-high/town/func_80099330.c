#include "common.h"

/* Expands fixed-point bounds to include the inset rectangle. */
void func_80096A90(s32 *bounds, s16 *rect) {
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;

    left = rect[0] + rect[2];
    top = rect[1] + rect[3];
    right = left + rect[4];
    bottom = top + rect[5];
    top <<= 16;
    right <<= 16;
    bottom <<= 16;
    left = (left << 16) + 0x1FFFFF;
    top += 0x1FFFFF;
    right += 0xFFE00000;
    bottom += 0xFFEC0000;
    if (left < bounds[0]) {
        bounds[0] = left;
    }
    if (top < bounds[2]) {
        bounds[2] = top;
    }
    if (bounds[1] < right) {
        bounds[1] = right;
    }
    if (bounds[3] < bottom) {
        bounds[3] = bottom;
    }
}
