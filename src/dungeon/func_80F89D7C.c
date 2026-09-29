#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    u16 unk_A0;
} S_8017357C_0;   /* arg0 in func_8017357C */


typedef struct S_8017357C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017357C_3;   /* counter_base in func_8017357C */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173D38(void *, void *, void *, void *);

extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174AFC[];
extern u8 D_80174B04[];

/* Updates actor state, animation, and transition counters. */
void func_8017357C(void *controller, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 actor_flags;
    s32 state;

    state = ((S_8017357C_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AFC;
        func_80047784(sprite,
            D_80174AFC[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_8017357C_3 *)(u8 *)&dungeonStatus.unk_00)->unk_0A = ((S_8017357C_3 *)(u8 *)&dungeonStatus.unk_00)->unk_0A
            - 1;
        ((S_8017357C_0 *)controller)->unk_9B++;
        return;
    case 1:
        if ((func_80042900(actor, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174B04;
            func_80047784(sprite,
                D_80174B04[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                ((S_8017357C_0 *)controller)->unk_8C = D_80171138;
            } else {
                ((S_8017357C_0 *)controller)->unk_96.s = 3;

                ((S_8017357C_3 *)(u8 *)&dungeonStatus.unk_00)->unk_0A =
                    ((S_8017357C_3 *)(u8 *)&dungeonStatus.unk_00)->unk_0A + 1;
                ((S_8017357C_0 *)controller)->unk_9B++;
            }
            return;
        }
        if (dungeonStatus.flags & 0x1000) {
            return;
        }
        if (actor->unk_64 != 0) {
            if (func_800AA6B4(controller, motion, sprite, 0) != 0) {
                return;
            }
        }
        if (actor->tileY == 0) {
            if (dungeonStatus.flags & 0x2008) {
                return;
            }
            func_800AA79C(controller, motion, sprite, actor);
            return;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            return;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            func_800AA258(controller, motion, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            func_800AA888(controller, motion, sprite, actor);
            ((S_8017357C_0 *)controller)->unk_A0 = 0;
            func_80173D38(controller, motion, sprite, actor);
            return;
        }
        if (actor->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            EntityRec *owner = D_800814A8;

            if ((func_8009A180(actor,
                    (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }
        func_800A9A0C(actor);
        func_800A9A04(actor);
        if ((func_80042900(actor, 1) << 16) != 0) {
            TileObject *origin = &D_80082E80;
            s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

            if (((tile == origin->unk_026) && (tile >= 0)) ||
                ((s16)func_8009FD40(origin, sprite) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(actor, 1);
                }
            }
        }
        if ((func_80042900(actor, 1) << 16) != 0) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174B04;
        func_80047784(sprite,
            D_80174B04[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor_flags = actor->flags1C | 0x40000;
        actor->flags1C = actor_flags;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            actor->flags1C = actor_flags & ~0x200;
            ((S_8017357C_0 *)controller)->unk_8C = D_80171138;
        } else {
            ((S_8017357C_0 *)controller)->unk_96.s = 3;

            ((S_8017357C_3 *)(u8 *)&dungeonStatus.unk_00)->unk_0A =
                ((S_8017357C_3 *)(u8 *)&dungeonStatus.unk_00)->unk_0A + 1;
            ((S_8017357C_0 *)controller)->unk_9B++;
        }
        return;
    case 2:
        ((S_8017357C_0 *)controller)->unk_96.s--;
        if (((S_8017357C_0 *)controller)->unk_96.u <= 0) {
            motion->flags14 = 0xFFF00000;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        ((S_8017357C_0 *)controller)->unk_A0 = 0;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
        func_80047784(sprite,
            D_80174AD4[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            dungeonStatus.unk_0A--;
        }
        actor->flags1C &= ~0x200;
        ((S_8017357C_0 *)controller)->unk_8C = D_80171138;
    }
}
