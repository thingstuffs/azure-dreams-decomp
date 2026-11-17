#include "shared/entity.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/naplass/create_actor_with_kind_parts.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/naplass/create_actor_with_kind_parts.h"
#include "dungeon/monster/naplass.h"
#include "dungeon/actor.h"

/* Creates an actor and initializes its parts and flags for the requested kind. */
/* Creates Naplass with default frames at D_80150194, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_naplass(s16 spawn_flags, s16 part_b_value_24, s16 part_b_value_25, s16 part_a_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    register s32 flags_14;
    register s32 flags_1c;
    s8 saved_value_24;
    register s16 saved_part_value;
    s8 saved_value_25;

    work = 0;
    saved_value_24 = part_b_value_24;
    saved_part_value = part_a_value;
    saved_value_25 = part_b_value_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = NODE_BODY(obj);
        obj->update_callback = func_8014CA3C;
        work->species = MONSTER_NAPLASS;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_value_25;
        actor = work;
        part_b->frameTable = D_80150194;
        part_b->tile_x = saved_value_24;

        if (kind == 1) {
            flags_14 = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = flags_14;
            work->flags1C = flags_1c;
        } else if (kind >= 2) {
            flags_14 = work->flags14 | ACTOR_CLASS_ENABLED;
            flags_1c = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = flags_14;
            work->flags1C = flags_1c;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                work->flags1C |= ACTOR_ASLEEP;
                set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                              (generate_random_value() & 0x3F) | 0x20);
                part_b->frameTable = D_801501DC;
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->action_id = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &dispatch_dungeon_actor_behavior_and_facing;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
