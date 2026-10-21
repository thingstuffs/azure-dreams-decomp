#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80173DD4_arg0.h"

typedef struct S_80173DD4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173DD4_3;   /* counter_base in update_actor_behavior_2 */

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80174520(void *, void *, void *, void *);
extern void create_randomized_motion_object(void *, void *);

extern u8 D_80171094[];
extern u8 D_80176470[];
extern u8 D_80176478[];

/* Updates actor behavior and directional animation through three states, then sets its next callback. */
void update_actor_behavior_2(void *controller, void *context_in, void *object, ActorRecord *actor)
{
    
    s32 actor_flags;
    u16 current_value;
    u16 value_adjustment;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = ((Rec_func_80173DD4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)object)->flags & 0xE000)) {
            create_randomized_motion_object(controller, context_in);
            create_randomized_motion_object(controller, context_in);
            create_randomized_motion_object(controller, context_in);
            create_randomized_motion_object(controller, context_in);
            break;
        }
        ((SpriteFrameState *)object)->frameTable = D_80176470;
        select_sprite_entry(object,
            D_80176470[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {
            u8 *counter_base = (u8 *)&g_dungeon_status.turn_scale;

            ((S_80173DD4_3 *)counter_base)->unk_0A--;
        }
        ((Rec_func_80173DD4_arg0 *)controller)->unk_9B++;
        break;
    case 1:
        if ((get_entity_effect_value(actor, 1) << 16) == 0) {
        ((SpriteFrameState *)object)->frameTable = D_80176478;
        select_sprite_entry(object,
            D_80176478[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&actor->flags1C) |= 0x40000;
        if (((SpriteFrameState *)object)->flags & 0x8000) {
            ((Rec_func_80173DD4_arg0 *)controller)->unk_8C = D_80171094;
            break;
        }
        {
            u8 *counter_base = (u8 *)&g_dungeon_status.turn_scale;

            ((Rec_func_80173DD4_arg0 *)controller)->unk_9B++;
            ((S_80173DD4_3 *)counter_base)->unk_0A++;
        }
        break;
        } else {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                break;
            }
            if (actor->unk_64 != 0) {
                if (begin_ready_actor_directional_action(controller, context_in, object, 0) != 0) {
                    break;
                }
            }
            if (actor->mp == 0) {
                if (global_base->flags & 0x2008) {
                    break;
                }
                advance_actor_pending_action(controller, context_in, object, actor);
                break;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                break;
            }
            actor_flags = actor->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(controller, context_in, object, actor);
                break;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(controller, context_in, object, actor);
                current_value = ((Rec_func_80173DD4_arg0 *)controller)->unk_92;
                value_adjustment = ((Rec_func_80173DD4_arg0 *)controller)->unk_A6;
                ((Rec_func_80173DD4_arg0 *)controller)->unk_A6 = 0;
                ((Rec_func_80173DD4_arg0 *)controller)->unk_AC = 0;
                ((Rec_func_80173DD4_arg0 *)controller)->unk_92 = current_value - value_adjustment;
                func_80174520(controller, context_in, object, actor);
                break;
            }
            if (actor->pending_turn_updates == 0) {
                break;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((check_entity_relation(actor,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    break;
                }
            }
            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&((SpriteFrameState *)object)->unk_26;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, object) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor, 1);
                    }
                }
            }
            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                break;
            }
        }
        ((SpriteFrameState *)object)->frameTable = D_80176478;
        select_sprite_entry(object,
            D_80176478[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&actor->flags1C) |= 0x40000;
        if (((SpriteFrameState *)object)->flags & 0x8000) {
            ((Rec_func_80173DD4_arg0 *)controller)->unk_8C = D_80171094;
            break;
        }
        {
            u8 *counter_base = (u8 *)&g_dungeon_status.turn_scale;

            ((Rec_func_80173DD4_arg0 *)controller)->unk_9B++;
            ((S_80173DD4_3 *)counter_base)->unk_0A++;
        }
        break;
    case 2:
        if (((SpriteFrameState *)object)->flags & 0xE000) {
            u8 *counter_base;

            counter_base = (u8 *)&g_dungeon_status.turn_scale;
            ((S_80173DD4_3 *)counter_base)->unk_0A--;
            ((Rec_func_80173DD4_arg0 *)controller)->unk_8C = D_80171094;
        } else {
            create_randomized_motion_object(controller, context_in);
            create_randomized_motion_object(controller, context_in);
            create_randomized_motion_object(controller, context_in);
            create_randomized_motion_object(controller, context_in);
        }
        break;
    }

    return;
}
