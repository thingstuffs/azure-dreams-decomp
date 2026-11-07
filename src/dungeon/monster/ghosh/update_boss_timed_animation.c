#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/ghosh.h"
#include "sdk/libgte.h"
#include "dungeon/data.h"

extern void select_sprite_entry(void *, s32, s32);


/* Updates a timed animation offset and restores the actor's directional animation. */
void update_boss_timed_animation(ActorRecord *actor, ObjectPosition *transform, SpriteFrameState *animation, ActorRecord *motion)
{
    s32 timer;
    s16 next_timer;
    s32 state;
    u8 *anim_table;

    state = actor->action_phase;
    switch (state) {
    case 0:
        anim_table = ghosh_frame_bank + 0x4A7C;
        if (*(u8 **)&animation->frameTable != anim_table) {
            (animation->frameTable) = anim_table;
            select_sprite_entry(
                animation,
                *(u8 *)(((((g_game_work.view.camera_rotation.parts.viewAngle + motion->facing + 0x100) >> 9) & 7))
                        + (u32)anim_table),
                0);
        }
        actor->action_state_flags |= 8;
        motion->flags1C &= 0xF7FFFFFF;
        actor->unk_9E = 5;
        actor->unk_A4.value = 0;
        actor->action_phase++;
    case 1:
        timer = (s16)actor->unk_9E;
        actor->unk_90.value -= actor->unk_A4.value;
        if (timer != 0) {
            actor->unk_A4.value = -rsin(timer * 0x199) << 10;
        }

        actor->unk_90.value += actor->unk_A4.value;
        next_timer = (u16)actor->unk_9E - 1;
        actor->unk_9E = next_timer;
        if (next_timer < 0) {
            actor->unk_90.value = 0;
            actor->action_state_flags &= 0xFFF7;
            motion->flags1C |= 0x08000000;
            actor->action_phase++;
        }
    case 2:
        if (!(motion->flags1C & 0x08000000)) {
            return;
        }
        actor->action_state_flags &= 0xFFF7;
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, animation->tile_x, animation->tile_y);
        actor->action_phase++;
        return;
    case 3:
        if (*(u8 **)&animation->frameTable != ghosh_frame_set_8 - 0x50) {
            (animation->frameTable) = ghosh_frame_set_8 - 0x50;
            select_sprite_entry(
                animation,
                (ghosh_frame_set_8 - 0x50)[((g_game_work.view.camera_rotation.parts.viewAngle + motion->facing + 0x100) >> 9) & 7],
                0);
        }
    }
}
