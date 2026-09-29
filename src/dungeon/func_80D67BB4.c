#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
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
    switch (phase) {
    case 0:
        timer_value = ((S_801733B4_0 *)motion)->unk_AA.s + 1;
        ((S_801733B4_0 *)motion)->unk_AA.s = timer_value;
        if ((s16)timer_value < 2) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2368;
        func_80047784(sprite,
            D_800E2368[((gameWork.view.viewAngle + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801733B4_0 *)motion)->unk_98 |= 8;
        ((S_801733B4_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801733B4_0 *)motion)->unk_AA.s = 5;
        ((S_801733B4_0 *)motion)->unk_A4 = 0;
        ((S_801733B4_0 *)motion)->unk_9B++;
                        /* fallthrough */
    case 1:
        ((S_801733B4_0 *)motion)->unk_90.at00.v -= ((S_801733B4_0 *)motion)->unk_A4;
        if (((S_801733B4_0 *)motion)->unk_AA.u != 0) {
            ((EntityRec *)position)->unk_0C =
                (((((Rec_D_80082E80 *)sprite)->unk_24 << 6) -
                  ({ ((EntityRec *)position)->x.w.i - 0x20; })) << 16) /
                ((S_801733B4_0 *)motion)->unk_AA.u;
            y_offset = ((EntityRec *)position)->y.w.i - 0x20;
            ((EntityRec *)position)->unk_10 =
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
                        /* fallthrough */
    case 2:
        if (((S_801733B4_1 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801733B4_0 *)motion)->unk_98 &= 0xFFF7;
            ((EntityRec *)position)->flags14 = 0;
            ((EntityRec *)position)->unk_10 = 0;
            ((EntityRec *)position)->unk_0C = 0;
            func_800A2B04(position, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2370;
            func_80047784(sprite,
                D_800E2370[((gameWork.view.viewAngle + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801733B4_0 *)motion)->unk_9B++;
        }
        break;
        break;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_800E2348) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2348;
            func_80047784(sprite,
                D_800E2348[((gameWork.view.viewAngle + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801733B4_0 *)motion)->unk_9E = 0;
        }
        break;
    }

    timer_value = ((S_801733B4_0 *)motion)->unk_96 - 1;
    ((S_801733B4_0 *)motion)->unk_96 = timer_value;
    if (((s32)timer_value << 16) <= 0) {
        s32 actor_flags;

        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        func_800A2B04(position, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08--;
        }
        actor_flags = ((S_801733B4_1 *)actor)->unk_1C.u;
        if (actor_flags & 0x2000) {
            if (((S_801733B4_1 *)actor)->unk_46 & 0x8000) {
                ((S_801733B4_1 *)actor)->unk_46 &= 0x7FFF;
            }
        } else {
            if (!(actor_flags & 0x410)) {
                if (actor_flags & 0x20000) {
                    ((S_801733B4_1 *)actor)->unk_2A = func_800A0818(
                        ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                        D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
                }
            }
        }

        if ((func_800AD9B4(sprite, actor) << 16) > 0) {
            ((S_801733B4_0 *)motion)->unk_8C = &D_80171F1C;
            func_800A9A04(actor);
        }
    }
}
