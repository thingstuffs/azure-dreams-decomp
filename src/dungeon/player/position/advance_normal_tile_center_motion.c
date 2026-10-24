#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/player/position.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player.h"

extern void set_sprite_animation_frame(void *, u8, s32, s32);
extern s32 collect_ground_item(void *, void *, void *, void *);
extern void set_record_integer_tile_center(void *, u8, u8);

extern u8 player_tile_motion_frames[];

/* Move toward the target tile, update the animation, and finish when the timer expires. */
void advance_normal_tile_center_motion(void *entity, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *facing) {
    DungeonGlobalStatus *late_status;
    u8 * status_page;
    s32 frames_left;
    s32 x_velocity;
    s32 y_position;
    s32 move_frames;
    s16 timer;
    u16 flags;

    if (g_dungeon_status.flags & 0x80) {
        g_dungeon_status.movement_frames_left = 0;
    }

    timer = g_dungeon_status.movement_frames_left;
    if (timer != 0) {
        x_velocity =
            ((((sprite->tile_x << 6) + 0x20) << 16) -
             motion->x.v) /
            timer;
        y_position = motion->y.v;
        motion->velocity_x = x_velocity;
        move_frames = g_dungeon_status.movement_frames_left;
        motion->velocity_y =
            ((((sprite->tile_y << 6) + 0x20) << 16) -
             y_position) /
            move_frames;
    }

    if (((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 & 0x100) {
        frames_left = g_dungeon_status.movement_frames_left;
        if (((*(u16 *)0x80013714 & 8) && frames_left == 3) ||
            (!(*(u16 *)0x80013714 & 8) && frames_left == 6)) {
            begin_wake_nearby_monsters(entity, motion, sprite, facing);
            return;
        }
    }

continue_update:
    flags = ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2;
    if (!(flags & 0x10)) {
        if (*(u8 **)&sprite->frameTable != player_tile_motion_frames) {
            ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 = flags | 1;
            sprite->frameTable = player_tile_motion_frames;
            set_sprite_animation_frame(
                sprite,
                player_tile_motion_frames[((g_game_work.view.camera_rotation.parts.viewAngle + facing->facing + 0x100) >> 9) & 7],
                0,
                1);
        }
    }

    status_page = (u8 *)(&g_dungeon_status.turn_scale);
    late_status = (void *)status_page;
    timer = late_status->movement_frames_left - 1;
    late_status->movement_frames_left = timer;
    if (timer > 0) {
        return;
    }

    late_status->movement_frames_left = 0;
    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

    sprite->flags |= 0x4000;
    if ((s16)collect_ground_item(entity, motion, sprite, facing) > 0) {
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_8C.as_s32 = (s32)handle_player_input;
    }
}
