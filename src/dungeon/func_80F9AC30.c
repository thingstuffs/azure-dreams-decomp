/* Relink of matched dungeon/func_80F88C30; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState func_8015F138
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonCheckActorFloorTrap();
extern s32 dungeonUpdateLinkedActorMotion();
/* Select the bank actor callback when the resident checks succeed. */
void func_80160430(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((dungeonUpdateLinkedActorMotion(state, action, source, target) != 0) && ((dungeonCheckActorFloorTrap(source, target) << 0x10) > 0)) {
        state->callback = func_8015F138;
    }
}

