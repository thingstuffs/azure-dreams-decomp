/* Relink of matched dungeon/func_80E658F8; every changed retail word is a paired relocation. */
#define dungeonAdvanceDeformingActionAnimation func_8016F0F8
#define D_801716F4 D_8016B6F4
#define D_8017555C D_8016F55C
#define D_801755BC D_8016F5BC
#define D_801755C4 D_8016F5C4
#define D_801755CC D_8016F5CC
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
} S_801750F8_0;   /* arg0 in func_8016F0F8 */

typedef struct S_801750F8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801750F8_1;   /* arg3 in func_8016F0F8 */

typedef struct S_801750F8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801750F8_2;   /* arg2 in func_8016F0F8 */



extern s32 func_8016E4E0(void *);
extern void func_80047784(void *, s32, s32);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern void func_8016ED98(void *, void *, void *, void *);

extern u8 D_8016B6F4[];
extern u8 D_8016F55C[];
extern u8 D_8016F5BC[];
extern u8 D_8016F5C4[];
extern u8 D_8016F5CC[];

/* Advances a timed action animation, deforming the sprite and restoring it on completion. */
void func_8016F0F8(void *action_in, void *direction_data_in, void *sprite_in, void *actor_in)
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

        facing_angle = func_8016E4E0(direction_data);
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
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016F5BC;
        func_80047784(sprite,
            D_8016F5BC[((gameWork.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800A56E0(0x51E);
        return;
    }

    case 1:
        if (!(((S_801750F8_2 *)sprite)->unk_14 & 0x6000)) {
            return;
        }
        ((S_801750F8_0 *)action_in)->unk_96.s = 0;
        ((S_801750F8_0 *)action_in)->unk_9B++;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016F5CC;
        func_80047784(sprite,
            D_8016F5CC[((gameWork.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
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
            func_800A56E0(0x51F);
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
            func_800A56E0(0x51F);
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
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016F5C4;
        func_80047784(sprite,
            D_8016F5C4[((gameWork.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_800A56E0(0x509);
        func_8016ED98(action_in, direction_data, sprite, actor);
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

        dungeonStatus.unk_0A--;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016F55C;
        func_80047784(sprite,
            D_8016F55C[((gameWork.view.viewAngle + ((S_801750F8_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        dungeonReduceActorFoodMeter(actor, 0x1000);
        ((S_801750F8_0 *)action_in)->unk_8C = D_8016B6F4;
        dungeonStatus.unk_0C = 0;
        ((S_801750F8_1 *)actor)->unk_46 &= 0x7FFF;
    }
    }

    return;
}

/* MECHANISM: pin-free at 2.7.2-cdk-G0. Testing timer < 3 first, then
   < 7, < 11, < 15 and < 17, retains both squash/stretch sites and the shared
   completion path. The short deformation-and-sound tail is copied for the
   two low-timer intervals; all four original gotos are removed byte-exactly. */
