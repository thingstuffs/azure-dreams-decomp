#include "modules/dungeon_ovl_9c32d4.h"

void func_80174FC0(ovl_9c32d4_809A37C0_MotionObject *parent, s16 direction, s32 value) {
    ovl_9c32d4_809A37C0_MotionObject *object;
    ovl_9c32d4_809A37C0_MotionDraw *draw;
    ovl_9c32d4_809A37C0_MotionState *state;
    object = func_8003FD64(0x212, parent);
    if (object != 0) {
        object->update = func_80174E98;
        func_8004491C(object, func_80045340);
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
