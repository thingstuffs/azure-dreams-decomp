#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_801750F8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801750F8_0;   /* arg0 in advance_deforming_action_animation */

typedef struct S_801750F8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801750F8_1;   /* arg3 in advance_deforming_action_animation */

typedef struct S_801750F8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801750F8_2;   /* arg2 in advance_deforming_action_animation */



extern s32 func_801744E0(void *);
extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);
extern void create_randomized_item_object(void *, void *, void *, void *);

extern u8 D_801716F4[];
extern u8 D_8017555C[];
extern u8 D_801755BC[];
extern u8 D_801755C4[];
extern u8 D_801755CC[];

/* Advances a timed action animation, deforming the sprite and restoring it on completion. */
void advance_deforming_action_animation(void *action_in, void *direction_data_in, void *sprite_in, void *actor_in)
{
    void *direction_data = direction_data_in;
    void *sprite = sprite_in;
    void *actor = actor_in;
    u8 state;

    state = ((S_801750F8_0 *)action_in)->unk_9B;
    switch (state) {
    case 0:
    {
        s32 facing_angle;
        s16 timer;
        u32 actor_flags;

        facing_angle = func_801744E0(direction_data);
        facing_angle = (facing_angle << 16) >> 7;
        ((S_801750F8_1 *)actor)->unk_2A = facing_angle;

        timer = ++((S_801750F8_0 *)action_in)->unk_96.s;
        if (timer >= 0x78) {
            ((S_801750F8_0 *)action_in)->unk_9B = 5;
            ((S_801750F8_0 *)action_in)->unk_96.s = 0;
            return;
        }

        actor_flags = ((S_801750F8_1 *)actor)->unk_14;
        if (!(actor_flags & 0x00800000)) {
            return;
        }
        ((S_801750F8_1 *)actor)->unk_14 = actor_flags & 0xFF7FFFFF;
        ((S_801750F8_0 *)action_in)->unk_96.s = 0;
        ((S_801750F8_0 *)action_in)->unk_9B++;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801755BC;
        select_sprite_entry(sprite,
            D_801755BC[((g_game_work.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x51E);
        return;
    }

    case 1:
        if (!(((S_801750F8_2 *)sprite)->unk_14 & 0x6000)) {
            return;
        }
        ((S_801750F8_0 *)action_in)->unk_96.s = 0;
        ((S_801750F8_0 *)action_in)->unk_9B++;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801755CC;
        select_sprite_entry(sprite,
            D_801755CC[((g_game_work.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801750F8_2 *)sprite)->unk_14 |= 0x0800;
        return;

    case 2:
    {
        s16 timer;

        timer = ++((S_801750F8_0 *)action_in)->unk_96.s;
        if (timer < 0xF) {
            return;
        }
        ((S_801750F8_0 *)action_in)->unk_96.s = 0;
        ((S_801750F8_0 *)action_in)->unk_9B++;
        ((S_801750F8_2 *)sprite)->unk_14 &= 0xF7FF;
        return;
    }

    case 3:
    {
        s32 scale_x;
        s32 scale_y;
        s16 timer;

        timer = ++((S_801750F8_0 *)action_in)->unk_96.s;
        if (timer < 3) {
            scale_x = ((S_801750F8_2 *)sprite)->unk_1C - 0x258;
            scale_y = ((S_801750F8_2 *)sprite)->unk_1E + 0x258;
            ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
            ((S_801750F8_2 *)sprite)->unk_1E = scale_y;
            play_sound_if_enabled(0x51F);
        } else if (timer < 7) {
            scale_x = ((S_801750F8_2 *)sprite)->unk_1C;
            scale_y = ((S_801750F8_2 *)sprite)->unk_1E;
            scale_x += 0x258;
            scale_y -= 0x258;
            ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
            ((S_801750F8_2 *)sprite)->unk_1E = scale_y;
        } else if (timer < 0xB) {
            scale_x = ((S_801750F8_2 *)sprite)->unk_1C - 0x258;
            scale_y = ((S_801750F8_2 *)sprite)->unk_1E + 0x258;
            ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
            ((S_801750F8_2 *)sprite)->unk_1E = scale_y;
            play_sound_if_enabled(0x51F);
        } else {
            if (timer < 0xF) {
                scale_x = ((S_801750F8_2 *)sprite)->unk_1C;
                scale_y = ((S_801750F8_2 *)sprite)->unk_1E;
                scale_x += 0x258;
                scale_y -= 0x258;
                ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
                ((S_801750F8_2 *)sprite)->unk_1E = scale_y;
            } else if (timer < 0x11) {
                scale_x = ((S_801750F8_2 *)sprite)->unk_1C - 0x258;
                scale_y = ((S_801750F8_2 *)sprite)->unk_1E + 0x258;
                ((S_801750F8_2 *)sprite)->unk_1C = scale_x;
                ((S_801750F8_2 *)sprite)->unk_1E = scale_y;
            }
        }

        if (((S_801750F8_0 *)action_in)->unk_96.u < 0x14) {
            return;
        }
        ((S_801750F8_0 *)action_in)->unk_96.s = 0;
        ((S_801750F8_0 *)action_in)->unk_9B++;
        ((S_801750F8_2 *)sprite)->unk_1E = 0x1000;
        ((S_801750F8_2 *)sprite)->unk_1C = 0x1000;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801755C4;
        select_sprite_entry(sprite,
            D_801755C4[((g_game_work.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x509);
        create_randomized_item_object(action_in, direction_data, sprite, actor);
        return;
    }

    case 4:
    {
        s16 timer;

        timer = ++((S_801750F8_0 *)action_in)->unk_96.s;
        if (timer < 9) {
            return;
        }
        ((S_801750F8_0 *)action_in)->unk_96.s = 0;
        ((S_801750F8_0 *)action_in)->unk_9B++;
        return;
    }

    case 5:
    {

        g_dungeon_status.unk_0A--;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017555C;
        select_sprite_entry(sprite,
            D_8017555C[((g_game_work.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        reduce_actor_food_meter(actor, 0x1000);
        ((S_801750F8_0 *)action_in)->unk_8C = D_801716F4;
        g_dungeon_status.unk_0C = 0;
        ((S_801750F8_1 *)actor)->unk_46 &= 0x7FFF;
    }
    }

    return;
}

/* MECHANISM: pin-free at 2.7.2-cdk-G0. Testing timer < 3 first, then
   < 7, < 11, < 15 and < 17, retains both squash/stretch sites and the shared
   completion path. The short deformation-and-sound tail is copied for the
   two low-timer intervals; all four original gotos are removed byte-exactly. */
