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
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);

extern u8 uboat_default_frames[];
extern u8 uboat_action_frames[];

#include "dungeon/monster/u_boat.h"

/* Creates a U-Boat actor, initializes its status and tile placement, and creates a linked directional
 * display. */
void *create_configured_actor_sprite(s16 mode, s16 value_24, s16 value_25, s16 value_0A)
{
    s8 held_value_24 = value_24;
    s16 held_value_0A = value_0A;
    s8 held_value_25 = value_25;
    s16 mode_copy;
    s32 kind;
    u16 saved_x;
    u16 saved_y;
    ObjectNodeHeader *object;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *work_copy;

    work = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    mode_copy = mode;
    if (object != 0) {
        work = (ActorRecord *)(object + 1);
        object->update_callback = update_actor_visual_motion;
        work->species = MONSTER_U_BOAT;
        register_node(object, project_sprite_chain);

        part_a = object->position;
        kind = mode & 3;
        part_a->z.w.i = held_value_0A;
        part_b = object->sprite;
        work_copy = work;
        part_b->frameTable = uboat_default_frames;
        part_b->tile_x = held_value_24;
        part_b->tile_y = held_value_25;

        if (kind == 1) {
            work->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            work->flags14 |= ACTOR_CLASS_ENABLED;
            work->flags1C |= ACTOR_PLAYER_SIDE;
        } else if (((mode & -4) << 16) == 0) {
            if ((work->flags14 & ACTOR_RESIST_SLEEP) == 0) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = uboat_action_frames;
                }
            }
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, mode_copy);
        work_copy->action_id.u = 0xFF;
        work_copy->unk_9C = -1;
        work_copy->unk_8C.address = uboat_behavior_entry;
        work->flags1C |= 0x40000;
        work_copy->unk_90.parts.high.s = -0x20;
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);

        work_copy->pad_B4[1] = 0; /* BYTES: action scratch byte at +0xB5. */
        saved_x = part_b->scale_x;
        saved_y = part_b->scale_y;
        part_b->scale_x = 0;
        part_b->scale_y = 0;
        create_owner_linked_directional_object(work_copy, part_a, part_b);
        part_b->scale_x = saved_x;
        part_b->scale_y = saved_y;
    }

    return work;
}

/* MECHANISM: Ordered value_24/value_0A/value_25 homes plus an s5 part_a base reproduce the 0x38 frame
   and retail save/hold set; both generate_random_value sites are zero-argument RNG calls, leaving their
   delay slots as nops. */
