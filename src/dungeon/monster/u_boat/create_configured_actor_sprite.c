#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170F9C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80170F9C_1;   /* work in create_configured_actor_sprite */

typedef struct S_80170F9C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170F9C_2;   /* part_a in create_configured_actor_sprite */

typedef struct S_80170F9C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x18];
    s8 unk_B5;
} S_80170F9C_4;   /* work_copy in create_configured_actor_sprite */

extern void *allocate_list_node();
extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value(void);
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern void create_owner_linked_directional_object();

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
    S_80170F9C_1 *work;
    S_80170F9C_4 *work_copy;

    work = 0;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    mode_copy = mode;
    if (object != 0) {
        work = (u8 *)object + 0x20;
        object->update_callback = update_actor_visual_motion;
        work->unk_13 = MONSTER_U_BOAT;
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
            work->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            work->unk_14 |= ACTOR_CLASS_ENABLED;
            work->unk_1C |= ACTOR_PLAYER_SIDE;
        } else if (((mode & -4) << 16) == 0) {
            if ((work->unk_14 & ACTOR_RESIST_SLEEP) == 0) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = uboat_action_frames;
                }
            }
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, mode_copy);
        work_copy->unk_9A = 0xFF;
        work_copy->unk_9C = -1;
        work_copy->unk_8C = uboat_behavior_entry;
        work->unk_1C |= 0x40000;
        work_copy->unk_92 = -0x20;
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);

        work_copy->unk_B5 = 0;
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
