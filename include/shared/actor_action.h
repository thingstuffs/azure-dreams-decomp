#ifndef SHARED_ACTOR_ACTION_H
#define SHARED_ACTOR_ACTION_H
#include "common.h"

/* Action pointer, signed/unsigned timer alternatives and phase; sparse 0x9C view. */
typedef struct ActorActionTimerView {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} ActorActionTimerView;

/* Callback/action pointer and phase; preserve the sparse 0x9C extent. */
typedef struct ActorActionStateView {
    unsigned char pad_00[0x8C];
    void *unk_8C;
    unsigned char pad_90[0xB];
    unsigned char unk_9B;
} ActorActionStateView;

/* Action record used by the directional action handlers; preserve every union path. */
typedef struct ActorActionView {
    unsigned char pad_00[0x8C];
    union { int code; void *record; unsigned char *frames; int *word; } nextAction;
    union { int v; struct { unsigned short frac; short i; } w; } motionOffset;
    unsigned char pad_94[2];
    union { unsigned short unsignedTicks; short signedTicks; } timer;
    unsigned short flags;
    unsigned char behavior;
    unsigned char phase;
    unsigned char pad_9C[4];
    short frameParameter;
    unsigned char pad_A2[4];
    unsigned short effectTicks;
    union { short signedPhase; unsigned short phase; unsigned short startX; } effectState;
    union { unsigned short facing; unsigned short startY; } saved;
    unsigned short effectX;
    unsigned short effectY;
    unsigned short effectZ;
} ActorActionView;

#endif
