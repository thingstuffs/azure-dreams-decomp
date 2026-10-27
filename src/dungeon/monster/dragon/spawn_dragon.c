#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/dragon/spawn_variant_slot_c.h"
#include "shared/monster_ids.h"

/* Creates a Dragon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_variant_monster_slot_c(s16 mode_flags, s16 attribute_24, s16 attribute_25, s16 attribute_0a)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 flags_or_result;
    s32 secondary_flags;
    s8 saved_attribute_24;
    s16 saved_attribute_0a;
    s8 saved_attribute_25;

    work = 0;
    saved_attribute_24 = attribute_24;
    saved_attribute_0a = attribute_0a;
    saved_attribute_25 = attribute_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_80158A28;
        work->species = MONSTER_DRAGON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_attribute_0a;
        part_b = obj->sprite;
        kind = mode_flags & 3;
        part_b->tile_y = saved_attribute_25;
        actor = work;
        part_b->frameTable = D_8015BC7C;
        part_b->tile_x = saved_attribute_24;

        if (kind == 1) {
            flags_or_result = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = flags_or_result;
            work->flags1C = secondary_flags;
        } else if (kind >= 2) {
            flags_or_result = work->flags14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = flags_or_result;
            work->flags1C = secondary_flags;
        } else if (((mode_flags & ~3) << 16) == 0) {
            if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8015BCDC;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, mode_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &dragon_slot_c_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
