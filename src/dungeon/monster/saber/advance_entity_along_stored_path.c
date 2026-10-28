#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"
#include "engine/graphics.h"
#include "dungeon/level.h"

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 check_movement_clearance_and_height();
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void initialize_actor_facing_sprite(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation);

extern u8 saber_frame_set_9[];

typedef struct S_80171CD4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171CD4_0;   /* state in advance_entity_along_stored_path */

typedef struct S_80171CD4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171CD4_4;   /* (u8 *)state + ((S_80171CD4_0 *)state)->unk_8A.s in advance_entity_along_stored_path */

/* Advance the entity along its stored path and update movement timing. */
void advance_entity_along_stored_path(void *movement, void *motion, SpriteFrameState *entity, void *path_state) {
    ActorRecord *path_actor = movement;
    S_80171CD4_0 *state = path_state;
    s32 move_flags;
    s16 heading;
    s16 move_result;
    s16 x;
    s32 y;

    if (state->unk_71.s <= 0) {
        return;
    }

    if (((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 != 0xF) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_90 = 0;
        ((Rec_func_80171CD4_arg1 *)motion)->unk_14 = 0;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9D = 0;
    }

    if (state->unk_71.u <= state->unk_8A.s) {
        return;
    }

    if (*(u8 **)&entity->frameTable != saber_frame_set_9) {
        (entity->frameTable) = saber_frame_set_9;
        select_sprite_entry(
            entity,
            saber_frame_set_9[((g_game_work.view.camera_rotation.parts.viewAngle + state->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = entity->tile_x;
    y = entity->tile_y;
    move_flags = 0x3000;
    if (state->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, move_flags);

    heading = get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((S_80171CD4_4 *)((u8 *)state + state->unk_8A.s))->unk_74,
        ((S_80171CD4_4 *)((u8 *)state + state->unk_8A.s))->unk_7C,
        &path_actor->action_state_flags);
    move_result = check_movement_clearance_and_height(heading, entity, state, 0x20);

    entity->tile_x =
        ((S_80171CD4_4 *)((u8 *)state + state->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    entity->tile_y =
        ((S_80171CD4_4 *)((u8 *)state + state->unk_8A.s))->unk_7C;
    state->unk_8A.u++;

    {
        s32 next_x = entity->tile_x;
        s32 next_y = entity->tile_y;

        if (state->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, move_flags);
    }

    state->unk_2A = heading;
    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(entity->flags & 0x8000)) {
            initialize_actor_facing_sprite(movement, motion, entity, state);
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        } else {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        }
    } else {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
    }
    state->unk_1C |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 0;
        return;
    }

    ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8;
    {
        s32 step_count = state->unk_71.u;
        if (step_count > 0) {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8 / step_count;
        }
    }
}
