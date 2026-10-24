/* Actor path dispatch and its file-private helper. */
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800C9F34_arg0.h"
#include "dungeon/actor.h"
typedef s32 M2C_UNK;
extern s32 check_entity_relation();
extern s8 find_active_rect_containing_point();
extern s32 can_entity_gain_level();
static void advance_actor_along_path_points(void *motion, s32 unused, void *position, void *path);
#include "dungeon/actor/state.h"
typedef struct S_800C9F34_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800C9F34_3;
#include "shared/dungeon_moving_views.h"
#include "shared/actor_status.h"
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
typedef struct S_800CA0DC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_800CA0DC_0;

/* Routes actor updates through path movement, defeat or level checks, and pending action selection. */
void dispatch_actor_behavior_state(Rec_func_800C9F34_arg0 *actor_state, s32 context, S_800C9F34_3 *position, ActorRecord *entity) {

    if (g_dungeon_status.flags & 0x1000) {
        actor_state->unk_9A.as_s8 = 0xE;
        advance_actor_along_path_points(actor_state, context, position, entity);
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        actor_state->unk_9A.as_s8 = 0xE;
        entity->flags1C =
            entity->flags1C | 0x40000;
        actor_state->unk_98 = actor_state->unk_98 & 0xFFF7;
        if (entity->hp == 0 || ((*(u16 *)0x80013714) & 8) != 0) {
            set_actor_action_state_eight(actor_state, context, position);
            return;
        }
        if ((can_entity_gain_level(entity) << 0x10) != 0) {
            if ((g_dungeon_status.active_actor == entity) &&
                (g_dungeon_status.activity_counts.parts.pending_action_count == 0) &&
                !(g_dungeon_status.flags & 8)) {
                entity->experience = 0;
                g_dungeon_status.active_actor = 0;
            }
            return;
        }
    }
    position->unk_26 = find_active_rect_containing_point(
        position->unk_24, position->unk_25);
    if ((entity->pending_turn_updates > 0) &&
        (!(g_dungeon_status.flags & 0x2000) ||
         ((check_entity_relation(entity,
            ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) == 0))) {
        choose_best_eligible_entry_for_actor(actor_state, context, position);
    }
}

/* Advances to the next stored path tile, updates facing, and sets the movement animation duration. */
static void advance_actor_along_path_points(void *motion, s32 unused, void *position, void *path)
{
    s32 step_count;
    s32 old_x;
    s32 old_y;

    if (((S_800CA0DC_0 *)path)->unk_71.s <= 0) {
        return;
    }
    if (((S_800CA0DC_0 *)path)->unk_71.u <= ((S_800CA0DC_0 *)path)->unk_8A.s) {
        return;
    }

    old_x = ((MovingTile *)position)->tile_x;
    old_y = ((MovingTile *)position)->tile_y;
    ((MovingTile *)position)->tile_x =
        ((ActorStatusBytesView *)((u8 *)path + ((S_800CA0DC_0 *)path)->unk_8A.s))->path_x;
    ((MovingTile *)position)->tile_y =
        ((ActorStatusBytesView *)((u8 *)path + ((S_800CA0DC_0 *)path)->unk_8A.s))->path_y;
    ((S_800CA0DC_0 *)path)->unk_8A.u++;

    ((S_800CA0DC_0 *)path)->unk_2A =
        get_rounded_facing_and_rounding_flag(old_x, old_y, ((MovingTile *)position)->tile_x,
                      ((MovingTile *)position)->tile_y, (u8 *)motion + 0x98);
    ((S_800CA0DC_0 *)path)->unk_1C |= 0x40000000;
    ((Rec_func_800C9F34_arg0 *)motion)->unk_9A.as_u8 = 0xF;
    (*(s32 *)((u8 *)motion + (0x8C))) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_800C9F34_arg0 *)motion)->unk_96 = 0;
        return;
    }

    ((Rec_func_800C9F34_arg0 *)motion)->unk_96 = 8;
    step_count = ((S_800CA0DC_0 *)path)->unk_71.u;
    if (step_count > 0) {
        ((Rec_func_800C9F34_arg0 *)motion)->unk_96 = 8 / step_count;
    }
}
