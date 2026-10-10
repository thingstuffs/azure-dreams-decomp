#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
struct BankFA_faa600_BankActorState {
    u8 pad_00[0x8C];
    BankActorCallback callback;
};

extern s32 func_800AD9B4();
extern s32 func_800AC010();
/* Select the bank actor callback when the resident checks succeed. */
void func_80173E00(BankFA_faa600_BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AC010(state, action, source, target) != 0) && ((func_800AD9B4(source, target) << 0x10) > 0)) {
        state->callback = func_80171138;
    }
}

