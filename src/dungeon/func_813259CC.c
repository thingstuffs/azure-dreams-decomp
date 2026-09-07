#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct {
    u8 pad[0xA];
    s16 unk0A;
} State_D_80083460;

extern s32 D_8016B778;
extern State_D_80083460 D_80083460;

void func_8016D1CC(void *arg0, void *arg1, void *arg2, void *arg3) {
    State_D_80083460 *state;

    FIELD(arg0, s32 **, 0x8C) = &D_8016B778;
    state = &D_80083460;
    state->unk0A--;
    FIELD(arg3, u16 *, 0x46) = (u16)(FIELD(arg3, u16 *, 0x46) & 0x7FFF);
}
