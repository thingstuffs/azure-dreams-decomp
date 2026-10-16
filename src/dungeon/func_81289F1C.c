#define dungeonCheckActorFloorTrap func_800AC66C
#define dungeonUpdateBankActorState func_80164514
#define dungeonUpdateThrownActorTravel func_800AACC8
/* Relink of matched dungeon/func_80F8A600 at file 0xFAA600; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AC66C();
extern s32 func_800AACC8();
/* Select the bank actor callback when the resident checks succeed. */
void func_8016671C(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AACC8(state, action, source, target) != 0) && ((func_800AC66C(source, target) << 0x10) > 0)) {
        state->callback = func_80164514;
    }
}

