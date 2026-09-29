#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801724E8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801724E8_0;   /* arg0 in func_801724E8 */





extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80170E5C[];
extern u8 D_80174520[];

/* Updates an actor's hop toward its tile and handles movement completion. */
void func_801724E8(void *anim, EntityRec *motion, void *actor, EntityRec *actor_state)
{
    s32 facing_aux;
    s32 hop_frames;
    s16 next_hop_frames;
    u16 move_frames;
    s32 phase;
    s32 actor_flags;
    s32 tile_origin_y;

    phase = ((S_801724E8_0 *)anim)->unk_9B;
    switch (phase) {
    case 0:
        if (!((((Rec_D_80082E80 *)actor)->unk_04.as_s8 == 2 &&
               (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x1000)) ||
              (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0xE000))) {
            break;
        }
        ((S_801724E8_0 *)anim)->unk_98 |= 8;
        (*(u32 *)&actor_state->flags1C) &= 0xF7FFFFFF;
        ((S_801724E8_0 *)anim)->unk_9E.s = 5;
        ((S_801724E8_0 *)anim)->unk_A0 = 0;
        ((S_801724E8_0 *)anim)->unk_9B++;
        /* fall through */
    case 1:
        hop_frames = ((S_801724E8_0 *)anim)->unk_9E.s;
        ((S_801724E8_0 *)anim)->unk_90 -= ((S_801724E8_0 *)anim)->unk_A0;
        if (hop_frames != 0) {
            motion->unk_0C =
                (((((Rec_D_80082E80 *)actor)->unk_24 << 6) - ({ motion->x.w.i - 0x20; })) << 16) / hop_frames;
            motion->unk_10 =
                (((((Rec_D_80082E80 *)actor)->unk_25 << 6) - (tile_origin_y = motion->y.w.i - 0x20)) << 16) /
                ((S_801724E8_0 *)anim)->unk_9E.s;
            ((S_801724E8_0 *)anim)->unk_A0 =
                (-func_800644B8(((S_801724E8_0 *)anim)->unk_9E.s * 0x199)) << 9;
        }

        ((S_801724E8_0 *)anim)->unk_90 += ((S_801724E8_0 *)anim)->unk_A0;
        next_hop_frames = ((S_801724E8_0 *)anim)->unk_9E.u - 1;
        ((S_801724E8_0 *)anim)->unk_9E.s = next_hop_frames;
        if (next_hop_frames < 0) {
            ((S_801724E8_0 *)anim)->unk_90 = 0;
            ((S_801724E8_0 *)anim)->unk_98 &= 0xFFF7;
            (*(u32 *)&actor_state->flags1C) |= 0x08000000;
            ((S_801724E8_0 *)anim)->unk_9B++;
        }
        /* fall through */
    case 2:
        if (((u32)actor_state->flags1C) & 0x08000000) {
            ((S_801724E8_0 *)anim)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
            (*(void * *)((u8 *)actor + 0x2C)) = D_80174520;
            func_80047784(
                actor,
                D_80174520[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            ((S_801724E8_0 *)anim)->unk_9B++;
        }
        break;
    default:
        break;
    }

    move_frames = ((S_801724E8_0 *)anim)->unk_96 - 1;
    ((S_801724E8_0 *)anim)->unk_96 = move_frames;
    if ((s16)move_frames <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
        func_800AD594(actor_state, 4);
        func_800A4ACC(actor_state);

        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08--;
        }

        actor_flags = actor_state->flags1C;
        if (actor_flags & 0x2000) {
            if (actor_state->unk_46 & 0x8000) {
                actor_state->unk_46 &= 0x7FFF;
            }
        } else {
            if (!(actor_flags & 0x410)) {
                if (actor_flags & 0x20000) {
                    actor_state->facing = func_800A0818(
                        ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25,
                        D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
                }
            }
        }

        if ((func_800AD9B4(actor, actor_state) << 16) > 0) {
            ((S_801724E8_0 *)anim)->unk_8C = D_80170E5C;
            func_800A9A04(actor_state);
        }
    }
}
