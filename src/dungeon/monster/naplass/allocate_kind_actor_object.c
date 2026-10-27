#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"




extern s32 generate_random_value(void);
extern u8 naplass_object_callback[];
extern s32 naplass_slot_f_action_callback;
extern u8 D_8016E194[];
extern u8 D_8016E1DC[];

/* Allocate an actor object and initialize its parts and flags for the requested kind. */
/* Creates Naplass with default frames at D_8016E194, applies spawn flags, and attempts valid tile
 * placement. */
void *allocate_kind_actor_object(s16 spawn_flags, s16 part_b_value_24, s16 part_b_value_25, s16 part_a_value)
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
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = naplass_object_callback;
        work->species = MONSTER_NAPLASS;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_value_25;
        actor = work;
        part_b->frameTable = D_8016E194;
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
                part_b->frameTable = D_8016E1DC;
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &naplass_slot_f_action_callback;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
