#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);

extern u8 ghosh_frame_set_8[];
extern u8 ghosh_frame_bank[];

typedef struct S_801740F8_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_801740F8_0;   /* arg0 in update_boss_timed_animation */

typedef struct S_801740F8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_801740F8_2;   /* arg3 in update_boss_timed_animation */

/* Updates a timed animation offset and restores the actor's directional animation. */
void update_boss_timed_animation(void *actor, ObjectPosition *transform, SpriteFrameState *animation, void *motion)
{
    s32 timer;
    s16 next_timer;
    s32 state;
    u8 *anim_table;

    state = ((S_801740F8_0 *)actor)->unk_9B;
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
        ((S_801740F8_0 *)actor)->unk_98 |= 8;
        ((S_801740F8_2 *)motion)->unk_1C &= 0xF7FFFFFF;
        ((S_801740F8_0 *)actor)->unk_9E = 5;
        ((S_801740F8_0 *)actor)->unk_A4 = 0;
        ((S_801740F8_0 *)actor)->unk_9B++;
    case 1:
        timer = ((S_801740F8_0 *)actor)->unk_9E;
        ((S_801740F8_0 *)actor)->unk_90 -= ((S_801740F8_0 *)actor)->unk_A4;
        if (timer != 0) {
            ((S_801740F8_0 *)actor)->unk_A4 = -rsin(timer * 0x199) << 10;
        }

        ((S_801740F8_0 *)actor)->unk_90 += ((S_801740F8_0 *)actor)->unk_A4;
        next_timer = (u16)((S_801740F8_0 *)actor)->unk_9E - 1;
        ((S_801740F8_0 *)actor)->unk_9E = next_timer;
        if (next_timer < 0) {
            ((S_801740F8_0 *)actor)->unk_90 = 0;
            ((S_801740F8_0 *)actor)->unk_98 &= 0xFFF7;
            ((S_801740F8_2 *)motion)->unk_1C |= 0x08000000;
            ((S_801740F8_0 *)actor)->unk_9B++;
        }
    case 2:
        if (!(((S_801740F8_2 *)motion)->unk_1C & 0x08000000)) {
            return;
        }
        ((S_801740F8_0 *)actor)->unk_98 &= 0xFFF7;
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, animation->tile_x, animation->tile_y);
        ((S_801740F8_0 *)actor)->unk_9B++;
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
