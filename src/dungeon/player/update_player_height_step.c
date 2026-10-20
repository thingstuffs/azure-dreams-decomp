#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;

void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
s32 collect_ground_item();  /* extern */
void process_unflagged_linked_entries();                         /* extern */
void process_unflagged_linked_entries_alt();                         /* extern */
void set_record_integer_tile_center();              /* extern */
s32 play_sound_if_enabled();                     /* extern */
extern u8 D_800DD040[];
extern u8 D_800DD058[];

/* Updates movement toward a target tile and advances the actor's animation state. */
void update_player_height_step(void *actor, EntityRec *motion, SpriteFrameState *sprite, EntityRec *model) {
    s16 ticks_left;
    s32 coord_or_ticks;
    s32 motion_value;
    u32 state_index;
    u8 state;
    s32 launch_state;

    state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8;
    state_index = state;
    switch (state_index) {
    case 0:
    case 8:
    case 10:
        if (sprite->flags & 0x6000) {
            launch_state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8;
            if (launch_state == 0) {
                motion->flags14 = 0xFFF00000;
            } else {
                motion_value = 8;
                if (launch_state != motion_value) {
                    motion_value = 0xFFEC0000;
                } else {
                    motion_value = 0xFFF80000;
                }
                motion->flags14 = motion_value;
            }
            process_unflagged_linked_entries_alt(model->unk_5C);
            process_unflagged_linked_entries(model->unk_5C);
            g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x812);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_98 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_98 & 0xFFF3);
            sprite->frameTable = D_800DD040;
            set_sprite_animation_frame(sprite, D_800DD040[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + model->facing + 0x100) >> 9) & 7], 0, 1);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8
                + 1);
            play_sound_if_enabled(0x50A);
            return;
        }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    default:
        return;
    case 1:
    case 9:
    case 11:
        if (g_dungeon_status.movement_frames_left != 0) {
            motion_value = sprite->unk_24 << 6;
            coord_or_ticks = motion->x.w.i;
            coord_or_ticks -= 0x20;
            motion_value = (motion_value - coord_or_ticks) << 0x10;
            motion->unk_0C = motion_value / g_dungeon_status.movement_frames_left;
            coord_or_ticks = motion->y.w.i;
            motion_value = sprite->unk_25;
            coord_or_ticks -= 0x20;
            motion_value <<= 6;
            motion_value -= coord_or_ticks;
            coord_or_ticks = g_dungeon_status.movement_frames_left;
            motion_value <<= 0x10;
            motion->unk_10 = motion_value / coord_or_ticks;
        }
        ticks_left = (u16) g_dungeon_status.movement_frames_left - 1;
        g_dungeon_status.movement_frames_left = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            g_dungeon_status.movement_frames_left = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
            if ((u8) ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 >= 0xAU) {
                sprite->frameTable = D_800DD058;
                set_sprite_animation_frame(sprite, D_800DD058[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + model->facing + 0x100) >> 9) & 7],
                    0, 1);
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 =
                    (u8) (((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_u8 + 1);
                g_dungeon_status.movement_frames_left = 1;
                return;
            }
            if ((collect_ground_item(actor, motion, sprite, model) << 0x10) > 0) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = handle_player_input;
            }
            return;
        }
        return;
    case 12:
        if (sprite->flags & 0x6000) {
            g_dungeon_status.movement_frames_left = 0;
            if ((collect_ground_item(actor, motion, sprite, model) << 0x10) > 0) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = handle_player_input;
            }
            return;
        }
        return;
    }
}
