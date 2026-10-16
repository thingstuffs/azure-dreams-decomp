#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#define dungeonUpdateBankActorState func_80158514
#define dungeonUpdateLinkedActorMotion func_800AB4E4
#define dungeonCheckActorFloorTrap func_800AC66C
/* Relink of matched dungeon/func_80F88C30 at file 0xFA8C30; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AC66C(Rec_D_80082E80 *, EntityRec *);
extern s32 func_800AB4E4(Rec_func_800A9E70_arg0 *, EntityRec *, Rec_D_80082E80 *, void *);
/* Select the bank actor callback when the resident checks succeed. */
void func_8015A6B8(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AB4E4(state, action, source, target) != 0) && ((func_800AC66C(source, target) << 0x10) > 0)) {
        state->callback = func_80158514;
    }
}

