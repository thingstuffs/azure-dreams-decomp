#include "common.h"
#include "shared/game_work.h"

typedef struct Inner {
    u8 unk0[3];
    u8 type;
    s32 val4;
    s16 val8;
    s16 valA;
} Inner;

typedef struct State {
    u8 pad[0x8D0];
    Inner *next;
} State;

extern u8 D_801C9E40[16];
extern s32 func_8006658C(s32 submission_target, void *entry);

// Appends a type-2 entry with adjusted coordinates and submits it for processing.
void func_8009DA70(s32 x, s32 y, s32 *entryValue, s32 submissionTarget)
{
    s32 maskedY = y & 0xFFFF;
    s32 adjustedY = maskedY + 0xC0;
    State *state = gameWork.unk_000;
    Inner *entry = state->next;
    s32 adjustedX = x + 0x300;

    state->next = entry + 1;
    entry->type = 2;
    entry->val8 = (s16)adjustedX;
    if (state != (State *)D_801C9E40) {
        adjustedY = maskedY - 0x20;
    }
    entry->valA = (s16)adjustedY;
    entry->val4 = *entryValue;
    func_8006658C(submissionTarget, entry);
}
