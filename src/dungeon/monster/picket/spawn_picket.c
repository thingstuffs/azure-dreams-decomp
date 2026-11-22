#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "dungeon/monster/picket.h"
#include "dungeon/monster/picket_frames.h"




extern u8 D_80170CC8[];

/*
 * Spawns a Picket actor on its 0x112 node: sets its default frames, applies the side flags the low
 * two bits of the spawn flags select (or a random sleep status when none are set), then moves it
 * to a valid tile.
 */
void *spawn_picket(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = NODE_BODY(obj);
        obj->update_callback = D_80170CC8;
        work->species = MONSTER_PICKET;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_variant;
        actor = work;
        part_b->frameTable = picket_frame_set_1;
        part_b->tile_x = saved_kind_id;

        if (kind == 1) {
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
        } else if (kind >= 2) {
            left = work->flags14 | ACTOR_CLASS_ENABLED;
            right = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = left;
            work->flags1C = right;
        } else {
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                call_a1 = part_a;
                left = generate_random_value();
                call_a1 = obj;
                if (left & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = picket_frame_set_6;
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->action_id = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.handler = &update_picket_behavior;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
