#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

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

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
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
        u8 *dungeon_state;
        u8 *initial_effect;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        dungeon_state = (u8 *)&D_80083460;
        initial_effect = D_80174538;
        ((S_8017357C_2 *)dungeon_state)->unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = initial_effect;
        direction = (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(sprite, initial_effect[direction & 7], 0);
        ((S_8017357C_0 *)controller)->unk_9B++;
        return;
    }

state_one:
    if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
        if (D_80083462 & 0x1000) {
            return;
        }

        if ((((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) &&
            func_800AA6B4(controller, context, sprite, 0)) {
            return;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            return;
        }

        {
            register void *call_controller ASM_REG("$4") = controller;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

            if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x100) {
                func_800AA258(call_controller, context, sprite, actor);
                return;
            }

            if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x80000) {
                func_800AA888(call_controller, context, sprite, actor);
                func_801737DC(controller, context, sprite, actor);
                return;
            }
        }

        if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
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
        if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
            return;
        }
    }

    effect = D_80174520;
    (*(void * *)((u8 *)sprite + 0x2C)) = effect;
    direction = (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, effect[direction & 7], 0);
    ((S_8017357C_0 *)controller)->unk_8C = D_80170E5C;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= ~0x200;
}
