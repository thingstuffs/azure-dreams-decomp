#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"



typedef struct S_80172540_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172540_0;   /* arg0 in func_80172540 */




typedef struct S_80172540_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80172540_4;   /* global in func_80172540 */


M2C_UNK func_80047784();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
M2C_UNK func_800AD594();
s32 func_800AD9B4();

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801710F4;
extern u8 D_80174F20[];
extern u8 D_80174F28[];

/* Updates a jump toward the target tile and restores the actor when it finishes. */
void func_80172540(void *jump_state, void *motion, void *map_entity, void *actor) {
    s32 distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172540_0 *)jump_state)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_2;
    }
    goto tick;

state_0:
    if (((Rec_D_80082E80 *)map_entity)->unk_14.at00_u16.v & 0x6000) {
        (*(u8 * *)((u8 *)map_entity + 0x2C)) = D_80174F20;
        func_80047784(
            map_entity,
            D_80174F20[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_80172540_0 *)jump_state)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFEE0000;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= 0xF7FFFFFF;
        ((S_80172540_0 *)jump_state)->unk_A0 = 0;
        ((S_80172540_0 *)jump_state)->unk_9B++;
        goto state_1;
    }
    goto tick;

state_1:
    frames_left = ((S_80172540_0 *)jump_state)->unk_96.s;
    ((S_80172540_0 *)jump_state)->unk_90 -= ((S_80172540_0 *)jump_state)->unk_A0;
    if (frames_left != 0) {
        {
            s32 target_x = ((Rec_D_80082E80 *)map_entity)->unk_24 << 6;
            s32 current_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;

            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - current_x) << 16) / frames_left;
        }
        {
            s32 target_y = ((Rec_D_80082E80 *)map_entity)->unk_25 << 6;
            s32 current_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;

            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = ((target_y - current_y) << 16) /
                ((S_80172540_0 *)jump_state)->unk_96.s;
        }
        ((S_80172540_0 *)jump_state)->unk_A0 += ((Rec_D_800E3D7C *)motion)->unk_14.as_s32;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 += 0x40000;
    }
    ((S_80172540_0 *)jump_state)->unk_90 += ((S_80172540_0 *)jump_state)->unk_A0;
    if (((S_80172540_0 *)jump_state)->unk_96.s < 2) {
        ((S_80172540_0 *)jump_state)->unk_90 = 0;
        ((S_80172540_0 *)jump_state)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x08000000;
        ((S_80172540_0 *)jump_state)->unk_9B++;
    }

state_2:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x08000000) {
        ((S_80172540_0 *)jump_state)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25);
        (*(u8 * *)((u8 *)map_entity + 0x2C)) = D_80174F28;
        func_80047784(
            map_entity,
            D_80174F28[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_80172540_0 *)jump_state)->unk_9B++;
    }

tick:
    next_timer = ((S_80172540_0 *)jump_state)->unk_96.u - 1;
    ((S_80172540_0 *)jump_state)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25);
        func_800AD594(actor, 3);
        func_800A4ACC(actor);
        {
            void *action_counter = &D_80083460;

            if (((S_80172540_4 *)action_counter)->unk_08 != 0) {
                ((S_80172540_4 *)action_counter)->unk_08--;
            }
        }

        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32;
        if (actor_flags & 0x2000) {
            if (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) {
                ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                u8 *facing_target = D_80082E80;

                ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
                    ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25,
                    facing_target[0x24], facing_target[0x25], &distance);
            }
        }

finish:
        if ((func_800AD9B4(map_entity, actor) << 16) > 0) {
            ((S_80172540_0 *)jump_state)->unk_8C = &D_801710F4;
            func_800A9A04(actor);
        }
    }
}
