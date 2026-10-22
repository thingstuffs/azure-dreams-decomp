#include "dungeon/monster/nyuel/allocate_actor_parts.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/nyuel/allocate_actor_parts.h"

/* Creates a Nyuel actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
Body *allocate_actor_parts(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c) {
    s16 held_flags;
    s16 held_a;
    s32 held_c;
    s32 held_b;
    s16 arg0_copy;
    Body *body;
    Object *object;
    ChildA *child_a;
    SpriteFrameState *child_b;
    Body *body_alias;

    held_flags = spawn_flags;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    body = 0;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    arg0_copy = held_flags;
    if (object != 0) {
        body = &object->body_20;
        body->field_13 = 14;
        register_node(object, project_sprite_chain);

        child_a = object->child_a_08;
        attr_b = held_flags & 3;
        child_a->field_0A = held_c;
        child_b = object->child_b_0C;
        child_b->unk_24 = held_a;
        child_b->unk_25 = held_b;
        body_alias = body;

        if (attr_b == 1) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x6000;
            body->flags_1C |= 0x6000;
            child_b->frameTable = D_80162ED8;
        } else if (attr_b >= 2) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x2000;
            body->flags_1C |= 0x2000;
            child_b->frameTable = D_80162ED8;
        } else {
            if (((held_flags & ~3) << 16) == 0) {
                if (!(body->flags_14 & 0x200) && (generate_random_value() & 1)) {
                    set_or_clear_actor_status_slot(body, 1, (generate_random_value() & 0x3F) | 0x20);
                    child_b->frameTable = D_80162F00;
                }
                body_alias->callback_8C = D_8015EE9C;
                child_b->frameTable = D_80162ED8;
            } else {
                body->callback_8C = D_8015EE9C;
                child_b->frameTable = D_80162ED8;
            }
        }
        object->field_10 = D_8015EA98;
        initialize_actor_sprite_and_animation(object, child_a, child_b, (s16)arg0_copy);
        body_alias->field_9A = 0xFF;
        body_alias->field_9C = -1;
        try_move_actor_to_valid_position(body_alias, child_a, child_b, body);
    }
    return body;
}
