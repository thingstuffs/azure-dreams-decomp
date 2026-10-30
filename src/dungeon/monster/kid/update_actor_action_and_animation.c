#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/kid.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80174218(void *, void *, void *, void *);

extern u8 kid_action_resume_address[];
extern u8 kid_direction_frames[];
extern u8 kid_alt_spawn_direction_frames[];
extern u8 kid_frame_set_4[];

typedef struct S_80173A2C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80173A2C_0;   /* arg0 in update_actor_action_and_animation */

/* Updates an actor's action state and animation before restoring its default callback. */
void update_actor_action_and_animation(void *controller_in, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 actor_flags;
    u16 ticks_left;
    s32 state;

    state = ((S_80173A2C_0 *)controller_in)->unk_9B;
    switch (state) {
    case 0:
        ((S_80173A2C_0 *)controller_in)->unk_90 += 0x100000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = kid_alt_spawn_direction_frames;
        actor = (ActorRecord *)((u8 *)actor + 0x2A);
        select_sprite_entry(sprite,
            kid_alt_spawn_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)actor + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((S_80173A2C_0 *)controller_in)->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) == 0) {
            sprite->frameTable = kid_frame_set_4;
            select_sprite_entry(sprite,
                kid_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (sprite->flags & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                controller_in = (u8 *)controller_in + 0x8C;
                *(void **)controller_in = kid_action_resume_address;
                return;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (actor->hp_delta != 0) {
                if (begin_ready_actor_directional_action(controller_in, motion, sprite, 0) != 0) {
                    return;
                }
            }
            if (actor->mp_value.parts.whole == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(controller_in, motion, sprite, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            actor_flags = actor->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(controller_in, motion, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(controller_in, motion, sprite, actor);
                ((S_80173A2C_0 *)controller_in)->unk_A8 = 0;
                func_80174218(controller_in, motion, sprite, actor);
                return;
            }
            if (actor->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                {
                    void *current_body;
                    ActorRecord *current_actor;
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    current_body = actor;
                    current_actor = current_body;
                    previous_node = owner->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(current_actor,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&sprite->room_index;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
            sprite->frameTable = kid_frame_set_4;
            select_sprite_entry(sprite,
                kid_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (sprite->flags & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                controller_in = (u8 *)controller_in + 0x8C;
                *(void **)controller_in = kid_action_resume_address;
                return;
            }
        }
        ((S_80173A2C_0 *)controller_in)->unk_96 = 3;
        ((S_80173A2C_0 *)controller_in)->unk_98 &= 0xBFFF;
        {

            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }
        ((S_80173A2C_0 *)controller_in)->unk_9B++;
        return;

    case 2:
        ticks_left = ((S_80173A2C_0 *)controller_in)->unk_96 - 1;
        ((S_80173A2C_0 *)controller_in)->unk_96 = ticks_left;
        if ((ticks_left << 16) <= 0) {
            ((S_80173A2C_0 *)controller_in)->unk_98 |= 0x4000;
            motion->velocity_z = 0xFFEC0000;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        ((S_80173A2C_0 *)controller_in)->unk_A8 = 0;
        sprite->frameTable = kid_direction_frames;
        select_sprite_entry(sprite,
            kid_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags1C &= ~ACTOR_ASLEEP;

        controller_in = (u8 *)controller_in + 0x8C;
        *(void **)controller_in = kid_action_resume_address;

        return;
    }
}
