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
extern u8 D_801713A8[];
void dispatch_actor_animation_and_action(ActorRecord *motion_in, ObjectPosition *context_in, SpriteFrameState *entity_in, ActorRecord *actor_in);
extern u8 death_direction_frames[];
extern u8 death_frame_set_2[];

/* Creates a Death actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_configured_actor_object(s16 flags, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;

    work = 0;
    saved_arg1 = value_24;
    saved_arg3 = value_0A;
    saved_arg2 = value_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_801713A8;
        work->species = MONSTER_DEATH;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_arg3;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_arg2;
        actor = work;
        part_b->frameTable = death_direction_frames;
        part_b->tile_x = saved_arg1;

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
        } else if (((flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
            if (generate_random_value() & 1) {
                set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                              (generate_random_value() & 0x3F) | 0x20);
                part_b->frameTable = death_frame_set_2;
            }
        }
        initialize_actor_sprite_and_animation(((void *)(obj)), part_a, part_b, flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.handler = &dispatch_actor_animation_and_action;
        work->flags1C |= 0x40000;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

/* MECHANISM: Preserve the seed's exact 0x38 frame, s0-s7 holds, CFG, and true-base name.
   The sole residue was part_b's saved_arg1 byte field at 0xF versus retail offset 0x24.
   part_b->unk_24 closes the substitution at emitted word 32. */
