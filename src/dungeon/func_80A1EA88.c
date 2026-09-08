#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172288_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172288_0;   /* arg0 in func_80172288 */



typedef struct S_80172288_3 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172288_3;   /* counter in func_80172288 */




typedef struct {
    u16 x;
    u16 y;
} PathPoint;

typedef struct {
    PathPoint point[8];
} PathTable;

extern void func_80047784(void *, u8, s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170838[16];
extern s32 D_80170E84;
extern u8 D_80174820[];

/* Updates an actor's jump motion, landing animation, and completion state. */
void func_80172288(u8 *motion, u8 *position, u8 *sprite, u8 *actor)
{
    PathTable frame_path;
    s32 facing_result;
    s32 frames_left;
    s32 current_y;
    s16 timer;
    s32 actor_flags;
    s32 phase;
    u8 phase_value;
    u8 *global_counter;

    frame_path = *(PathTable *)D_80170838;
    phase = ((S_80172288_0 *)motion)->unk_9B;
    if (phase == 1) {
        goto airborne;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto takeoff;
        }
        goto tick_timer;
    }
    if (phase == 2) {
        goto landing;
    }
    goto tick_timer;

takeoff:
    if (((S_80172288_0 *)motion)->unk_96 < 8) {
        ((S_80172288_0 *)motion)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0xFFEE0000;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= 0xF7FFFFFF;
        phase_value = *(volatile u8 *)(motion + 0x9B);
        ((S_80172288_0 *)motion)->unk_A0 = 0;
        goto advance_phase;
    }
    goto tick_timer;

airborne:
    frames_left = ((S_80172288_0 *)motion)->unk_96;
    ((S_80172288_0 *)motion)->unk_90 -= ((S_80172288_0 *)motion)->unk_A0;
    if (frames_left != 0) {
        {
            s32 target_x;
            s32 current_x;

            target_x = sprite[0x24];
            current_x = ((Rec_D_800E3D7C *)position)->unk_00.at02_s16.v;
            target_x <<= 6;
            current_x -= 0x20;
            ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 =
                ((target_x - current_x) << 16) / frames_left;
        }
        current_y = ((Rec_D_800E3D7C *)position)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v =
            (((sprite[0x25] << 6) - current_y) << 16) /
            ((S_80172288_0 *)motion)->unk_96;
        ((S_80172288_0 *)motion)->unk_A0 += ((Rec_D_800E3D7C *)position)->unk_14.as_s32;
        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 += 0x40000;
    }
    ((S_80172288_0 *)motion)->unk_90 += ((S_80172288_0 *)motion)->unk_A0;
    if (((S_80172288_0 *)motion)->unk_96 < 3) {
        ((S_80172288_0 *)motion)->unk_90 = 0;
        ((S_80172288_0 *)motion)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 |= 0x08000000;
        ((S_80172288_0 *)motion)->unk_9B++;
    }

landing:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x08000000) {
        ((S_80172288_0 *)motion)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 = 0;
        func_800A2B04(position, sprite[0x24], sprite[0x25]);
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174820;
        func_80047784(
            sprite,
            D_80174820[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        phase_value = ((S_80172288_0 *)motion)->unk_9B;
advance_phase:
        ((S_80172288_0 *)motion)->unk_9B = phase_value + 1;
    }

tick_timer:
    timer = ((S_80172288_0 *)motion)->unk_96 - 1;
    ((S_80172288_0 *)motion)->unk_96 = timer;
    if ((timer << 16) <= 0) {
        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 = 0;
        func_800A2B04(position, sprite[0x24], sprite[0x25]);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);

        global_counter = (u8 *)&D_80083460;
        if (((S_80172288_3 *)global_counter)->unk_08.s != 0) {
            ((S_80172288_3 *)global_counter)->unk_08.u--;
        }

        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
        if (actor_flags & 0x2000) {
            if (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) {
                ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
                goto update_actor;
            }
            goto update_actor;
        }
        if (actor_flags & 0x410) {
            goto update_actor;
        }
        if (!(actor_flags & 0x20000)) {
            goto update_actor;
        }
        ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
            sprite[0x24], sprite[0x25], D_80082E80[0x24], D_80082E80[0x25],
            &facing_result);

update_actor:
        if ((func_800AD9B4(sprite, actor) << 16) > 0) {
            ((S_80172288_0 *)motion)->unk_8C = &D_80170E84;
            func_800A9A04(actor);
            goto update_position;
        }
    } else {
update_position:
        ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = frame_path.point[((S_80172288_0 *)motion)->unk_96].x;
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = frame_path.point[((S_80172288_0 *)motion)->unk_96].y;
    }
}

/* MECHANISM: The 32-byte PathTable copy fixes the 0x58 frame and stack slots.
   Block-scoped target_x/current_x ranges force retail's lbu/lh/sll/addiu order.
   A dedicated u8 phase_value merges both predecessors at the load-delay nop. */
