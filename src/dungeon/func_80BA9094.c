#include "modules/dungeon_ovl_bc9094.h"

Body *func_8015E894(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c) {
    s16 held_flags;
    s16 held_a;
    s32 held_c;
    s32 held_b;
    s16 arg0_copy;
    Body *body;
    Object *object;
    ChildA *child_a;
    ChildB *child_b;
    Body *body_alias;

    held_flags = spawn_flags;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    body = 0;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    arg0_copy = held_flags;
    if (object != 0) {
        body = &object->body_20;
        body->field_13 = 14;
        func_8004491C(object, func_80045340);

        child_a = object->child_a_08;
        attr_b = held_flags & 3;
        child_a->field_0A = held_c;
        child_b = object->child_b_0C;
        child_b->field_24 = held_a;
        child_b->field_25 = held_b;
        body_alias = body;

        if (attr_b == 1) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x6000;
            body->flags_1C |= 0x6000;
            child_b->field_2C = D_80162ED8;
        } else if (attr_b >= 2) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x2000;
            body->flags_1C |= 0x2000;
            child_b->field_2C = D_80162ED8;
        } else {
            if (((held_flags & ~3) << 16) == 0) {
                if (!(body->flags_14 & 0x200) && (func_800A6D30() & 1)) {
                    func_800A48F0(body, 1, (func_800A6D30() & 0x3F) | 0x20);
                    child_b->field_2C = D_80162F00;
                }
                body_alias->callback_8C = D_8015EE9C;
                child_b->field_2C = D_80162ED8;
            } else {
                body->callback_8C = D_8015EE9C;
                child_b->field_2C = D_80162ED8;
            }
        }
        object->field_10 = D_8015EA98;
        func_800A9C18(object, child_a, child_b, (s16)arg0_copy);
        body_alias->field_9A = 0xFF;
        body_alias->field_9C = -1;
        func_800AA36C(body_alias, child_a, child_b, body);
    }
    return body;
}
