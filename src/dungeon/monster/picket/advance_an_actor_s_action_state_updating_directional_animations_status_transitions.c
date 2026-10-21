#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_action.h"
#include "shared/sprite_frame_state.h"

   /* arg0 in advance_an_actor_s_action_state_updating_directional_animations_status_transitions */

   /* arg2 in advance_an_actor_s_action_state_updating_directional_animations_status_transitions */

typedef struct S_80173880_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173880_2;   /* arg3 in advance_an_actor_s_action_state_updating_directional_animations_status_transitions */


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80174060(void *, void *, void *, void *);

extern u8 D_801710F4[];
extern u8 D_80174F40[];
extern u8 D_80174F48[];
extern u8 D_80174F50[];

/* Advances an actor's action state, updating directional animations and status transitions. */
void advance_an_actor_s_action_state_updating_directional_animations_status_transitions(void *in_action, void *in_context, void *in_sprite, void *in_actor)
{
    void *context = in_context;
    void *actor = in_actor;
    DungeonGlobalStatus *input_state;
    s32 state;

    state = ((ActorActionStateView *)in_action)->unk_9B;
    switch (state) {
    case 0:
        if (((SpriteStatusIndexView *)in_sprite)->unk_14 & 0xE000) {
            u8 *anim_table;
            DungeonGlobalStatus *system_state;

            anim_table = D_80174F50;
            (*(void * *)((u8 *)in_sprite + 0x2C)) = anim_table;
            select_sprite_entry(in_sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_state = &g_dungeon_status;
            (*(u16 *)&system_state->activity_counts.parts.pending_action_count)--;
            ((ActorActionStateView *)in_action)->unk_9B++;
            return;
        }
        return;
    case 1:
        if (((SpriteStatusIndexView *)in_sprite)->unk_14 & 0xE000) {
            u8 *anim_table;

            anim_table = D_80174F48;
            (*(void * *)((u8 *)in_sprite + 0x2C)) = anim_table;
            select_sprite_entry(in_sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        if ((get_entity_effect_value(actor, 1) << 16) == 0) {
            {
                u8 *anim_table;

                anim_table = D_80174F50;
                (*(void * *)((u8 *)in_sprite + 0x2C)) = anim_table;
                select_sprite_entry(in_sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }

            if (((SpriteStatusIndexView *)in_sprite)->unk_14 & 0x8000) {
                break;
            }

            {
                DungeonGlobalStatus *system_state = &g_dungeon_status;

                (*(u16 *)&system_state->activity_counts.parts.pending_action_count)++;
            }
            ((ActorActionStateView *)in_action)->unk_9B++;
            return;
        }

        {
            s32 actor_flags;

            input_state = &g_dungeon_status;
            if (input_state->flags & 0x1000) {
                return;
            }

            if (((S_80173880_2 *)actor)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(in_action, context, in_sprite, 0) != 0) {
                    return;
                }
            }

            if (((S_80173880_2 *)actor)->unk_25 == 0) {
                if (input_state->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_action, context, in_sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((S_80173880_2 *)actor)->unk_1C.s;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_action, context, in_sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_action, context, in_sprite, actor);
                func_80174060(in_action, context, in_sprite, actor);
                return;
            }

            if (((S_80173880_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                        (u8 *)primary_actor_record->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &reference_tile_object;
                coordinate = ((SpriteStatusIndexView *)in_sprite)->unk_26;
                if ((((coordinate == origin->room_index) &&
                            (coordinate >= 0)) ||
                     (get_tile_chebyshev_distance(origin, in_sprite) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(actor, 1);
                }
            }

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *anim_table;

            anim_table = D_80174F50;
            (*(void * *)((u8 *)in_sprite + 0x2C)) = anim_table;
            select_sprite_entry(in_sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        if (((SpriteStatusIndexView *)in_sprite)->unk_14 & 0x8000) {
            break;
        }

        {
            DungeonGlobalStatus *system_state = &g_dungeon_status;
            u16 state_count;

            state_count = ((u16)system_state->activity_counts.parts.pending_action_count);
            state_count++;
            system_state->activity_counts.parts.pending_action_count = state_count;
        }
        ((ActorActionStateView *)in_action)->unk_9B++;
        return;
    case 2:
        if (((SpriteStatusIndexView *)in_sprite)->unk_14 & 0xE000) {
            u8 *anim_table;

            anim_table = D_80174F40;
            (*(void * *)((u8 *)in_sprite + 0x2C)) = anim_table;
            select_sprite_entry(in_sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173880_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((ActorActionStateView *)in_action)->unk_9B++;
            return;
        }
        return;
    case 3:
        if (!(((SpriteStatusIndexView *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *system_state;

            system_state = &g_dungeon_status;
            (*(u16 *)&system_state->activity_counts.parts.pending_action_count)--;
        }
        break;
    default:
        return;
    }

    ((S_80173880_2 *)actor)->unk_1C.u &= ~0x200;
    ((ActorActionStateView *)in_action)->unk_8C = D_801710F4;
}
