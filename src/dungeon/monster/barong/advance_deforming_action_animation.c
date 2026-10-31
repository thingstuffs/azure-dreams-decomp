#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801750F8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801750F8_1;   /* arg3 in advance_deforming_action_animation */

extern s32 func_801744E0(void *);
extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void create_randomized_item_object(ActorRecord *, ObjectPosition *, SpriteFrameState *, void *);

extern u8 barong_action_resume_address[];
extern u8 barong_frame_set_1[];
extern u8 D_801755BC[];
extern u8 D_801755C4[];
extern u8 barong_frame_set_3[];

/* Advances a timed action animation, deforming the sprite and restoring it on completion. */
void advance_deforming_action_animation(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite_in, void *actor_in)
{
    void *direction_data = position;
    SpriteFrameState *sprite= sprite_in;
    S_801750F8_1 *actor = actor_in;
    u8 state;

    state = body->action_phase.u;
    switch (state) {
    case 0:
    {
        s32 facing_angle;
        s16 timer;
        u32 actor_flags;

        facing_angle = func_801744E0(direction_data);
        facing_angle = (facing_angle << 16) >> 7;
        actor->unk_2A = facing_angle;

        timer = ++body->action_timer.u;
        if (timer >= 0x78) {
            body->action_phase.u = 5;
            body->action_timer.u = 0;
            return;
        }

        actor_flags = actor->unk_14;
        if (!(actor_flags & 0x00800000)) {
            return;
        }
        actor->unk_14 = actor_flags & 0xFF7FFFFF;
        body->action_timer.u = 0;
        body->action_phase.u++;
        (sprite->frameTable) = D_801755BC;
        select_sprite_entry(sprite,
            D_801755BC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x51E);
        return;
    }

    case 1:
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        body->action_timer.u = 0;
        body->action_phase.u++;
        (sprite->frameTable) = barong_frame_set_3;
        select_sprite_entry(sprite,
            barong_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
            0);
        sprite->flags |= 0x0800;
        return;

    case 2:
    {
        s16 timer;

        timer = ++body->action_timer.u;
        if (timer < 0xF) {
            return;
        }
        body->action_timer.u = 0;
        body->action_phase.u++;
        sprite->flags &= 0xF7FF;
        return;
    }

    case 3:
    {
        s32 scale_x;
        s32 scale_y;
        s16 timer;

        timer = ++body->action_timer.u;
        if (timer < 3) {
            scale_x = sprite->scale_x - 0x258;
            scale_y = sprite->scale_y + 0x258;
            sprite->scale_x = scale_x;
            sprite->scale_y = scale_y;
            play_sound_if_enabled(0x51F);
        } else if (timer < 7) {
            scale_x = sprite->scale_x;
            scale_y = sprite->scale_y;
            scale_x += 0x258;
            scale_y -= 0x258;
            sprite->scale_x = scale_x;
            sprite->scale_y = scale_y;
        } else if (timer < 0xB) {
            scale_x = sprite->scale_x - 0x258;
            scale_y = sprite->scale_y + 0x258;
            sprite->scale_x = scale_x;
            sprite->scale_y = scale_y;
            play_sound_if_enabled(0x51F);
        } else {
            if (timer < 0xF) {
                scale_x = sprite->scale_x;
                scale_y = sprite->scale_y;
                scale_x += 0x258;
                scale_y -= 0x258;
                sprite->scale_x = scale_x;
                sprite->scale_y = scale_y;
            } else if (timer < 0x11) {
                scale_x = sprite->scale_x - 0x258;
                scale_y = sprite->scale_y + 0x258;
                sprite->scale_x = scale_x;
                sprite->scale_y = scale_y;
            }
        }

        if (body->action_timer.s < 0x14) {
            return;
        }
        body->action_timer.u = 0;
        body->action_phase.u++;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        (sprite->frameTable) = D_801755C4;
        select_sprite_entry(sprite,
            D_801755C4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x509);
        create_randomized_item_object(body, direction_data, sprite, actor);
        return;
    }

    case 4:
    {
        s16 timer;

        timer = ++body->action_timer.u;
        if (timer < 9) {
            return;
        }
        body->action_timer.u = 0;
        body->action_phase.u++;
        return;
    }

    case 5:
    {

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        (sprite->frameTable) = barong_frame_set_1;
        select_sprite_entry(sprite,
            barong_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
            0);
        spend_actor_mp(actor, 0x1000);
        body->unk_8C.byte_ptr = barong_action_resume_address;
        g_dungeon_status.active_actor = 0;
        actor->unk_46 &= 0x7FFF;
    }
    }

    return;
}

/* MECHANISM: Testing timer < 3 first, then < 7, < 11, < 15 and < 17, retains both squash/stretch sites
   and the shared completion path. The short deformation-and-sound tail is copied for the two low-timer
   intervals; all four original gotos are removed byte-exactly. */
