#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/player.h"
#include "dungeon/player/input.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgte.h"
#include "engine/graphics.h"

typedef struct S_80091C64_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x76];
    u16 unk_11A;
} S_80091C64_0;   /* arg0 in update_actor_hop_and_return */

#include "dungeon/player/object.h"
s32 play_sound_if_enabled(s32 query_value);

extern u8 player_hop_frames[];
extern u8 player_landing_frame_set[];

/* Animate a hop and return to the entity's tile, then restore its facing and behavior. */
void update_actor_hop_and_return(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 *next_behavior;
    s16 frames_left;
    u8 phase;
    u16 return_duration;
    s32 target_x;
    s32 current_x;
    s32 y_work;
    s32 y_origin;
    s32 y_remaining;
    s32 y_step;
    u16 delay_left;
    u16 hop_frames_left;
    u16 return_frames_left;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        delay_left = body->action_timer.u - 1;
        body->action_timer.u = delay_left;
        if ((s16) delay_left >= 9) {
            return;
        }
        sprite->frameTable = player_hop_frames;
        set_sprite_animation_frame(sprite, player_hop_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0, 1);
        body->action_state_flags = (u16) (body->action_state_flags | 0xC);
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        play_sound_if_enabled(0x701);
        return;
    case 1:
        if (body->action_timer.s != 0) {
            position->x.v = (s32) (position->x.v + (rcos(actor->facing + 0x400) << 6));
            position->y.v = (s32) (position->y.v + (rsin(actor->facing + 0x400) << 6));
            body->unk_90.parts.high.s = (s16) ((s32) (0 - rsin((s16) body->action_timer.u
                << 8)) >> 8);
        }
        hop_frames_left = body->action_timer.u - 1;
        body->action_timer.u = hop_frames_left;
        if ((hop_frames_left << 0x10) > 0) {
            return;
        }
        sprite->frameTable = player_landing_frame_set;
        set_sprite_animation_frame(sprite, player_landing_frame_set[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0, 1);
        body->unk_90.parts.high.s = 0;
        body->action_phase.u++;
        return;
    case 2:
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        sprite->frameTable = player_hop_frames;
        set_sprite_animation_frame(sprite, player_hop_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0, 1);
        return_duration = 8U;
        body->action_timer.u = return_duration;
        body->action_phase.u++;
        return;
    case 3:
        frames_left = (s16) body->action_timer.u;
        if (frames_left != 0) {
            target_x = sprite->tile_x << 6;
            current_x = position->x.w.i - 0x20;
            position->x.v = (s32) (position->x.v + ((target_x - current_x) << 0x10) / frames_left);
            y_step = sprite->tile_y;
            y_step <<= 6;
            y_origin = position->y.w.i - 0x20;
            {
                s32 y_numerator = (y_step - y_origin) << 0x10;

                y_remaining = body->action_timer.s;
                y_step = y_numerator / y_remaining;
            }
            y_work = position->y.v + y_step;
            position->y.v = y_work;
            body->unk_90.parts.high.s = (s16) ((s32) (0 - rsin((s16) body->action_timer.u
                << 8)) >> 8);
        }
        return_frames_left = body->action_timer.u - 1;
        body->action_timer.u = return_frames_left;
        if ((return_frames_left << 0x10) > 0) {
            return;
        }
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        body->unk_90.parts.high.s = 0;
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        sprite->frameTable = player_landing_frame_set;
        set_sprite_animation_frame(sprite, player_landing_frame_set[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0, 1);
        return;
    case 4:
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        actor->facing = (s16) ((S_80091C64_0 *)body)->unk_11A;
        if (actor->flags1C & 0x100000) {
            next_behavior = &handle_carrying_player_input;
        } else {
            next_behavior = handle_player_input;
        }
        body->unk_8C.address = next_behavior;
        actor->flags14 = (s32) (actor->flags14 & 0xFFFDFFFF);
        body->action_state_flags = (u16) (body->action_state_flags & 0xFFF3);
        body->unk_A0.parts.high = (u16) (body->unk_A0.parts.high | 0x10);
        return;
    }
}
