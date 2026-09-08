#include "common.h"

extern s32 func_8009A350(s16 arg0, s16 arg1, s32 arg2, u16 *flags);
extern s32 func_800A41F0(void *object);
extern void *D_800E3D7C[];

/* Find an eligible object at the tile within 64 units of the target height. */
void *func_8009B390(s16 tile_x, s16 tile_y, s16 target_height)
{
    u16 flags;
    s32 height_delta;
    void *first_object;
    void *object;
    void *tile;

    if ((func_8009A350((u16)(tile_x - 1), tile_y, 0, &flags) << 16) == 0) {
        return 0;
    }
    if (!(flags & 0x3300)) {
        return 0;
    }

    object = D_800E3D7C[0];
    first_object = object;
    do {
        tile = *(void **)((u8 *)object - 0x14);
        if (*(u8 *)((u8 *)tile + 0x24) == (u16)tile_x &&
            *(u8 *)((u8 *)tile + 0x25) == (u16)tile_y) {
            height_delta = *(s16 *)((u8 *)object + 0x88) - target_height;
            if (height_delta < 0) {
                height_delta = -height_delta;
            }
            if (height_delta < 0x40 &&
                (func_800A41F0(object) << 16) != 0) {
                return object;
            }
        }
        object = (u8 *)*(void **)((u8 *)object + 0x5C) + 0x20;
    } while (object != first_object);
    return 0;
}
