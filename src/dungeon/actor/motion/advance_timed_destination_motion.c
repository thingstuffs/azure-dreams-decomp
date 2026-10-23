#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct { u8 pad0[2]; u16 field2; s16 field4; u8 pad6[6]; } D_80083460_t;
extern u8 destination_motion_resume_address[];
extern void begin_player_trap_trigger(void *, void *, void *, void *);
extern void process_unflagged_linked_entries(s32);
extern void process_unflagged_linked_entries_alt(s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);

/* Advances timed movement toward a destination and handles completion. */
void advance_timed_destination_motion(Rec_func_8008ACDC_arg0 *action, ObjectPosition *motion, SpriteFrameState *destination, EntityRec *actor) {
    u16 delay;
    u8 state;
    s32 vertical_speed;
    state = action->unk_9B.as_u8;
    switch (state) {
    case 0:
    case 8:
    case 10:
        delay = action->unk_96.as_u16 - 1;
        action->unk_96.as_u16 = delay;
        if ((s16)delay > 0)
            return;
        state = action->unk_9B.as_u8;
        vertical_speed = 8;
        if (state == 0) {
            vertical_speed = 0xFFF00000;
        } else if (state == vertical_speed) {
            vertical_speed = 0xFFF80000;
        } else {
            vertical_speed = 0xFFEC0000;
        }
        motion->velocity_z = vertical_speed;
        process_unflagged_linked_entries_alt(actor->unk_5C);
        process_unflagged_linked_entries(actor->unk_5C);
        g_dungeon_status.flags |= 0x812;
        action->unk_98 &= 0xFFF3;
        action->unk_9B.as_u8++;
        play_sound_if_enabled(0x50A);
        return;
    case 1:
    case 9:
    case 11:
        if (g_dungeon_status.movement_frames_left != 0) {
            s32 target_x, current_x, current_y;
            target_x = destination->tile_x << 6;
            current_x = motion->x.w.i - 0x20;
            motion->velocity_x = ((target_x - current_x) << 16) / g_dungeon_status.movement_frames_left;
            current_y = motion->y.w.i - 0x20;
            motion->velocity_y = (((destination->tile_y << 6) - current_y) << 16) / g_dungeon_status.movement_frames_left;
        }
        g_dungeon_status.movement_frames_left--;
        if (g_dungeon_status.movement_frames_left > 0)
            return;
        g_dungeon_status.movement_frames_left = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, destination->tile_x, destination->tile_y);
        if (action->unk_9B.as_u8 >= 10) {
            g_dungeon_status.movement_frames_left = 1;
            action->unk_9B.as_u8++;
            return;
        }
        if (action->unk_100 >= 0) {
            begin_player_trap_trigger(action, motion, destination, actor);
            return;
        }
        action->unk_8C.as_pv = destination_motion_resume_address;
        return;
    case 12:
        if (destination->flags & 0x6000) {
            g_dungeon_status.movement_frames_left = 0;
            if (action->unk_100 >= 0) {
                begin_player_trap_trigger(action, motion, destination, actor);
                return;
            }
            action->unk_8C.as_pv = destination_motion_resume_address;
        }
        return;
    default:
        return;
    }
}
