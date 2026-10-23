#include "common.h"

typedef struct S_80810454_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_80810454_0;   /* state_data in animate_betting_game_sprite */

typedef struct S_80810454_1 {
    u8 pad_00[0x8];
    union { s32 s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x8];
    union { s32 s; s32 u; } unk_14;   /* accessed as both */
} S_80810454_1;   /* motion_data in animate_betting_game_sprite */

typedef struct S_80810454_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80810454_2;   /* ((S_80810454_0 *)state_data)->unk_04 in animate_betting_game_sprite */


extern s32 func_8006A3A4();
extern s32 scene_object_flags;

/* Moves the sprite into place, bobs it, and marks it for removal after it moves out. */
void animate_betting_game_sprite(void *state_data, S_80810454_1 *motion_data) {
    s16 state;

    if (((S_80810454_2 *)(((S_80810454_0 *)state_data)->unk_04))->unk_18 == 2) {
        ((S_80810454_0 *)state_data)->unk_00 = 3;
    }
    state = ((S_80810454_0 *)state_data)->unk_00;
    switch (state) {
    case 0:
    {
        s32 position;

        position = motion_data->unk_08.s;
        position += 0x100000;
        motion_data->unk_08.s = position;
        if (position >= (s32)0xFF900000) {
            ((S_80810454_0 *)state_data)->unk_02 = 0;
            motion_data->unk_14.s = -0x40000;
            ((S_80810454_0 *)state_data)->unk_00 = 1;
            return;
        }
        return;
    }

    case 1:
    {
        s32 old_speed;
        s32 position;
        s32 speed;

        position = motion_data->unk_08.u;
        old_speed = motion_data->unk_14.u;
        position += old_speed;
        motion_data->unk_08.s = position;
        speed = motion_data->unk_14.u;
        speed += 0x4000;
        motion_data->unk_14.s = speed;
        if (speed == 0x40000) {
            ((S_80810454_0 *)state_data)->unk_00 = 2;
            return;
        }
        return;
    }

    case 2:
    {
        s32 position;
        s32 speed;

        position = motion_data->unk_08.s;
        speed = motion_data->unk_14.s;
        position += speed;
        motion_data->unk_08.s = position;
        motion_data->unk_14.s -= 0x8000;
        if (motion_data->unk_14.s == -0x40000) {
            ((S_80810454_0 *)state_data)->unk_00 = 1;
            return;
        }
        return;
    }

    case 0xF0:
    {
        s32 result;
        u16 phase;

        phase = (((S_80810454_0 *)state_data)->unk_02 + 1) & 0x7F;
        ((S_80810454_0 *)state_data)->unk_02 = phase;
        result = func_8006A3A4(phase << 6);
        motion_data->unk_08.s = (result << 7) + (s32)0xFF900000;
        return;
    }

    case 3:
    {
        s32 position;

        position = motion_data->unk_08.s;
        position -= 0x100000;
        motion_data->unk_08.s = position;
        if (position <= (s32)0xFE000000) {
            *(u16 *)((u8 *)state_data - 2) |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        return;
    }
    }
}
