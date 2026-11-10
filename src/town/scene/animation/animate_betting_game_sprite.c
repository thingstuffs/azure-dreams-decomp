#include "common.h"
#include "town/scene/animation.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"

typedef struct S_80810454_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_80810454_0;   /* state_data in animate_betting_game_sprite */

typedef struct S_80810454_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80810454_1;   /* motion_data in animate_betting_game_sprite */

typedef struct S_80810454_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80810454_2;   /* ((S_80810454_0 *)state_data)->unk_04 in animate_betting_game_sprite */



/* Moves the sprite into place, bobs it, and marks it for removal after it moves out. */
void animate_betting_game_sprite(void *state_data_arg, S_80810454_1 *motion_data) {
    S_80810454_0 *state_data = state_data_arg;
    s16 state;

    if (((S_80810454_2 *)(state_data->unk_04))->unk_18 == 2) {
        state_data->unk_00 = 3;
    }
    state = state_data->unk_00;
    switch (state) {
    case 0:
    {
        s32 position;

        position = motion_data->unk_08;
        position += 0x100000;
        motion_data->unk_08 = position;
        if (position >= (s32)0xFF900000) {
            state_data->unk_02 = 0;
            motion_data->unk_14 = -0x40000;
            state_data->unk_00 = 1;
            return;
        }
        return;
    }

    case 1:
    {
        s32 old_speed;
        s32 position;
        s32 speed;

        position = motion_data->unk_08;
        old_speed = motion_data->unk_14;
        position += old_speed;
        motion_data->unk_08 = position;
        speed = motion_data->unk_14;
        speed += 0x4000;
        motion_data->unk_14 = speed;
        if (speed == 0x40000) {
            state_data->unk_00 = 2;
            return;
        }
        return;
    }

    case 2:
    {
        s32 position;
        s32 speed;

        position = motion_data->unk_08;
        speed = motion_data->unk_14;
        position += speed;
        motion_data->unk_08 = position;
        motion_data->unk_14 -= 0x8000;
        if (motion_data->unk_14 == -0x40000) {
            state_data->unk_00 = 1;
            return;
        }
        return;
    }

    case 0xF0:
    {
        s32 result;
        u16 phase;

        phase = (state_data->unk_02 + 1) & 0x7F;
        state_data->unk_02 = phase;
        result = func_8006A3A4(phase << 6);
        motion_data->unk_08 = (result << 7) + (s32)0xFF900000;
        return;
    }

    case 3:
    {
        s32 position;

        position = motion_data->unk_08;
        position -= 0x100000;
        motion_data->unk_08 = position;
        if (position <= (s32)0xFE000000) {
            *(u16 *)((u8 *)state_data - 2) |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        return;
    }
    }
}
