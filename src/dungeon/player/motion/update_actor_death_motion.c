#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player.h"
#include "dungeon/player/position.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;

void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
void set_record_integer_tile_center();              /* extern */
void apply_clamped_actor_value_delta();                      /* extern */
extern u8 player_wait_frames[8];
extern u8 D_800DCFE0[8];


/* Update death movement and animation, then select the next death state. */
void update_actor_death_motion(void *state, void *motion, void *sprite, void *actor) {
    s16 frames_left;
    s32 pos_y;
    s32 pos_x;
    u16 anim_frames;
    u16 move_frames;
    u16 next_timer;
    u32 velocity_x;
    u8 *anim_table;

    if (((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_u8 == 0) {
        apply_clamped_actor_value_delta(actor);
        ((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_u8 = (u8) (((Rec_func_8008ACDC_arg0 *)state)->unk_9B.as_u8 + 1);
        ((EntityRec *)motion)->unk_0C = (u32) (func_80064584(((s16)((EntityRec *)actor)->unk_6A)) << 9);
        ((EntityRec *)motion)->unk_10 = (s32) (func_800644B8(((s16)((EntityRec *)actor)->unk_6A)) << 9);
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = 0xCU;
    }
    if (((Rec_func_8008ACDC_arg0 *)state)->unk_10C & 1) {
        begin_player_damage_reaction(state, motion, sprite, actor);
        return;
    }
    if ((((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_800DCFE0)
        && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        anim_frames = ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 - 1;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = anim_frames;
        if ((anim_frames << 0x10) > 0) {
            set_sprite_animation_frame(sprite, ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7], 0, 1);
        }
    }
    frames_left = (s16) ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16;
    if (frames_left > 0) {
        pos_x = ((EntityRec *)motion)->x.v;
        pos_y = ((EntityRec *)motion)->y.v;
        ((EntityRec *)motion)->x.v = (s32) (pos_x + ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20)
            << 0x10) - pos_x) / frames_left));
        ((EntityRec *)motion)->y.v = (s32) (pos_y + ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20)
            << 0x10) - pos_y) / (s16) ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16));
        velocity_x = ((u32)((EntityRec *)motion)->unk_0C);
        ((EntityRec *)motion)->unk_0C = (u32) ((s32) (velocity_x + (velocity_x >> 0x1F)) >> 1);
        ((EntityRec *)motion)->unk_10 = (s32) ((s32) ((EntityRec *)motion)->unk_10 / 2);
        move_frames = ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 - 1;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = move_frames;
        if ((move_frames << 0x10) == 0) {
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0U;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        }
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        anim_table = player_wait_frames;
        (*(u8 **)((u8 *)sprite + (0x2C))) = anim_table;
        set_sprite_animation_frame(sprite, anim_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7], 0, 1);
        if (((s32)g_dungeon_status.pending_display_owner) == (actor - 0x20)) {
            g_dungeon_status.pending_display_owner = (s32) (((s32)g_dungeon_status.pending_display_owner) & 0x7FFFFFFF);
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            if (dungeon_floor_flags & 0x08000000) {
                ((EntityRec *)actor)->unk_28 = 1U;
            } else {
                ((EntityRec *)actor)->unk_28 = 0U;
                reset_actor_motion_at_sprite_tile(state, motion, sprite, actor);
                return;
            }
        }
        next_timer = 8U;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_96.as_u16 = next_timer;
        ((Rec_func_8008ACDC_arg0 *)state)->unk_8C.as_pm = handle_player_input;
    }
}

