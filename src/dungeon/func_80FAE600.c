/* Relink of matched dungeon/func_80F8A600; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState dungeonUpdateActorActionAndFacing
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonCheckActorFloorTrap();
extern s32 dungeonUpdateThrownActorTravel();
/* Select the bank actor callback when the resident checks succeed. */
void func_8014FE00(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((dungeonUpdateThrownActorTravel(state, action, source, target) != 0) && ((dungeonCheckActorFloorTrap(source, target) << 0x10) > 0)) {
        state->callback = dungeonUpdateActorActionAndFacing;
    }
}

