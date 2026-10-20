#include "modules/dungeon_ovl_9c32d4.h"

void spawn_randomized_directional_motion_object(ovl_9c32d4_809A37C0_MotionObject *parent, s16 direction, s32 value) {
    ovl_9c32d4_809A37C0_MotionObject *object;
    ovl_9c32d4_809A37C0_MotionDraw *draw;
    ovl_9c32d4_809A37C0_MotionState *state;
    object = allocate_list_node(0x212, parent);
    if (object != 0) {
        object->update = advance_directional_effect_motion;
        register_node(object, project_sprite_chain);
        object->position->x.ovl_9c32d4_809A37C0_half.high = parent->position->x.ovl_9c32d4_809A37C0_half.high + (func_80069EF8() & 0x3F) - 0x20;
        object->position->y.ovl_9c32d4_809A37C0_half.high = parent->position->y.ovl_9c32d4_809A37C0_half.high + (func_80069EF8() & 0x3F) - 0x20;
        object->position->z.ovl_9c32d4_809A37C0_half.high = parent->position->z.ovl_9c32d4_809A37C0_half.high + (func_80069EF8() & 0x3F) - 0x20;
        draw = object->draw;
        state = &object->state;
        draw->resource = D_80175F9C;
        draw->scale_x = draw->scale_y = 0x1000;
        draw->value = value;
        draw->count = 8;
        state->direction = direction;
        state->speed = (func_80069EF8() & 0xFF) | 0x80;
    }
}
