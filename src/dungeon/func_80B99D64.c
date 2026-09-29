#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80173564_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173564_0;   /* arg0 in func_80173564 */




extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737C4(void *, void *, void *, void *);

extern u8 D_80170E9C[];
extern u8 D_80174EE0[];
extern u8 D_80174F00[];


/* Updates the actor state and selects its directional effect. */
void func_80173564(void *controller, void *context, void *sprite, EntityRec *actor)
{
    u8 state;
    u8 *effect_table;
    s32 direction;

    state = ((S_80173564_0 *)controller)->unk_9B;
    switch (state) {
    case 0: {
        u8 *initial_effects;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        initial_effects = D_80174F00;
        dungeonStatus.unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = initial_effects;
        direction = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        func_80047784(sprite, initial_effects[direction & 7], 0);
        ((S_80173564_0 *)controller)->unk_9B++;
        return;
    }
    case 1:
        if (actor->tileY == 0) {
            if (dungeonStatus.flags & 0x1000) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                func_800AA6B4(controller, context, sprite, 0)) {
                return;
            }

            if ((s16)func_800A2C34(actor) != 0) {
                return;
            }

            if (((u32)actor->flags1C) & 0x100) {
                func_800AA258(controller, context, sprite, actor);
                return;
            }

            if (((u32)actor->flags1C) & 0x80000) {
                func_800AA888(controller, context, sprite, actor);
                func_801737C4(controller, context, sprite, actor);
                return;
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)func_800A2C34(actor) != 0) {
                EntityRec *owner;

                owner = D_800814A8;
                if ((s16)func_8009A180(actor, (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            func_800A9A0C(actor);
            func_800A9A04(actor);
            if (actor->tileY == 0) {
                return;
            }
        }

        effect_table = D_80174EE0;
        (*(void * *)((u8 *)sprite + 0x2C)) = effect_table;
        direction = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        func_80047784(sprite, effect_table[direction & 7], 0);
        actor->flags1C &= ~0x200;
        ((S_80173564_0 *)controller)->unk_8C = D_80170E9C;
        break;
    default:
        return;
    }
}
