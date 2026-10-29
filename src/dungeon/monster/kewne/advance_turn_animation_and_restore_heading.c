#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/monster/kewne.h"

extern u8 kewne_action_resume_address[];
extern u8 kewne_turn_frames[];
extern u8 kewne_frame_set_4[];
extern u8 D_80175ED0[];

typedef struct S_80172480_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u16 unk_B0;
    s16 unk_B2;
} S_80172480_0;   /* arg0 in advance_turn_animation_and_restore_heading */

typedef struct S_80172480_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
} S_80172480_1;   /* arg3 in advance_turn_animation_and_restore_heading */

typedef struct S_80172480_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80172480_4;   /* D_800E3D7C[0] in advance_turn_animation_and_restore_heading */

/* Advances an actor's turn-and-animation sequence and restores its saved heading. */
void advance_turn_animation_and_restore_heading(S_80172480_0 *actor, ObjectPosition *unused, SpriteFrameState *animation, S_80172480_1 *transform_in) {
    S_80172480_1 *transform = transform_in;
    s32 heading;
    u8 phase;
    GameWork *scene_state = &g_game_work;

    phase = actor->unk_9B;
    switch (phase) {
    case 0:
        heading = transform->unk_2A & 0xFFF;
        transform->unk_2A = heading;
        if (((0x400 - ((((u16)scene_state->view.camera_rotation.parts.viewAngle) + 0x100) & 0xE00)) & 0xE00) != heading) {
            transform->unk_2A = heading + 0x200;
            return;
        }
        phase = actor->unk_9B + 1;
        actor->unk_9B = phase;
        return;
    case 1:
        if (actor->unk_92 == 0) {
            {
                u8 *animation_table = kewne_frame_set_4;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        if ((animation->flags & 0x8000) == 0) {
            return;
        }
        {
            u8 *animation_table = kewne_frame_set_4;
            animation->frameTable = animation_table;
            {
                unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                    + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                animation_entry += (unsigned long)animation_table;
                select_sprite_entry(animation, *(u8 *)animation_entry, 0);
            }
        }
        phase = actor->unk_9B + 1;
        actor->unk_9B = phase;
        return;
    case 2:
        if (animation->flags & 0xE000) {
            {
                u8 *animation_table;
                animation_table = (u8 *)D_80175ED0;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        return;
    case 3:
    {
        u16 scene_status = ((u16)scene_state->buttons);
        if (scene_status != 0) {
            {
                u8 *animation_table = kewne_frame_set_4;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        if (dungeon_actor_ring_anchor->action_id.u != 0x17) {
            {
                u8 *animation_table = kewne_frame_set_4;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        return;
    }
        phase = actor->unk_9B + 1;
        actor->unk_9B = phase;
        return;
    case 4:
        if (animation->flags & 0xE000) {
            transform->unk_1C = (s32) (transform->unk_1C | 0x40000);
            {
                u8 *animation_table = kewne_turn_frames;
                animation->frameTable = animation_table;
                select_sprite_entry(animation, animation_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) transform->unk_2A
                    + 0x100) >> 9) & 7], 0);
            }
            actor->unk_8C = kewne_action_resume_address;
            transform->unk_2A = (u16) actor->unk_B0;
            actor->unk_B2 = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        return;
    default:
        return;
    }
}
