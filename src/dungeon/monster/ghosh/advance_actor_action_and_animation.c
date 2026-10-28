#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void select_sprite_entry(void *, s32, s32);
s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
s32 generate_random_value(void);
void on_actor_status_updated(void *);
void update_actor_status_and_mp(ActorRecord *entity);
void begin_pushed_actor_move(void *,void *, void *, void *);
s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void func_8016DAA4(void *, s32, void *, void *);

extern u8 ghosh_action_resume_address[];
extern u8 ghosh_frame_set_12[];
extern u8 D_801746AC[];
#include "dungeon/monster/ghosh.h"
extern u8 resident_globals_page[];

typedef struct S_8016D6F0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x18];
    u8 unk_B4;
} S_8016D6F0_0;   /* arg0 in advance_actor_action_and_animation */

typedef struct S_8016D6F0_2 {
    u8 pad_00[0x14A8];
    u8 * unk_14A8;
    u8 pad_14AC[0x1D7C];
    s16 unk_3228;
    u8 pad_322A[0x238];
    u16 unk_3462;
} S_8016D6F0_2;   /* base8008 in advance_actor_action_and_animation */

typedef struct S_8016D6F0_5 {
    u8 pad_00[0x3714];
    u16 unk_3714;
} S_8016D6F0_5;   /* base8001 in advance_actor_action_and_animation */

typedef struct S_8016D6F0_9 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8016D6F0_9;   /* ((S_8016D6F0_2 *)base8008)->unk_14A8 in advance_actor_action_and_animation */

/* Advance the actor's action state, directional animation, and completion callback. */
void advance_actor_action_and_animation(S_8016D6F0_0 *actor, void *actor_id, SpriteFrameState *sprite, ActorRecord *entity)
{
    TileObject *reference_pos;
    DungeonGlobalStatus *counter_base;
    S_8016D6F0_5 *flags_page;
    DungeonGlobalStatus *reference_base;
    void *action_actor;
    s32 state;
    s32 entity_flags;
    s32 action_flag;
    s8 room_id;

    state = actor->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        {
            u8 *dir_table = ghosh_frame_set_12;
            sprite->frameTable = dir_table;
            select_sprite_entry(
                sprite,
                dir_table[((g_game_work.view.camera_rotation.parts.viewAngle +
                            entity->facing + 0x100) >> 9) & 7],
                0);
        }
        counter_base = &g_dungeon_status;
        counter_base->activity_counts.parts.pending_action_count--;
        actor->unk_9B++;
        return;
    case 1:
        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 0x10) != 0) {
            if (((S_8016D6F0_2 *)resident_globals_page)->unk_3462 & 0x1000) {
                return;
            }
            flags_page = (S_8016D6F0_5 *)0x80010000;
            if (actor->unk_B4 == 0 && !(flags_page->unk_3714 & 8)) {
                if (entity->hp_delta != 0) {
                    if (begin_ready_actor_directional_action(actor, actor_id, sprite, ghosh_ready_action_frames) != 0) {
                        return;
                    }
                }
            } else if (entity->hp_delta != 0) {
                reference_base = &g_dungeon_status;
                if ((reference_base->pending_display_owner) ==
                    (u8 *)entity - 0x20) {
                    (*(s32 *)&reference_base->pending_display_owner) &= 0x7FFFFFFF;
                }
            }
            if ((has_pending_actor_or_turn_action(entity) << 0x10) != 0) {
                return;
            }
            entity_flags = entity->flags1C;
            action_flag = entity_flags & 0x100;
            action_actor = actor;
            if (action_flag) {
                begin_pushed_actor_move(action_actor, actor_id, sprite, entity);
                return;
            }
            if (entity_flags & 0x80000) {
                begin_actor_move_to_target_facing(action_actor, actor_id, sprite, entity);
                func_8016DAA4(actor, actor_id, sprite, entity);
                return;
            }
            if (entity->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(entity) << 0x10) != 0) {
                if ((check_entity_relation(
                         entity,
                         ((S_8016D6F0_9 *)(((S_8016D6F0_2 *)resident_globals_page)->unk_14A8))->unk_58 + 0x20)
                     << 0x10) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(entity);
            on_actor_status_updated(entity);
            if ((get_entity_effect_value(entity, STATUS_SLEEP) << 0x10) != 0) {
                reference_pos = &reference_tile_object;
                room_id = *(s8 *)&sprite->room_index;
                if (((room_id == reference_pos->room_index && room_id >= 0) ||
                     get_tile_chebyshev_distance(reference_pos, sprite) < 2) &&
                    (generate_random_value() & 7) == 0) {
                    clear_slots_of_type(entity, STATUS_SLEEP);
                }
            }
            if ((get_entity_effect_value(entity, STATUS_SLEEP) << 0x10) != 0) {
                return;
            }
        }
        {
            u8 *dir_table = D_801746AC;
            sprite->frameTable = dir_table;
            select_sprite_entry(
                sprite,
                dir_table[((g_game_work.view.camera_rotation.parts.viewAngle +
                            entity->facing + 0x100) >> 9) & 7],
                0);
        }
        if (sprite->flags & 0x8000) {
            actor->unk_8C = ghosh_action_resume_address;
            return;
        }
        {
            DungeonGlobalStatus *counter_update = &g_dungeon_status;
            counter_update->activity_counts.parts.pending_action_count++;
        }
        actor->unk_9B++;
        return;
    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *counter_update = &g_dungeon_status;
            counter_update->activity_counts.parts.pending_action_count--;
        }
        actor->unk_8C = ghosh_action_resume_address;
        break;
    default:
        return;
    }
}
