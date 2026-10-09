#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef void (*ActorCallback)(void *, void *, void *, void *);

/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
typedef struct BankActorState {
    u8 pad_00[0x8C];
    ActorCallback callback;
    u8 pad_90[2];
    s16 unk_92;
} BankActorState;

extern s32 func_800A4ACC();
extern s32 func_800AB1C0();
extern s32 func_800AD594();
extern s32 func_800AD9B4();

extern void func_80171138(void *, void *, void *, void *);

/* Select the bank actor callback when the resident checks succeed. */
void func_8017239C(BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 16) > 0) {
            state->callback = func_80171138;
            if (dungeonStatus.flags & 0x80) {
                state->unk_92 = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        state->unk_92 = -0x20;
    }
}
