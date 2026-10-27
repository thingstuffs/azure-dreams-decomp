#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/naplass/allocate_actor_effect_object.h"
#include "shared/monster_ids.h"

/* Allocates an object, initializes its parts and actor state, and returns its work area. */
/* Creates Naplass with default frames at D_80174194, applies spawn flags, and attempts valid tile
 * placement. */
void *allocate_actor_effect_object(s16 kind_flags, s16 x, s16 y, s16 part_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    register s32 primary_flags;
    register s32 secondary_flags;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;

    work = 0;
    saved_x = x;
    saved_value = part_value;
    saved_y = y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_80170A3C;
        work->species = MONSTER_NAPLASS;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value;
        part_b = obj->sprite;
        kind = kind_flags & 3;
        part_b->tile_y = saved_y;
        actor = work;
        part_b->frameTable = naplass_frame_set_1;
        part_b->tile_x = saved_x;

        if (kind == 1) {
            primary_flags = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = primary_flags;
            work->flags1C = secondary_flags;
        } else if (kind >= 2) {
            primary_flags = work->flags14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = primary_flags;
            work->flags1C = secondary_flags;
        } else {
            if (((kind_flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                work->flags1C |= ACTOR_ASLEEP;
                set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                              (generate_random_value() & 0x3F) | 0x20);
                part_b->frameTable = naplass_frame_set;
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &naplass_action_continuation_address;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
