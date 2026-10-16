/* Relink of matched dungeon/func_80F8A538; every changed retail word is a paired relocation. */
#define D_80174AD4 D_80156AD4
#define D_80174AFC D_80156AFC
#define dungeonUpdateBankActorState updateActorActionAndTargetState
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AC82C(BankActorState *, s32, SpriteFrameState *, EntityRec *);
extern s32 dungeonCheckActorFloorTrap(SpriteFrameState *, EntityRec *);
extern u8 D_80156AD4[9];
extern u8 D_80156AFC[9];

/* Update actor and sprite state after checking the target entity. */
void func_80155D38(BankActorState *actor, s32 action, SpriteFrameState *sprite, EntityRec *target)
{
    if (func_800AC82C(actor, action, sprite, target) != 0) {
        if ((dungeonCheckActorFloorTrap(sprite, target) << 16) > 0) {
            actor->callback = updateActorActionAndTargetState;
            return;
        }
    } else if (sprite->frameTable == D_80156AFC &&
               !(target->flags1C & 0x208)) {
        sprite->frameTable = D_80156AD4;
        func_80047784(sprite,
                      D_80156AD4[((gameWork.view.viewAngle + target->facing + 0x100) >> 9) & 7],
                      0);
    }
}

