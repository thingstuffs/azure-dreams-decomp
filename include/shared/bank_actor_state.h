#ifndef SHARED_BANK_ACTOR_STATE_H
#define SHARED_BANK_ACTOR_STATE_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
typedef void (*BankActorCallback)(void *, s32, SpriteFrameState *, EntityRec *);
typedef struct BankActorState { u8 pad_00[0x8C]; BankActorCallback callback; u8 pad_90[2]; s16 unk_92; } BankActorState;
#endif
