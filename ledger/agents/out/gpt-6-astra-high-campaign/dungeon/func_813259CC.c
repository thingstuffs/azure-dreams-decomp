#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct {
    u8 pad[0xA];
    s16 unk0A;
} State_D_80083460;

extern s32 D_8016B778;
extern State_D_80083460 D_80083460;

/* Set the object state pointer, decrement the shared count, and clear the target flag. */
void func_8016D1CC(void *object, void *unused_1, void *unused_2, void *target) {
    State_D_80083460 *state;

    FIELD(object, s32 **, 0x8C) = &D_8016B778;
    state = &D_80083460;
    state->unk0A--;
    FIELD(target, u16 *, 0x46) = (u16)(FIELD(target, u16 *, 0x46) & 0x7FFF);
}
