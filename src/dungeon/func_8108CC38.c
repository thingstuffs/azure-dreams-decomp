/* Relink of matched dungeon/func_80DE5D7C; every changed retail word is a paired relocation. */
#define D_80170E5C D_8016AE94
#define D_80174520 D_8016FF10
#define D_80174538 D_8016FF28
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
} S_8017357C_0;   /* arg0 in func_8016E438 */


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_8016E698(void *, s32, void *, void *);

extern u8 D_8016AE94[];
extern u8 D_8016FF10[];
extern u8 D_8016FF28[];


/* Advance the actor state and select its directional effect. */
void func_8016E438(void *controller, void *context, void *sprite, EntityRec *actor)
{
    u8 state;
    u8 *effect;
    s32 direction;

    state = ((S_8017357C_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *initial_effect;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        initial_effect = D_8016FF28;
        dungeonStatus.unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = initial_effect;
        direction = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        func_80047784(sprite, initial_effect[direction & 7], 0);
        ((S_8017357C_0 *)controller)->unk_9B++;
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

            {
                void *call_controller = controller;

                if (((u32)actor->flags1C) & 0x100) {
                    do {
                        func_800AA258(call_controller, context, sprite, actor);
                    } while (0);
                    return;
                }

                if (((u32)actor->flags1C) & 0x80000) {
                    func_800AA888(call_controller, context, sprite, actor);
                    func_8016E698(controller, context, sprite, actor);
                    return;
                }
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

        effect = D_8016FF10;
        (*(void * *)((u8 *)sprite + 0x2C)) = effect;
        direction = (gameWork.view.viewAngle + actor->facing + 0x100) >> 9;
        func_80047784(sprite, effect[direction & 7], 0);
        ((S_8017357C_0 *)controller)->unk_8C = D_8016AE94;
        actor->flags1C &= ~0x200;
    }
}
