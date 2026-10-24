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
    ProjectileObject *obj;
    SignedHeightView *part_a;
    S_8016A854_3 *part_b;
    S_8016A854_1 *work;
    S_8016A854_4 *actor;
    s32 primary_bits;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_value_0a;
    s8 saved_byte_25;

    work = 0;
    saved_byte_24 = byte_24;
    saved_value_0a = value_0a;
    saved_byte_25 = byte_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8016AA28;
        work->unk_13 = MONSTER_DRAGON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z = saved_value_0a;
        part_b = obj->sprite;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_byte_25;
        actor = work;
        part_b->unk_2C = D_8016DC7C;
        part_b->unk_24 = saved_byte_24;

        if (kind == 1) {
            primary_bits = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = primary_bits;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            primary_bits = work->unk_14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = primary_bits;
            work->unk_1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8016DCDC;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &dragon_slot_f_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
