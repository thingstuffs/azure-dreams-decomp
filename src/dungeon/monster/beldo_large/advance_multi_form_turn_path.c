#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo_large.h"

typedef struct S_8016AFC4_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016AFC4_3;   /* entry in advance_multi_form_turn_path */

typedef struct S_8016AFC4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016AFC4_4;   /* (u8 *)arg3 + ((S_8016AFC4_0 *)arg3)->unk_8A.s in advance_multi_form_turn_path */

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 check_movement_clearance_and_height();

extern u8 beldo_large_frame_set_10[8];
extern u8 beldo_large_frame_set[8];
extern u8 beldo_large_frame_set_15[8];
extern u8 beldo_large_frame_set_16[8];

/* Advance the actor along its path and update its animation, facing, and movement timing. */
void advance_multi_form_turn_path(ActorRecord *actor, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *movement) {
    s32 move_mode;
    s32 behavior;
    s32 step_count;
    s32 old_x;
    s32 old_y;
    s16 direction;
    S_8016AFC4_3 *path_step;

    if (((s8)movement->movement_queue_state) <= 0) {
        return;
    }
    {
        s32 path_count = movement->movement_queue_state;
        if (movement->unk_8A >= path_count) {
            return;
        }
    }

    behavior = actor->unk_AC.byte;
    switch (behavior) {
    case 0:
        if (*(u8 **)&sprite->frameTable != beldo_large_frame_set_10) {
            (sprite->frameTable) = beldo_large_frame_set_10;
            select_sprite_entry(sprite,
                beldo_large_frame_set_10[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 1:
        if (*(u8 **)&sprite->frameTable != beldo_large_frame_set) {
            (sprite->frameTable) = beldo_large_frame_set;
            select_sprite_entry(sprite,
                beldo_large_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 2:
        if (*(u8 **)&sprite->frameTable != beldo_large_frame_set_15) {
            (sprite->frameTable) = beldo_large_frame_set_15;
            select_sprite_entry(sprite,
                beldo_large_frame_set_15[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 3:
        if (*(u8 **)&sprite->frameTable != beldo_large_frame_set_16) {
            (sprite->frameTable) = beldo_large_frame_set_16;
            select_sprite_entry(sprite,
                beldo_large_frame_set_16[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    move_mode = 0x3000;
    old_x = sprite->tile_x;
    old_y = sprite->tile_y;
    if (movement->flags1C & ACTOR_PLAYER_SIDE) {
        move_mode = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, move_mode);

    path_step = (S_8016AFC4_3 *)((u8 *)movement + movement->unk_8A);
    direction = get_rounded_facing_and_rounding_flag(old_x, old_y, path_step->unk_74,
                              path_step->unk_7C, &actor->action_state_flags);
    check_movement_clearance_and_height(direction, sprite, movement, 0x20);

    sprite->tile_x =
        ((S_8016AFC4_4 *)((u8 *)movement + movement->unk_8A))->unk_74;
    sprite->tile_y =
        ((S_8016AFC4_4 *)((u8 *)movement + movement->unk_8A))->unk_7C;
    (*(u16 *)&movement->unk_8A)++;

    cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                  (movement->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

    movement->facing = direction;
    actor->action_id.s = 0xF;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
    (movement->flags1C) |= ACTOR_REFRESH_GROUND;

    if (g_dungeon_status.flags & 0x80) {
        actor->action_timer.s = 0;
        return;
    }

    if (actor->unk_B0.bytes[0] != 0) {
        actor->action_timer.s = 0x10;
    } else {
        actor->action_timer.s = 8;
    }
    step_count = movement->movement_queue_state;
    if (step_count > 0) {
        actor->action_timer.s =
            actor->action_timer.s / step_count;
    }
}
