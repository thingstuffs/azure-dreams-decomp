#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

void set_sprite_animation_frame();
s32 collect_ground_item();
s32 process_unflagged_linked_entries();
s32 process_unflagged_linked_entries_alt();
s32 set_record_integer_tile_center();
extern s32 player_action_tag;
extern u8 player_height_step_frames[];
extern u8 player_landing_frame_set[];
extern u8 player_throw_frame_set[];

/* Updates timed movement and directional animation, then selects the next handler. */
void update_carrying_player_step(u8 *entity_in, s32 *motion_in, u16 *sprite_in, s32 *actor_in) {
    u8 *entity = entity_in;
    s32 *motion = motion_in;
    u16 *sprite = sprite_in;
    s32 *actor = actor_in;
    s32 vertical_speed;
    u8 phase;
    s32 start_y;
    s16 frames_left;
    u8 *anim_table;
    u8 *next_handler;

    phase = *(u8 *)(entity + 0x9B);
    switch (phase) {
    case 0:
    case 8:
    case 10:
        if (!(*(u16 *)((u8 *)sprite + 0x14) & 0x6000)) {
            return;
        }
        phase = *(u8 *)(entity + 0x9B);
        vertical_speed = 8;
        if (phase == 0) {
            vertical_speed = 0xFFF00000;
        } else {
            if (phase != vertical_speed) {
                vertical_speed = 0xFFEC0000;
            } else {
                vertical_speed = 0xFFF80000;
            }
        }
        *(s32 *)((u8 *)motion + 0x14) = vertical_speed;
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x100000) {
            anim_table = player_throw_frame_set;
        } else {
            anim_table = player_height_step_frames;
        }
        *(u8 **)((u8 *)sprite + 0x2C) = anim_table;
        process_unflagged_linked_entries_alt(*(s32 *)((u8 *)actor + 0x5C));
        process_unflagged_linked_entries(*(s32 *)((u8 *)actor + 0x5C));
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x812);
        *(u16 *)((u8 *)entity + 0x98) = (u16) (*(u16 *)((u8 *)entity + 0x98) & 0xFFF3);
        set_sprite_animation_frame(sprite, *(*(u8 **)((u8 *)sprite + 0x2C) + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor
            + 0x2A) + 0x100) >> 9) & 7)), 0, 1);
        *(u8 *)(entity + 0x9B) = (u8) (*(u8 *)(entity + 0x9B) + 1);
        return;
    case 1:
    case 9:
    case 11:
        if (g_dungeon_status.movement_frames_left != 0) {
            s32 target_x;
            s32 start_x;
            target_x = *(u8 *)((u8 *)sprite + 0x24);
            target_x <<= 6;
            start_x = *(s16 *)((u8 *)motion + 2);
            start_x -= 0x20;
            *(s32 *)((u8 *)motion + 0xC) = ((target_x - start_x) << 0x10) / (s16) g_dungeon_status.movement_frames_left;
            start_y = *(s16 *)((u8 *)motion + 6) - 0x20;
            *(s32 *)((u8 *)motion + 0x10) = (s32) ((s32) ((*(u8 *)((u8 *)sprite + 0x25) << 6) - start_y)
                << 0x10) / (s16) g_dungeon_status.movement_frames_left;
        }
        frames_left = (u16) g_dungeon_status.movement_frames_left - 1;
        g_dungeon_status.movement_frames_left = frames_left;
        if ((frames_left << 0x10) > 0) {
            return;
        }
        g_dungeon_status.movement_frames_left = 0;
        *(s32 *)((u8 *)motion + 0x10) = 0;
        *(s32 *)((u8 *)motion + 0xC) = 0;
        set_record_integer_tile_center(motion, *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25));
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x100000) {
            if ((collect_ground_item(entity, motion, sprite, actor) << 0x10) <= 0) {
                return;
            }
            next_handler = (u8 *)&player_action_tag;
            *(u8 **)((u8 *)entity + 0x8C) = next_handler;
            return;
        }
        if ((u8) *(u8 *)(entity + 0x9B) < 0xAU) {
        if ((collect_ground_item(entity, motion, sprite, actor) << 0x10) <= 0) {
            return;
        }
        next_handler = (u8 *)handle_player_input;
        *(u8 **)((u8 *)entity + 0x8C) = next_handler;
        return;
        }
        *(u8 **)((u8 *)sprite + 0x2C) = player_landing_frame_set;
        set_sprite_animation_frame(sprite, *(*(u8 **)((u8 *)sprite + 0x2C) + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor
            + 0x2A) + 0x100) >> 9) & 7)), 0, 1);
        g_dungeon_status.movement_frames_left = 1;
block_19:
        *(u8 *)(entity + 0x9B) = (u8) (*(u8 *)(entity + 0x9B) + 1);
        return;
    case 12:
        if (!(*(u16 *)((u8 *)sprite + 0x14) & 0x6000)) {
            return;
        }
        g_dungeon_status.movement_frames_left = 0;
block_22:
        if ((collect_ground_item(entity, motion, sprite, actor) << 0x10) <= 0) {
            return;
        }
        next_handler = (u8 *)handle_player_input;
block_24:
        *(u8 **)((u8 *)entity + 0x8C) = next_handler;
        return;
    }
}
