#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player.h"
#include "dungeon/player/position.h"
#include "sdk/libgte.h"
#include "dungeon/actor.h"
#include "dungeon/player/motion.h"
#include "dungeon/player/object.h"
#include "engine/graphics.h"

extern u8 player_wait_frames[8];
extern u8 player_damage_frames_2[8];


/* Update death movement and animation, then select the next death state. */
void update_actor_death_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s16 frames_left;
    s32 pos_y;
    s32 pos_x;
    u16 anim_frames;
    u16 move_frames;
    u16 next_timer;
    u32 velocity_x;
    u8 *anim_table;

    if (body->action_phase == 0) {
        apply_clamped_actor_value_delta(actor);
        body->action_phase = (u8) (body->action_phase + 1);
        motion->velocity_x = (u32) (rcos((actor->movement_facing)) << 9);
        motion->velocity_y = (s32) (rsin((actor->movement_facing)) << 9);
        body->action_timer = 0xCU;
    }
    if (((Rec_func_8008ACDC_arg0 *)body)->unk_10C & 1) {
        begin_player_damage_reaction(body, motion, sprite, actor);
        return;
    }
    if ((sprite->frameTable == player_damage_frames_2)
        && (sprite->flags & 0x6000)) {
        anim_frames = body->action_timer - 1;
        body->action_timer = anim_frames;
        if ((anim_frames << 0x10) > 0) {
            set_sprite_animation_frame(sprite, ((u8 *)sprite->frameTable)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + actor->facing + 0x100) >> 9) & 7], 0, 1);
        }
    }
    frames_left = body->action_timer;
    if (frames_left > 0) {
        pos_x = motion->x.v;
        pos_y = motion->y.v;
        motion->x.v = (s32) (pos_x + ((s32) ((((sprite->tile_x << 6) + 0x20)
            << 0x10) - pos_x) / frames_left));
        motion->y.v = (s32) (pos_y + ((s32) ((((sprite->tile_y << 6) + 0x20)
            << 0x10) - pos_y) / body->action_timer));
        velocity_x = ((u32)motion->velocity_x);
        motion->velocity_x = (u32) ((s32) (velocity_x + (velocity_x >> 0x1F)) >> 1);
        motion->velocity_y = (s32) ((s32) motion->velocity_y / 2);
        move_frames = body->action_timer - 1;
        body->action_timer = move_frames;
        if ((move_frames << 0x10) == 0) {
            motion->velocity_y = 0;
            motion->velocity_x = 0U;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        }
    }
    if (sprite->flags & 0xE000) {
        anim_table = player_wait_frames;
        sprite->frameTable = anim_table;
        set_sprite_animation_frame(sprite, anim_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0, 1);
        if (((s32)g_dungeon_status.pending_display_owner) == NODE_HEADER(actor)) {
            g_dungeon_status.pending_display_owner = (s32) (((s32)g_dungeon_status.pending_display_owner) & 0x7FFFFFFF);
        }
        if (actor->hp == 0) {
            if (dungeon_floor_flags & 0x08000000) {
                actor->hp = 1U;
            } else {
                actor->hp = 0U;
                reset_actor_motion_at_sprite_tile(body, motion, sprite, actor);
                return;
            }
        }
        next_timer = 8U;
        body->action_timer = next_timer;
        body->unk_8C.address = handle_player_input;
    }
}

