#ifndef SHARED_BANK_ACTOR_STATE_H
#define SHARED_BANK_ACTOR_STATE_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
/* Bank actor action callback: working body, context word, sprite state and actor view.
 * update_bank_actor_movement dispatches it with these four arguments. */
typedef void (*BankActorCallback)(void *, s32, SpriteFrameState *, EntityRec *);
/* Partial actor action state within a pool-owned body.
 * update_bank_actor_movement dispatches callback at +0x8C. */
typedef struct BankActorState { u8 pad_00[0x8C]; BankActorCallback callback; /* actor action callback; takes body, context, sprite and actor arguments */ u8 pad_90[2]; s16 unk_92; } BankActorState;
#endif
