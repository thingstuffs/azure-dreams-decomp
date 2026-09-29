#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

typedef struct S_801734E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0xA];
    u16 unk_B2;
} S_801734E0_0;   /* arg0 in func_801734E0 */


typedef struct S_801734E0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801734E0_2;   /* base in func_801734E0 */


typedef struct S_801734E0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801734E0_4;   /* global in func_801734E0 */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173834(void *, void *, void *, void *);

extern s32 D_80171058;
extern u8 D_801748E0[];
extern u8 D_801748E8[];

/* Advance the entity state, updating directional sprites and handling actor events. */
void func_801734E0(void *entity, void *context, void *sprite, void *actor)
{
    s32 state;

    state = ((S_801734E0_0 *)entity)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    {
        u8 *direction_table;

        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        dungeonStatus.unk_0A--;
        direction_table = D_801748E0;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_table;
        func_80047784(sprite,
            direction_table[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u32 actor_flags;

        if (((EntityRec *)actor)->tileY != 0) {

            (*(void * *)((u8 *)sprite + 0x2C)) = D_801748E8;
            func_80047784(sprite,
                D_801748E8[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((EntityRec *)actor)->flags1C |= 0x40000;
            dungeonStatus.unk_0A++;
            ((S_801734E0_0 *)entity)->unk_9B++;
            return;
        }

        if (dungeonStatus.flags & 0x1000) {
            return;
        }

        if (((EntityRec *)actor)->unk_64 != 0) {
            if (func_800AA6B4(entity, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((func_800A2C34(actor) << 16) != 0) {
            return;
        }

        actor_flags = ((u32)((EntityRec *)actor)->flags1C);
        if (actor_flags & 0x100) {
            func_800AA258(entity, context, sprite, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            u16 previous_total;
            u16 pending_decrease;

            func_800AA888(entity, context, sprite, actor);
            previous_total = ((S_801734E0_0 *)entity)->unk_92;
            pending_decrease = ((S_801734E0_0 *)entity)->unk_A6;
            ((S_801734E0_0 *)entity)->unk_A6 = 0;
            ((S_801734E0_0 *)entity)->unk_B2 = 0;
            ((S_801734E0_0 *)entity)->unk_92 = previous_total - pending_decrease;
            func_80173834(entity, context, sprite, actor);
            return;
        }

        if (((EntityRec *)actor)->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            if ((func_8009A180(actor,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);
        if (((EntityRec *)actor)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_801748E8;
        func_80047784(sprite,
            D_801748E8[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((EntityRec *)actor)->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
    }

increment_state:
    ((S_801734E0_0 *)entity)->unk_9B++;
    return;

state_two:
    if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {

        dungeonStatus.unk_0A--;
        ((EntityRec *)actor)->flags1C &= ~0x208;
        ((S_801734E0_0 *)entity)->unk_8C = &D_80171058;
    }

    return;
}
