#include "common.h"

extern s16 D_80083780[];
extern u16 D_800E58F8[];
extern void func_800C77D0(void *, void *, s16, s32);

/* Sets up the object at the supplied position if both planar distances are at most 192. */
void func_800C78A0(s32 object, s32 x, s32 y, s32 height, s32 mode, s32 settings)
{
    s32 distance;
    s32 saved_mode;

    saved_mode = mode;
    distance = D_80083780[1] - x;
    ASM_KEEP(saved_mode);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 193) {
        distance = D_80083780[3] - y;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 193) {
            u16 *position = D_800E58F8;

            position[1] = x;
            position[3] = y;
            position[5] = height;
            func_800C77D0((void *)object, position, (s16)saved_mode, settings);
        }
    }
}
