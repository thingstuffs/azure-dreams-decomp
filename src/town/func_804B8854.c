#include "common.h"

typedef struct TownState {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} TownState;

typedef struct TownContext {
    u8 pad_00[0x1C];
    TownState *state;
} TownContext;

extern TownContext *D_80016000;

void func_80017054(void) {
    D_80016000->state->unk4 = 0x6A0;
    D_80016000->state->unk8 = 0x4A0;
}
