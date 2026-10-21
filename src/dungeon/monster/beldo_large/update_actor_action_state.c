#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_8016CC70_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016CC70_0;   /* obj in update_actor_action_state_2 */

typedef struct S_8016CC70_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_8016CC70_1;   /* target_arg in update_actor_action_state_2 */

typedef struct S_8016CC70_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8016CC70_2;   /* actor_arg in update_actor_action_state_2 */


s32 get_entity_effect_value(void *, s32);
void clear_slots_of_type(void *, s32);
void select_sprite_entry(void *, s32, s32);
s32 check_entity_relation(void *, void *);
s16 get_tile_chebyshev_distance(void *, void *);
s32 has_pending_actor_or_turn_action(void *);
s32 generate_random_value(void);
void on_actor_status_updated(void *);
void update_actor_status_and_mp(void *);
void begin_pushed_actor_move(void *, s32, void *, void *);
s32 begin_ready_actor_directional_action(void *, s32, void *, s32);
void advance_actor_pending_action(void *, s32, void *, void *);
void begin_actor_move_to_target_facing(void *, s32, void *, void *);
void update_multi_form_actor_movement(void *, s32, void *, void *);
extern M2C_UNK D_8016A36C;
extern u8 D_80173AC8[];
extern u8 D_80173AD0[];

/* Processes object action states, dispatches actor_arg actions, and updates directional tiles. */
void update_actor_action_state_2(void *obj_arg, s32 context_arg, void *target_arg, void *actor_arg) {
    void *target;

    DungeonGlobalStatus *held_base;
    void *callback;
    TileObject *room_base;
    DungeonGlobalStatus *counter_base;
    s32 counter_value;
    s32 action_state;
    s32 obj_kind;
    s32 actor_flags;
    s8 target_room;

    action_state = ((S_8016CC70_0 *)obj_arg)->unk_9B;
    switch (action_state) {
    case 0:
        if (!(((S_8016CC70_1 *)target_arg)->unk_14 & 0xE000)) {
            return;
        }
        obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
        if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
            (*(u8 **)((u8 *)target_arg + 0x2C)) = D_80173AC8;
            select_sprite_entry(target_arg, D_80173AC8[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                >> 9) & 7], 0);
        }
        counter_base = &g_dungeon_status;
        counter_value = *(u16 *)&counter_base->activity_counts.parts.pending_action_count;
        counter_value--;
        *(u16 *)&counter_base->activity_counts.parts.pending_action_count = counter_value;
        ((S_8016CC70_0 *)obj_arg)->unk_9B++;
        return;

    case 1:
        obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
        if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
            if (((S_8016CC70_1 *)target_arg)->unk_2C != D_80173AC8) {
                (*(u8 **)((u8 *)target_arg + 0x2C)) = D_80173AC8;
                select_sprite_entry(target_arg, D_80173AC8[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                    >> 9) & 7], 0);
            }
        }
        target = target_arg;
        if ((get_entity_effect_value(actor_arg, 1) << 0x10) == 0) {
            obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
            if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
                (*(u8 **)((u8 *)target + 0x2C)) = D_80173AD0;
                select_sprite_entry(target, D_80173AD0[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                    >> 9) & 7], 0);
            }
        } else {
            held_base = &g_dungeon_status;
            if (held_base->flags & 0x1000) {
                return;
            }
            if (((S_8016CC70_2 *)actor_arg)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(obj_arg, context_arg, target, 0) != 0) {
                    return;
                }
            }
            if (((S_8016CC70_2 *)actor_arg)->unk_25 == 0) {
                if (held_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_arg) << 0x10) != 0) {
                return;
            }
            actor_flags = ((S_8016CC70_2 *)actor_arg)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(obj_arg, context_arg, target, actor_arg);
                update_multi_form_actor_movement(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if (((S_8016CC70_2 *)actor_arg)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_arg) << 0x10) != 0) {
                if ((check_entity_relation(actor_arg, (u8 *)primary_actor_record->unk_58 + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor_arg);
            on_actor_status_updated(actor_arg);
            if ((get_entity_effect_value(actor_arg, 1) << 0x10) != 0) {
                room_base = &reference_tile_object;
                target_room = ((S_8016CC70_1 *)target)->unk_26;
                if (!(((target_room != room_base->room_index) || (target_room < 0))
                      && get_tile_chebyshev_distance(room_base, target) >= 2)) {
                    if ((generate_random_value() & 7) == 0) {
                        clear_slots_of_type(actor_arg, 1);
                    }
                }
            }
            if ((get_entity_effect_value(actor_arg, 1) << 0x10) != 0) {
                return;
            }
            obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
            if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
                (*(u8 **)((u8 *)target + 0x2C)) = D_80173AD0;
                select_sprite_entry(target, D_80173AD0[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                    >> 9) & 7], 0);
            }
        }
        if (((S_8016CC70_1 *)target)->unk_14 & 0x8000) {
            break;
        }
        counter_base = &g_dungeon_status;
        counter_value = *(u16 *)&counter_base->activity_counts.parts.pending_action_count;
        counter_value++;
        *(u16 *)&counter_base->activity_counts.parts.pending_action_count = counter_value;
        ((S_8016CC70_0 *)obj_arg)->unk_9B++;
        return;

    case 2:
        target = target_arg;
        if (!(((S_8016CC70_1 *)target)->unk_14 & 0xE000)) {
            return;
        }
        counter_base = &g_dungeon_status;
        counter_value = *(u16 *)&counter_base->activity_counts.parts.pending_action_count;
        counter_value--;
        *(u16 *)&counter_base->activity_counts.parts.pending_action_count = counter_value;
        break;

    default:
        return;
    }
    callback = &D_8016A36C;
    ((S_8016CC70_0 *)obj_arg)->unk_8C = callback;
}
