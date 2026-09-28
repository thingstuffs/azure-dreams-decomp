#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_8017357C_0;   /* arg0 in func_8017357C */


typedef struct S_8017357C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017357C_2;   /* global in func_8017357C */


typedef struct S_8017357C_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017357C_4;   /* owner in func_8017357C */


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737DC(void *, void *, void *, void *);

extern u8 D_80170E5C[];
extern u8 D_80174520[];
extern u8 D_80174538[];


/* Advance the actor state and select its directional effect. */
void func_8017357C(void *controller, void *context, void *sprite, void *actor)
{
    u8 state;
    u8 *effect;
    s32 direction;

    state = ((S_8017357C_0 *)controller)->unk_9B;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    {
        u8 *initial_effect;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        initial_effect = D_80174538;
        dungeonStatus.unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = initial_effect;
        direction = (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9;
        func_80047784(sprite, initial_effect[direction & 7], 0);
        ((S_8017357C_0 *)controller)->unk_9B++;
        return;
    }

state_one:
    if (((EntityRec *)actor)->tileY == 0) {
        if (dungeonStatus.flags & 0x1000) {
            return;
        }

        if ((((EntityRec *)actor)->unk_64 != 0) &&
            func_800AA6B4(controller, context, sprite, 0)) {
            return;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            return;
        }

        {
            void *call_controller = controller;

            if (((u32)((EntityRec *)actor)->flags1C) & 0x100) {
                do {
                    func_800AA258(call_controller, context, sprite, actor);
                } while (0);
                return;
            }

            if (((u32)((EntityRec *)actor)->flags1C) & 0x80000) {
                func_800AA888(call_controller, context, sprite, actor);
                func_801737DC(controller, context, sprite, actor);
                return;
            }
        }

        if (((EntityRec *)actor)->unk_6D == 0) {
            return;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            void *owner;

            owner = D_800814A8;
            if ((s16)func_8009A180(actor, (u8 *)((S_8017357C_4 *)owner)->unk_58 + 0x20) != 0) {
                return;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);
        if (((EntityRec *)actor)->tileY == 0) {
            return;
        }
    }

    effect = D_80174520;
    (*(void * *)((u8 *)sprite + 0x2C)) = effect;
    direction = (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9;
    func_80047784(sprite, effect[direction & 7], 0);
    ((S_8017357C_0 *)controller)->unk_8C = D_80170E5C;
    ((EntityRec *)actor)->flags1C &= ~0x200;
}
