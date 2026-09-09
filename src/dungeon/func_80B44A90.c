#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"



typedef struct S_80172290_0 {
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
} S_80172290_0;   /* arg0 in func_80172290 */





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
extern u8 D_80170E70;
extern u8 D_80175A6C[];
extern u8 D_80175A74[];

/* Update a timed jump toward the actor's map tile and handle landing and completion. */
void func_80172290(void *action, void *motion, void *map_actor, void *actor) {
    s32 target_distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172290_0 *)action)->unk_9B;
    if (state == 1) {
        goto update_jump;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto start_jump;
        }
        goto tick;
    }
    if (state == 2) {
        goto check_landing;
    }
    goto tick;

start_jump:
    if (((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x6000) {
        (*(u8 * *)((u8 *)map_actor + 0x2C)) = D_80175A6C;
        func_80047784(
            map_actor,
            D_80175A6C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_80172290_0 *)action)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFF00000;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= 0xF7FFFFFF;
        ((S_80172290_0 *)action)->unk_A0 = 0;
        ((S_80172290_0 *)action)->unk_9B++;
        goto update_jump;
    }
    goto tick;

update_jump:
    frames_left = ((S_80172290_0 *)action)->unk_96.s;
    ((S_80172290_0 *)action)->unk_90 -= ((S_80172290_0 *)action)->unk_A0;
    if (frames_left != 0) {
        {
            s32 target_x = ((Rec_D_80082E80 *)map_actor)->unk_24 << 6;
            s32 current_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;

            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - current_x) << 16) / frames_left;
        }
        {
            s32 target_y = ((Rec_D_80082E80 *)map_actor)->unk_25 << 6;
            s32 current_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;

            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = ((target_y - current_y) << 16) /
                ((S_80172290_0 *)action)->unk_96.s;
        }
        ((S_80172290_0 *)action)->unk_A0 += ((Rec_D_800E3D7C *)motion)->unk_14.as_s32;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 += 0x40000;
    }
    ((S_80172290_0 *)action)->unk_90 += ((S_80172290_0 *)action)->unk_A0;
    if (((S_80172290_0 *)action)->unk_96.s < 0) {
        ((S_80172290_0 *)action)->unk_90 = 0;
        ((S_80172290_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x08000000;
        ((S_80172290_0 *)action)->unk_9B++;
    }

check_landing:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x08000000) {
        ((S_80172290_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);
        (*(u8 * *)((u8 *)map_actor + 0x2C)) = D_80175A74;
        func_80047784(
            map_actor,
            D_80175A74[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_80172290_0 *)action)->unk_9B++;
    }

tick:
    next_timer = ((S_80172290_0 *)action)->unk_96.u - 1;
    ((S_80172290_0 *)action)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        {
            u32 count;
            s16 *counter_words;
            s32 signed_count;

            counter_words = (s16 *)&D_80083460;
            signed_count = counter_words[4];
            count = ((u16 *)counter_words)[4];

            if (signed_count != 0) {
                counter_words[4] = count - 1;
            }
        }

        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32;
        if (actor_flags & 0x2000) {
            if (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) {
                ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                u8 *target = D_80082E80;

                ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
                    ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25,
                    target[0x24], target[0x25], &target_distance);
            }
        }

finish:
        if ((func_800AD9B4(map_actor, actor) << 16) > 0) {
            ((S_80172290_0 *)action)->unk_8C = &D_80170E70;
            func_800A9A04(actor);
        }
    }
}
