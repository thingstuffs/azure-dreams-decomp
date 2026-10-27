#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/dragon/create_mode_configured_actor.h"
#include "shared/monster_ids.h"

/* Creates a Dragon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_mode_configured_actor_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 primary_bits;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_value_0a;
    s8 saved_byte_25;

    work = 0;
    saved_byte_24 = byte_24;
    saved_value_0a = value_0a;
    saved_byte_25 = byte_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_8016AA28;
        work->species = MONSTER_DRAGON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value_0a;
        part_b = obj->sprite;
        kind = kind_flags & 3;
        part_b->tile_y = saved_byte_25;
        actor = work;
        part_b->frameTable = D_8016DC7C;
        part_b->tile_x = saved_byte_24;

        if (kind == 1) {
            primary_bits = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = primary_bits;
            work->flags1C = secondary_flags;
        } else if (kind >= 2) {
            primary_bits = work->flags14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = primary_bits;
            work->flags1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8016DCDC;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &dragon_slot_f_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
