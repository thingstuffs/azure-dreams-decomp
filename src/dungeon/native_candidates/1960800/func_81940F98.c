#include "modules/dungeon_ovl_1960800.h"
#include "common.h"





extern s32 rand(void);

/* Spawn and initialize an object at a randomized offset from its parent. */
void func_80024798(Object *source, s32 state_14_value, s32 state_08_value, s32 state_32_value,
                   s16 x_offset, s16 y_offset, s16 z_offset) {
    Object *parent = source;
    s16 held_x_offset = x_offset;
    s16 held_y_offset = y_offset;
    s16 held_z_offset = z_offset;
    s32 state_14 = state_14_value;
    Object *spawned;
    Data *position;
    u8 *state;
    s32 jitter;

    spawned = (Object *)func_8003FD64(0x211, (ObjectNodeHeader **)parent);
    if (spawned != 0) {
        spawned->callback = func_80024734;
        jitter = rand();
        spawned->data->x =
            parent->data->x +
            (jitter & 0xF) + (held_x_offset - 8);
        jitter = rand();
        spawned->data->y =
            parent->data->y +
            (jitter & 0xF) + (held_y_offset - 8);
        state = (u8 *)spawned + 0x20;
        jitter = rand();
        position = spawned->data;
        position->z =
            parent->data->z +
            (jitter & 0x1F) + (held_z_offset - 0x10);
        *(s16 *)(state + 0x14) = state_14;
        *(s16 *)(state + 0x32) = state_32_value;
        func_8004491C(spawned, (s32)func_800244E4);
        *(s32 *)(state + 8) = state_08_value;
    }
}
