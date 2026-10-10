#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
struct BankFA_fa9d44_BankActorState {
    u8 pad_00[0x8C];
    BankActorCallback callback;
};

extern s32 func_800ABDBC();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_80173544(BankFA_fa9d44_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ABDBC(state, action, source, target) != 0) {
        state->callback = func_80171138;
    }
}

