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
#include "dungeon/item.h"
#include "dungeon/monster/saber.h"

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 check_movement_clearance_and_height();

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


/* Advance the entity along its stored path and update movement timing. */
void advance_entity_along_stored_path(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    ActorRecord *path_actor = body;
    S_80171CD4_0 *state = (S_80171CD4_0 *)actor;
    s32 move_flags;
    s16 heading;
    s16 move_result;
    s16 x;
    s32 y;

    if (state->unk_71.s <= 0) {
        return;
    }

    if (body->action_id.u != 0xF) {
        body->unk_90.value = 0;
        motion->velocity_z = 0;
        body->unk_9D.s = 0;
    }

    if (state->unk_71.u <= state->unk_8A.s) {
        return;
    }

    if (*(u8 **)&sprite->frameTable != saber_frame_set_9) {
        (sprite->frameTable) = saber_frame_set_9;
        select_sprite_entry(
            sprite,
            saber_frame_set_9[((g_game_work.view.camera_rotation.parts.viewAngle + state->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = sprite->tile_x;
    y = sprite->tile_y;
    move_flags = 0x3000;
    if (state->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, move_flags);

    heading = get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((ActorRecord *)((u8 *)state + state->unk_8A.s))->path_x[0],
        ((ActorRecord *)((u8 *)state + state->unk_8A.s))->path_y[0],
        &path_actor->action_state_flags);
    move_result = check_movement_clearance_and_height(heading, sprite, state, 0x20);

    sprite->tile_x =
        ((ActorRecord *)((u8 *)state + state->unk_8A.s))->path_x[0];
    move_flags = 0x3000;
    sprite->tile_y =
        ((ActorRecord *)((u8 *)state + state->unk_8A.s))->path_y[0];
    state->unk_8A.u++;

    {
        s32 next_x = sprite->tile_x;
        s32 next_y = sprite->tile_y;

        if (state->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, move_flags);
    }

    state->unk_2A = heading;
    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(sprite->flags & 0x8000)) {
            initialize_actor_facing_sprite(body, motion, sprite, state);
            body->unk_8C.word = 0;
        } else {
            body->action_id.u = 0xF;
            body->unk_8C.word = 0;
        }
    } else {
        body->action_id.u = 0xF;
        body->unk_8C.word = 0;
    }
    state->unk_1C |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        body->action_timer.s = 0;
        return;
    }

    body->action_timer.s = 8;
    {
        s32 step_count = state->unk_71.u;
        if (step_count > 0) {
            body->action_timer.s = 8 / step_count;
        }
    }
}
