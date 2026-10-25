#include "common.h"
#include "dungeon/player/input.h"
#include "dungeon/player/position.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player.h"

extern void set_sprite_animation_frame(void *, s16, s16, s32);
extern s32 collect_ground_item(void *, void *, void *, void *);
extern void set_record_integer_tile_center(void *, u8, u8);


extern u8 player_alternate_motion_frames[];

/* Updates movement toward the destination tile and handles arrival when the timer expires. */
void advance_alternate_tile_center_motion(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *facing) {
    u16 ticks_left;

    if (g_dungeon_status.flags & 0x80) {
        g_dungeon_status.movement_frames_left = 0;
    }
    if (g_dungeon_status.movement_frames_left != 0) {
        motion->velocity_x = (s32) ((s32) ((((sprite->tile_x << 6) + 0x20) << 0x10)
            - motion->x.v) / g_dungeon_status.movement_frames_left);
        motion->velocity_y = (s32) ((s32) ((((sprite->tile_y << 6) + 0x20) << 0x10)
            - motion->y.v) / g_dungeon_status.movement_frames_left);
    }
    if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x100) && (g_dungeon_status.movement_frames_left == 6)) {
        begin_wake_nearby_monsters(actor, motion, sprite, facing);
        return;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x10)) {
        u8 *old_anim_table = sprite->frameTable;
        u8 *anim_table = player_alternate_motion_frames;
        if (old_anim_table != anim_table) {
            sprite->frameTable = anim_table;
            set_sprite_animation_frame(sprite, anim_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + facing->facing + 0x100) >> 9) & 7], 0,
                1);
        }
    }
    ticks_left = g_dungeon_status.movement_frames_left - 1;
    g_dungeon_status.movement_frames_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        g_dungeon_status.movement_frames_left = 0U;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if ((collect_ground_item(actor, motion, sprite, facing) << 0x10) > 0) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = &handle_carrying_player_input;
        }
    }
}
