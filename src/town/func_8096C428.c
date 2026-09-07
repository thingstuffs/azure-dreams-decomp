#include "common.h"

typedef struct {
    s32 unk00[12];
    s32 *unk30;
    s32 *unk34;
    s32 unk38[12];
    s32 *unk68;
    s32 *unk6C;
} State;

extern State D_80129728;

void func_801248C0(void *arg0) {
    State *state = &D_80129728;

    *((u8 *)arg0 + 0xC) = 1;
    *((s16 *)((u8 *)arg0 + 8)) = 0;
    *((u8 *)arg0 + 0xE) = 0;
    *state->unk30 = 0;
    *state->unk34 = 0;
    *state->unk68 = 0;
    *state->unk6C = 0;
}
