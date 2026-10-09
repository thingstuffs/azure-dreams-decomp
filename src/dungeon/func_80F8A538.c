#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef void (*ActorCallback)(void *, void *, void *, void *);

/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
typedef struct BankActorState {
    u8 pad_00[0x8C];
    ActorCallback callback;
} BankActorState;

extern s32 func_800AC82C(BankActorState *, s32, SpriteFrameState *, EntityRec *);
extern s32 func_800AD9B4(SpriteFrameState *, EntityRec *);
extern void func_80047784(SpriteFrameState *, s16, s16);

extern void func_80171138(void *, void *, void *, void *);
extern u8 D_80174AD4[9];
extern u8 D_80174AFC[9];

/* Update actor and sprite state after checking the target entity. */
void func_80173D38(BankActorState *actor, s32 action, SpriteFrameState *sprite, EntityRec *target)
{
    if (func_800AC82C(actor, action, sprite, target) != 0) {
        if ((func_800AD9B4(sprite, target) << 16) > 0) {
            actor->callback = func_80171138;
            return;
        }
    } else if (sprite->frameTable == D_80174AFC &&
               !(target->flags1C & 0x208)) {
        sprite->frameTable = D_80174AD4;
        func_80047784(sprite,
                      D_80174AD4[((gameWork.view.viewAngle + target->facing + 0x100) >> 9) & 7],
                      0);
    }
}
