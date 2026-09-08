#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173564_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173564_0;   /* arg0 in func_80173564 */


typedef struct S_80173564_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173564_2;   /* global in func_80173564 */


typedef struct S_80173564_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173564_4;   /* owner in func_80173564 */


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737C4(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_80170E9C[];
extern u8 D_80174EE0[];
extern u8 D_80174F00[];


/* Updates the actor state and selects its directional effect. */
void func_80173564(void *controller, void *context, void *sprite, void *actor)
{
    u8 state;
    u8 *effect_table;
    s32 direction;

    state = ((S_80173564_0 *)controller)->unk_9B;
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
        u8 *initial_effects;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        dungeon_state = (u8 *)&D_80083460;
        initial_effects = D_80174F00;
        ((S_80173564_2 *)dungeon_state)->unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = initial_effects;
        direction = (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(sprite, initial_effects[direction & 7], 0);
        ((S_80173564_0 *)controller)->unk_9B++;
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

        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x100) {
            func_800AA258(controller, context, sprite, actor);
            return;
        }

        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(controller, context, sprite, actor);
            func_801737C4(controller, context, sprite, actor);
            return;
        }

        if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
            return;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            void *owner;

            owner = D_800814A8;
            if ((s16)func_8009A180(actor, (u8 *)((S_80173564_4 *)owner)->unk_58 + 0x20) != 0) {
                return;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);
        if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
            return;
        }
    }

    effect_table = D_80174EE0;
    (*(void * *)((u8 *)sprite + 0x2C)) = effect_table;
    direction = (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, effect_table[direction & 7], 0);
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= ~0x200;
    ((S_80173564_0 *)controller)->unk_8C = D_80170E9C;
}
