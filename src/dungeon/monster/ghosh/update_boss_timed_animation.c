#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/ghosh.h"
#include "sdk/libgte.h"

extern void select_sprite_entry(void *, s32, s32);

extern u8 ghosh_frame_set_8[];
extern u8 ghosh_frame_bank[];


typedef struct S_801740F8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_801740F8_2;   /* arg3 in update_boss_timed_animation */

/* Updates a timed animation offset and restores the actor's directional animation. */
void update_boss_timed_animation(ActorRecord *actor, ObjectPosition *transform, SpriteFrameState *animation, void *motion)
{
    s32 timer;
    s16 next_timer;
    s32 state;
    u8 *anim_table;

    state = actor->action_phase.u;
    switch (state) {
    case 0:
        anim_table = ghosh_frame_bank + 0x4A7C;
        if (*(u8 **)&animation->frameTable != anim_table) {
            (animation->frameTable) = anim_table;
            select_sprite_entry(
                animation,
                *(u8 *)(((((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801740F8_2 *)motion)->unk_2A + 0x100) >> 9) & 7))
                        + (u32)anim_table),
                0);
        }
        actor->action_state_flags |= 8;
        ((S_801740F8_2 *)motion)->unk_1C &= 0xF7FFFFFF;
        actor->unk_9E.s = 5;
        actor->unk_A4.value = 0;
        actor->action_phase.u++;
    case 1:
        timer = actor->unk_9E.s;
        actor->unk_90.value -= actor->unk_A4.value;
        if (timer != 0) {
            actor->unk_A4.value = -rsin(timer * 0x199) << 10;
        }

        actor->unk_90.value += actor->unk_A4.value;
        next_timer = (u16)actor->unk_9E.s - 1;
        actor->unk_9E.s = next_timer;
        if (next_timer < 0) {
            actor->unk_90.value = 0;
            actor->action_state_flags &= 0xFFF7;
            ((S_801740F8_2 *)motion)->unk_1C |= 0x08000000;
            actor->action_phase.u++;
        }
    case 2:
        if (!(((S_801740F8_2 *)motion)->unk_1C & 0x08000000)) {
            return;
        }
        actor->action_state_flags &= 0xFFF7;
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, animation->tile_x, animation->tile_y);
        actor->action_phase.u++;
        return;
    case 3:
        if (*(u8 **)&animation->frameTable != ghosh_frame_set_8 - 0x50) {
            (animation->frameTable) = ghosh_frame_set_8 - 0x50;
            select_sprite_entry(
                animation,
                (ghosh_frame_set_8 - 0x50)[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801740F8_2 *)motion)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
    }
}
