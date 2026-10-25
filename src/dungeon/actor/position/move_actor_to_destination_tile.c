#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

void begin_player_trap_trigger(); /* extern */
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);              /* extern */
extern void destination_motion_resume_address();

/* Move the actor toward the destination tile and finish movement when the timer expires. */
void move_actor_to_destination_tile(Rec_func_8008ACDC_arg0 *actor, ObjectPosition *motion, SpriteFrameState *destination, s32 context) {
    s16 frames_left;
    u16 actor_flags;
    s32 saved_context;
    saved_context = context;

    if (g_dungeon_status.flags & 0x80) {
        g_dungeon_status.movement_frames_left = 0;
    }
    if (g_dungeon_status.movement_frames_left != 0) {
        motion->velocity_x = (s32) ((s32) ((((destination->tile_x << 6) + 0x20) << 0x10)
            - motion->x.v) / (s16) g_dungeon_status.movement_frames_left);
        motion->velocity_y = (s32) ((s32) ((((destination->tile_y << 6) + 0x20) << 0x10)
            - motion->y.v) / (s16) g_dungeon_status.movement_frames_left);
    }
    actor_flags = actor->unk_A2;
    if (!(actor_flags & 0x10)) {
        actor->unk_A2 = (u16) (actor_flags | 1);
    }
    frames_left = (u16) g_dungeon_status.movement_frames_left - 1;
    g_dungeon_status.movement_frames_left = frames_left;
    if ((frames_left << 0x10) <= 0) {
        g_dungeon_status.movement_frames_left = 0;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, destination->tile_x, destination->tile_y);
        destination->flags = (u16) (destination->flags | 0x4000);
        if (actor->unk_100 >= 0) {
            begin_player_trap_trigger(actor, motion, destination, saved_context);
            return;
        }
        actor->unk_8C.as_pm = &destination_motion_resume_address;
    }
}
