#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef void (*ActorCallback)(void *, void *, void *, void *);

/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
typedef struct BankActorState {
    u8 pad_00[0x8C];
    ActorCallback callback;
} BankActorState;

extern s32 func_800ACE34();
extern void func_80171138(void *, void *, void *, void *);

/* Restore the bank actor callback after the resident state check succeeds. */
void func_80173ED4(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ACE34(state, action, source, target) != 0) {
        state->callback = func_80171138;
    }
}
