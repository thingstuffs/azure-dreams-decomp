#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801733B4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
    u8 pad_A8[0x2];
    union { u16 s; s16 u; } unk_AA;   /* accessed as both */
} S_801733B4_0;   /* arg0 in func_801733B4 */

typedef struct S_801733B4_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801733B4_1;   /* arg3 in func_801733B4 */





extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2348[];
extern u8 D_800E2368[];
extern u8 D_800E2370[];
extern s32 D_80171F1C;

/* Advances the actor's hop animation and finishes the action when its timer expires. */
void func_801733B4(void *motion, void *position, void *sprite, void *actor)
{
    s32 facing_aux;
    s32 y_offset;
    u16 timer_value;
    s32 phase;

    phase = ((S_801733B4_0 *)motion)->unk_9B;
    if (phase == 1) {
        goto state_one;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_zero;
        }
        goto update_timer;
    }
    if (phase == 2) {
        goto state_two;
    }
    if (phase == 3) {
        goto state_three;
    }
    goto update_timer;

state_zero:
    timer_value = ((S_801733B4_0 *)motion)->unk_AA.s + 1;
    ((S_801733B4_0 *)motion)->unk_AA.s = timer_value;
    if ((s16)timer_value < 2) {
        goto update_timer;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2368;
    func_80047784(sprite,
        D_800E2368[((D_80083228 + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801733B4_0 *)motion)->unk_98 |= 8;
    ((S_801733B4_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
    ((S_801733B4_0 *)motion)->unk_AA.s = 5;
    ((S_801733B4_0 *)motion)->unk_A4 = 0;
    ((S_801733B4_0 *)motion)->unk_9B++;

state_one:
    ((S_801733B4_0 *)motion)->unk_90.at00.v -= ((S_801733B4_0 *)motion)->unk_A4;
    if (((S_801733B4_0 *)motion)->unk_AA.u != 0) {
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 =
            (((((Rec_D_80082E80 *)sprite)->unk_24 << 6) -
              ({ ((Rec_D_800E3D7C *)position)->unk_00.at02_s16.v - 0x20; })) << 16) /
            ((S_801733B4_0 *)motion)->unk_AA.u;
        y_offset = ((Rec_D_800E3D7C *)position)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - y_offset) << 16) /
            ((S_801733B4_0 *)motion)->unk_AA.u;
        ((S_801733B4_0 *)motion)->unk_A4 =
            (-func_800644B8(((S_801733B4_0 *)motion)->unk_AA.u * 0x199)) << 10;
    }
    ((S_801733B4_0 *)motion)->unk_90.at00.v += ((S_801733B4_0 *)motion)->unk_A4;
    timer_value = ((S_801733B4_0 *)motion)->unk_AA.s - 1;
    ((S_801733B4_0 *)motion)->unk_AA.s = timer_value;
    if ((s16)timer_value < 0) {
        ((S_801733B4_0 *)motion)->unk_90.at02.v = -0x10;
        ((S_801733B4_0 *)motion)->unk_98 &= 0xFFF7;
        ((S_801733B4_1 *)actor)->unk_1C.s |= 0x08000000;
        ((S_801733B4_0 *)motion)->unk_9B++;
    }

state_two:
    if (((S_801733B4_1 *)actor)->unk_1C.s & 0x08000000) {
        ((S_801733B4_0 *)motion)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 = 0;
        func_800A2B04(position, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2370;
        func_80047784(sprite,
            D_800E2370[((D_80083228 + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801733B4_0 *)motion)->unk_9B++;
        goto update_timer;
    }
    goto update_timer;

state_three:
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_800E2348) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2348;
        func_80047784(sprite,
            D_800E2348[((D_80083228 + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801733B4_0 *)motion)->unk_9E = 0;
    }

update_timer:
    timer_value = ((S_801733B4_0 *)motion)->unk_96 - 1;
    ((S_801733B4_0 *)motion)->unk_96 = timer_value;
    if (((s32)timer_value << 16) <= 0) {
        s32 actor_flags;
        s16 *global_counters;

        ((Rec_D_800E3D7C *)position)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)position)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)position)->unk_0C.as_s32 = 0;
        func_800A2B04(position, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        global_counters = (s16 *)&D_80083460;
        if (global_counters[4] != 0) {
            ((u16 *)global_counters)[4]--;
        }
        actor_flags = ((S_801733B4_1 *)actor)->unk_1C.u;
        if (actor_flags & 0x2000) {
            if (((S_801733B4_1 *)actor)->unk_46 & 0x8000) {
                ((S_801733B4_1 *)actor)->unk_46 &= 0x7FFF;
                goto check_actor;
            }
        } else {
            if (actor_flags & 0x410) {
                goto check_actor;
            }
            if (!(actor_flags & 0x20000)) {
                goto check_actor;
            }
            ((S_801733B4_1 *)actor)->unk_2A = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &facing_aux);
        }

check_actor:
        if ((func_800AD9B4(sprite, actor) << 16) > 0) {
            ((S_801733B4_0 *)motion)->unk_8C = &D_80171F1C;
            func_800A9A04(actor);
        }
    }
}
