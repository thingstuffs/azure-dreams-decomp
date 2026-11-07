#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/monster/kewne.h"
#include "dungeon/data.h"

extern u8 kewne_action_resume_address[];
extern u8 D_80175ED0[];





/* Advances an actor's turn-and-animation sequence and restores its saved heading. */
void advance_turn_animation_and_restore_heading(ActorRecord *actor, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *transform_in) {
    ActorRecord *transform = transform_in;
    s32 heading;
    u8 phase;
    GameWork *scene_state = &g_game_work;

    phase = actor->action_phase;
    switch (phase) {
    case 0:
        heading = (u16)transform->facing & 0xFFF;
        transform->facing = heading;
        if (((0x400 - ((((u16)scene_state->view.camera_rotation.parts.viewAngle) + 0x100) & 0xE00)) & 0xE00) != heading) {
            transform->facing = heading + 0x200;
            return;
        }
        phase = actor->action_phase + 1;
        actor->action_phase = phase;
        return;
    case 1:
        if (actor->unk_90.parts.high.s == 0) {
            {
                u8 *animation_table = kewne_frame_set_4;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->facing + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->action_phase + 1;
            actor->action_phase = phase;
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
                    + (s16) transform->facing + 0x100) >> 9) & 7);
                animation_entry += (unsigned long)animation_table;
                select_sprite_entry(animation, *(u8 *)animation_entry, 0);
            }
        }
        phase = actor->action_phase + 1;
        actor->action_phase = phase;
        return;
    case 2:
        if (animation->flags & 0xE000) {
            {
                u8 *animation_table;
                animation_table = D_80175ED0;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->facing + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->action_phase + 1;
            actor->action_phase = phase;
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
                        + (s16) transform->facing + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->action_phase + 1;
            actor->action_phase = phase;
            return;
        }
        if (dungeon_actor_ring_anchor->action_id != 0x17) {
            {
                u8 *animation_table = kewne_frame_set_4;
                animation->frameTable = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                        + (s16) transform->facing + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    select_sprite_entry(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->action_phase + 1;
            actor->action_phase = phase;
            return;
        }
        return;
    }
        phase = actor->action_phase + 1;
        actor->action_phase = phase;
        return;
    case 4:
        if (animation->flags & 0xE000) {
            transform->flags1C = (s32) (transform->flags1C | 0x40000);
            {
                u8 *animation_table = kewne_turn_frames;
                animation->frameTable = animation_table;
                select_sprite_entry(animation, animation_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) transform->facing
                    + 0x100) >> 9) & 7], 0);
            }
            actor->unk_8C.word_ptr = kewne_action_resume_address;
            transform->facing = (u16) actor->unk_B0.halves.low.u;
            actor->unk_B0.halves.high.s = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        return;
    default:
        return;
    }
}
