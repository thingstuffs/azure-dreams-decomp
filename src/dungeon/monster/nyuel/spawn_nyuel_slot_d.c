#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/nyuel/spawn_nyuel_slot_d.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"

/* Creates a Nyuel actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_nyuel(s16 spawn_flags, s16 tile_x, s32 tile_y, s32 spawn_height) {
    s16 held_flags;
    s16 held_a;
    s32 held_c;
    s32 held_b;
    s16 arg0_copy;
    ActorRecord *body;
    Object *object;
    ObjectPosition *child_a;
    SpriteFrameState *child_b;
    ActorRecord *body_alias;

    held_flags = spawn_flags;
    held_a = tile_x;
    held_c = spawn_height;
    held_b = tile_y;
    body = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    arg0_copy = held_flags;
    if (object != 0) {
        body = &object->body_20;
        body->species = 14;
        register_node(&object->header, project_sprite_chain);

        child_a = object->header.position;
        tile_y = held_flags & 3;
        child_a->z.w.i = held_c;
        child_b = object->header.sprite;
        child_b->tile_x = held_a;
        child_b->tile_y = held_b;
        body_alias = body;

        if (tile_y == 1) {
            body->unk_8C.address = nyuel_slot_d_action_callback;
            body->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            body->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            child_b->frameTable = nyuel_frame_set_7;
        } else if (tile_y >= 2) {
            body->unk_8C.address = nyuel_slot_d_action_callback;
            body->flags14 |= ACTOR_CLASS_ENABLED;
            body->flags1C |= ACTOR_PLAYER_SIDE;
            child_b->frameTable = nyuel_frame_set_7;
        } else {
            if (((held_flags & ~3) << 16) == 0) {
                if (!(body->flags14 & ACTOR_RESIST_SLEEP) && (generate_random_value() & 1)) {
                    set_or_clear_actor_status_slot(body, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    child_b->frameTable = D_80162F00;
                }
                body_alias->unk_8C.address = nyuel_slot_d_action_callback;
                child_b->frameTable = nyuel_frame_set_7;
            } else {
                body->unk_8C.address = nyuel_slot_d_action_callback;
                child_b->frameTable = nyuel_frame_set_7;
            }
        }
        object->header.update_callback = D_8015EA98;
        initialize_actor_sprite_and_animation(&object->header, child_a, child_b, (s16)arg0_copy);
        body_alias->action_id = 0xFF;
        body_alias->route_room = -1;
        try_move_actor_to_valid_position(body_alias, child_a, child_b, body);
    }
    return body;
}
