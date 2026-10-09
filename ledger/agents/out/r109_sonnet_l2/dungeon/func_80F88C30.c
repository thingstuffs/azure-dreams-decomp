#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef void (*ActorCallback)(void *, void *, void *, void *);

/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
typedef struct BankActorState {
    u8 pad_00[0x8C];
    ActorCallback callback;
} BankActorState;

extern s32 func_800AD9B4();
extern s32 func_800AB378();
extern void func_80171138(void *, void *, void *, void *);

/* Select the bank actor callback when the resident checks succeed. */
void func_80172430(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AB378(state, action, source, target) != 0) && ((func_800AD9B4(source, target) << 0x10) > 0)) {
        state->callback = func_80171138;
    }
}
