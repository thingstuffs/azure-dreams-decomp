#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



/* Actor state of the bank's actor callbacks: the callback slot at +0x8C. */
struct BankFA_fa8b9c_BankActorState {
    u8 pad_00[0x8C];
    BankActorCallback callback;
    u8 pad_90[2];
    s16 unk_92;
};

extern s32 func_800AB1C0();
extern s32 func_800AD9B4();

/* Select the bank actor callback when the resident checks succeed. */
void func_8017239C(BankFA_fa8b9c_BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target) {
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

