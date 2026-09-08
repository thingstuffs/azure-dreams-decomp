#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801722BC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_801722BC_0;   /* arg0 in func_801722BC */


typedef struct S_801722BC_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801722BC_2;   /* arg3 in func_801722BC */


typedef struct S_801722BC_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_801722BC_4;   /* counter_base in func_801722BC */



extern void func_80047784(void *, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E68[];
extern u8 D_80173884[];
extern u8 D_8017388C[];

/* Updates airborne movement, landing animation, and actor recovery when the timer expires. */
void func_801722BC(void *anim, void *motion, void *entity, void *actor)
{
    s32 direction_aux;
    s32 move_ticks;
    s32 acceleration;
    s32 origin_x;
    s32 origin_y;
    s32 height_offset;
    s32 height;
    s32 vertical_speed;
    s32 arc_ticks;
    s32 target_x;
    s16 next_tick;
    s32 actor_flags;
    u16 remaining_ticks;
    s32 phase;
    u8 *counter_base;

    phase = ((S_801722BC_0 *)anim)->unk_9B;
    if (phase == 1) {
        goto update_motion;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto start_motion;
        }
        goto update_timer;
    }
    if (phase == 2) {
        goto check_landing;
    }
    goto update_timer;

start_motion:
    if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x6000)) {
        goto update_timer;
    }
    (*(u8 * *)((u8 *)entity + 0x2C)) = D_80173884;
    func_80047784(
        entity,
        D_80173884[((D_80083228 + ((S_801722BC_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801722BC_0 *)anim)->unk_98 |= 8;
    ((S_801722BC_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFF00000;
    ((S_801722BC_0 *)anim)->unk_A0 = 0;
    ((S_801722BC_0 *)anim)->unk_9B++;

update_motion:
    move_ticks = ((S_801722BC_0 *)anim)->unk_A4.s;
    ((S_801722BC_0 *)anim)->unk_90 =
        ((S_801722BC_0 *)anim)->unk_90 - ((S_801722BC_0 *)anim)->unk_A0;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)entity)->unk_24 << 6;
        origin_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        origin_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            ((target_x - origin_x) << 16) /
            move_ticks;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)entity)->unk_25 << 6) - origin_y) << 16) /
            (s16)((S_801722BC_0 *)anim)->unk_A4.s;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        arc_ticks = ((S_801722BC_0 *)anim)->unk_A4.s;
        vertical_speed = ((Rec_D_800E3D7C *)motion)->unk_14.as_s32;
        ASM_KEEP(arc_ticks);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        acceleration =
            (arc_ticks << 15) + (arc_ticks << 13);
        vertical_speed += acceleration;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = vertical_speed;
        ((S_801722BC_0 *)anim)->unk_A0 += vertical_speed;
    }
    height = ((S_801722BC_0 *)anim)->unk_90;
    height_offset = ((S_801722BC_0 *)anim)->unk_A0;
    next_tick = ((S_801722BC_0 *)anim)->unk_A4.u - 1;
    height += height_offset;
    ((S_801722BC_0 *)anim)->unk_A4.s = next_tick;
    ((S_801722BC_0 *)anim)->unk_90 = height;
    if (next_tick < 0) {
        ((S_801722BC_0 *)anim)->unk_90 = 0;
        ((S_801722BC_0 *)anim)->unk_98 &= 0xFFF7;
        ((S_801722BC_2 *)actor)->unk_1C.s |= 0x08000000;
        ((S_801722BC_0 *)anim)->unk_9B++;
    }

check_landing:
    if (((S_801722BC_2 *)actor)->unk_1C.s & 0x08000000) {
        ((S_801722BC_0 *)anim)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_8017388C;
        func_80047784(
            entity,
            D_8017388C[((D_80083228 + ((S_801722BC_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)anim)->unk_9B++;
    }

update_timer:
    remaining_ticks = ((S_801722BC_0 *)anim)->unk_96 - 1;
    ((S_801722BC_0 *)anim)->unk_96 = remaining_ticks;
    if ((remaining_ticks << 16) <= 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);

        counter_base = (u8 *)&D_80083460;
        if (((S_801722BC_4 *)counter_base)->unk_08.s != 0) {
            ((S_801722BC_4 *)counter_base)->unk_08.u--;
        }

        actor_flags = ((S_801722BC_2 *)actor)->unk_1C.u;
        if (actor_flags & 0x2000) {
            if (((S_801722BC_2 *)actor)->unk_46 & 0x8000) {
                ((S_801722BC_2 *)actor)->unk_46 &= 0x7FFF;
            }
            goto check_followup;
        }
        if (actor_flags & 0x410) {
            goto check_followup;
        }
        if (!(actor_flags & 0x20000)) {
            goto check_followup;
        }
        ((S_801722BC_2 *)actor)->unk_2A = func_800A0818(
            ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &direction_aux);

check_followup:
        if ((func_800AD9B4(entity, actor) << 16) > 0) {
            ((S_801722BC_0 *)anim)->unk_8C = D_80170E68;
            func_800A9A04(actor);
        }
    }
}

/* MECHANISM: Four held arguments naturally give the 0x38 frame and s0/s1/s3/s2 save order.
   Named coordinate/delta and position/offset locals close both load-order residues.
   A guarded v0 timer pin plus a pre-load scheduling fence preserves the mflo nop and shift roles. */
