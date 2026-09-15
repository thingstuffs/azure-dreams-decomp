#include "common.h"

extern s16 D_80083780[];
extern u16 D_800E58F8[];
extern void func_800C77D0(void *, void *, s16, s32);

/* Sets up the object at the supplied position if both planar distances are at most 192. */
void func_800C78A0(s32 object, s32 x, s32 y, s32 height, s32 mode, s32 settings)
{
    s32 saved_mode;

    saved_mode = mode;
    mode = D_80083780[1] - x;
    if (mode < 0) {
        mode = -mode;
    }
    if (mode < 193) {
        mode = D_80083780[3] - y;
        if (mode < 0) {
            mode = -mode;
        }
        if (mode < 193) {
            u16 *position = D_800E58F8;

            position[1] = x;
            position[3] = y;
            position[5] = height;
            func_800C77D0((void *)object, position, (s16)saved_mode, settings);
        }
    }
}
