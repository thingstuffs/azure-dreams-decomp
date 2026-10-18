#include "modules/dungeon_ovl_184c800.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

/* cfail-repair: tf7-phase1-cache-v3 */

/* Advance motion with damping and downward acceleration, then count down or fade the effect. */
void advance_motion_damping_downward_acceleration_count_down_fade_effect(Object *object, Motion *motion, Effect *effect) {
    s16 state;
    ((s32 *)object->child)[3] |= 0x8000;
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dx -= motion->dx >> 3;
    motion->dy -= motion->dy >> 3;
    motion->dz -= func_80069EF8() * 4 + 0x4000;

    state = object->kind;
    switch (state) {
    case 0: {
        u16 ticks_left = object->count - 1;
        object->count = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            func_8004491C((u8 *)object - 0x20, func_80045340);
            object->kind++;
        }
        return;
    }
    case 1:
        func_800478B8(effect);
        if (effect->flags & 0x6000) {
            effect->pad[4] = 0;
            effect->pad[5] = 0;
        }
        {
            s32 fade_step = (func_80069EF8() & 0xF) + 4;
            if (fade_step >= effect->limit) {
                *(s32 *)((u8 *)effect + 0xC) = 0;
                *((u16 *)((u8 *)object - 2)) |= 0x8000;
                object_flag_block.flags |= 0x8000;
                return;
            } else {
                u8 fade_value = effect->value_e - fade_step;
                effect->value_e = fade_value;
                effect->value_d = fade_value;
                effect->limit = fade_value;
            }
        }
        break;
    }
}
