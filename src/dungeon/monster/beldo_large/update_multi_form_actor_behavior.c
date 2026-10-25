#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_8016D0FC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016D0FC_0;   /* arg0 in update_multi_form_actor_behavior */

typedef struct S_8016D0FC_3 {
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
} S_8016D0FC_3;   /* actor_arg in update_multi_form_actor_behavior */

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
#include "dungeon/player/object/action_state.h"
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, s32, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, s32, void *, s32);
extern void begin_actor_move_to_target_facing(void *, s32, void *, void *);
extern void update_multi_form_actor_movement(void *, s32, SpriteFrameState *, void *);

extern u8 beldo_large_action_resume_address[];
extern u8 beldo_large_frame_set_4[];
extern u8 beldo_large_frame_set_7[];

/* Advance the actor_arg state, updating directional tables and the shared counter. */
void update_multi_form_actor_behavior(void *context, s32 callback_arg, SpriteFrameState *object_arg, void *actor_arg)
{
    SpriteFrameState *object;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    u8 *expected_table;
    u8 *current_table;
    s32 state;
    s32 kind;
    s32 actor_flags;
    s32 direction_index;

    state = ((S_8016D0FC_0 *)context)->unk_9B;
    switch (state) {
    case 0:
        if (!(object_arg->flags & 0xE000)) {
            return;
        }
        current_table = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
        current_table--;
        g_dungeon_status.activity_counts.parts.pending_action_count = current_table;
        kind = ((S_8016D0FC_0 *)context)->unk_AC;
        if (kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)) {
            (object_arg->frameTable) = beldo_large_frame_set_4;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016D0FC_3 *)actor_arg)->unk_2A + 0x100) >> 9;
            select_sprite_entry(object_arg, beldo_large_frame_set_4[direction_index & 7], 0);
        }
        ((S_8016D0FC_0 *)context)->unk_9B++;
        return;
    case 1:
        kind = ((S_8016D0FC_0 *)context)->unk_AC;
        if (kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)) {
            current_table = object_arg->frameTable;
            expected_table = beldo_large_frame_set_4;
            if (current_table != expected_table) {
                (object_arg->frameTable) = expected_table;
                direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016D0FC_3 *)actor_arg)->unk_2A + 0x100) >> 9;
                select_sprite_entry(object_arg, expected_table[direction_index & 7], 0);
            }
        }
        object = object_arg;
        if (((S_8016D0FC_3 *)actor_arg)->unk_25 != 0) {
            kind = ((S_8016D0FC_0 *)context)->unk_AC;
            if (kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)) {
                (object->frameTable) = beldo_large_frame_set_7;
                select_sprite_entry(object,
                    beldo_large_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016D0FC_3 *)actor_arg)->unk_2A + 0x100) >> 9) & 7], 0);
            }
            current_table = (u8 *)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
            g_dungeon_status.activity_counts.parts.pending_action_count = current_table;
            ((S_8016D0FC_0 *)context)->unk_9B++;
            return;
        }
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (((S_8016D0FC_3 *)actor_arg)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(context, callback_arg, object, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(actor_arg) << 16) != 0) {
            return;
        }
        actor_flags = ((S_8016D0FC_3 *)actor_arg)->unk_1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(context, callback_arg, object, actor_arg);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(context, callback_arg, object, actor_arg);
            update_multi_form_actor_movement(context, callback_arg, object, actor_arg);
            return;
        }
        if (((S_8016D0FC_3 *)actor_arg)->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor_arg) << 16) != 0) {
            if ((check_entity_relation(actor_arg, ((ActorRecord *)((u8 *)primary_actor_record))->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_mp(actor_arg);
        on_actor_status_updated(actor_arg);
        if (((S_8016D0FC_3 *)actor_arg)->unk_25 == 0) {
            return;
        }
        kind = ((S_8016D0FC_0 *)context)->unk_AC;
        if (kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)) {
            (object->frameTable) = beldo_large_frame_set_7;
            select_sprite_entry(object,
                beldo_large_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016D0FC_3 *)actor_arg)->unk_2A + 0x100) >> 9) & 7], 0);
        }
        current_table = (u8 *)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = current_table;
        ((S_8016D0FC_0 *)context)->unk_9B++;
        return;
    case 2:
        object = object_arg;
        if (object->flags & 0xE000) {
            current_table = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            current_table--;
            g_dungeon_status.activity_counts.parts.pending_action_count = current_table;
            ((S_8016D0FC_0 *)context)->unk_8C = beldo_large_action_resume_address;
        }
        return;
    }
}
