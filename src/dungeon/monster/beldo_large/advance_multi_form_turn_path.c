#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"

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

extern s32 select_sprite_entry();
extern s32 cycle_map_cell_flags();
extern s32 update_map_cell_flags_with_item_limit();
extern s32 check_movement_clearance_and_height();
extern s16 get_rounded_facing_and_rounding_flag();

extern u8 beldo_large_frame_set_10[8];
extern u8 D_801739C8[8];
extern u8 D_801739D0[8];
extern u8 D_801739D8[8];

/* Advance the actor along its path and update its animation, facing, and movement timing. */
void advance_multi_form_turn_path(void *actor, s32 unused, SpriteFrameState *sprite, EntityRec *movement)
{
    s32 move_mode;
    s32 behavior;
    s32 step_count;
    s32 old_x;
    s32 old_y;
    s16 direction;
    u8 *path_step;

    if (((s8)movement->unk_71) <= 0) {
        return;
    }
    {
        s32 path_count = movement->unk_71;
        if (movement->unk_8A >= path_count) {
            return;
        }
    }

    behavior = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
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
        if (*(u8 **)&sprite->frameTable != D_801739C8) {
            (sprite->frameTable) = D_801739C8;
            select_sprite_entry(sprite,
                D_801739C8[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 2:
        if (*(u8 **)&sprite->frameTable != D_801739D0) {
            (sprite->frameTable) = D_801739D0;
            select_sprite_entry(sprite,
                D_801739D0[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 3:
        if (*(u8 **)&sprite->frameTable != D_801739D8) {
            (sprite->frameTable) = D_801739D8;
            select_sprite_entry(sprite,
                D_801739D8[((g_game_work.view.camera_rotation.parts.viewAngle + movement->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    move_mode = 0x3000;
    old_x = sprite->tile_x;
    old_y = sprite->tile_y;
    if (movement->flags1C & 0x2000) {
        move_mode = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, move_mode);

    path_step = (u8 *)movement + movement->unk_8A;
    direction = get_rounded_facing_and_rounding_flag(old_x, old_y, ((S_8016AFC4_3 *)path_step)->unk_74,
                              ((S_8016AFC4_3 *)path_step)->unk_7C, (u8 *)actor + 0x98);
    check_movement_clearance_and_height(direction, sprite, movement, 0x20);

    sprite->tile_x =
        ((S_8016AFC4_4 *)((u8 *)movement + movement->unk_8A))->unk_74;
    sprite->tile_y =
        ((S_8016AFC4_4 *)((u8 *)movement + movement->unk_8A))->unk_7C;
    (*(u16 *)&movement->unk_8A)++;

    cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                  (movement->flags1C & 0x2000) ? 0x300 : 0x3000);

    movement->facing = direction;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_s8 = 0xF;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
    (movement->flags1C) |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = 0;
        return;
    }

    if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 != 0) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = 0x10;
    } else {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 = 8;
    }
    step_count = movement->unk_71;
    if (step_count > 0) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 =
            ((Rec_func_800A9E70_arg0 *)actor)->unk_96.as_s16 / step_count;
    }
}
