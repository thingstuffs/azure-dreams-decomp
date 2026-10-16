#define dungeonUpdateLinkedActorMotion func_800AA030
#define dungeonCheckActorFloorTrap func_800AC66C
#define dungeonUpdateBankActorState func_8014C514
/* Relink of matched dungeon/func_80F88C30 at file 0xFA8C30; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AC66C();
extern s32 func_800AA030();
/* Select the bank actor callback when the resident checks succeed. */
void func_8014D508(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AA030(state, action, source, target) != 0) && ((func_800AC66C(source, target) << 0x10) > 0)) {
        state->callback = func_8014C514;
    }
}

