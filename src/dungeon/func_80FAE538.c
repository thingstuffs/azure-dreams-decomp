/* Relink of matched dungeon/func_80F8A538; every changed retail word is a paired relocation. */
#define D_80174AD4 D_80150AD4
#define D_80174AFC D_80150AFC
#define dungeonUpdateBankActorState dungeonUpdateActorActionAndFacing
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AC82C(BankActorState *, s32, SpriteFrameState *, EntityRec *);
extern s32 dungeonCheckActorFloorTrap(SpriteFrameState *, EntityRec *);
extern u8 D_80150AD4[9];
extern u8 D_80150AFC[9];

/* Update actor and sprite state after checking the target entity. */
void func_8014FD38(BankActorState *actor, s32 action, SpriteFrameState *sprite, EntityRec *target)
{
    if (func_800AC82C(actor, action, sprite, target) != 0) {
        if ((dungeonCheckActorFloorTrap(sprite, target) << 16) > 0) {
            actor->callback = dungeonUpdateActorActionAndFacing;
            return;
        }
    } else if (sprite->frameTable == D_80150AFC &&
               !(target->flags1C & 0x208)) {
        sprite->frameTable = D_80150AD4;
        func_80047784(sprite,
                      D_80150AD4[((gameWork.view.viewAngle + target->facing + 0x100) >> 9) & 7],
                      0);
    }
}

