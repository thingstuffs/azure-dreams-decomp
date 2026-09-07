#include "common.h"

extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern void *D_800CFC7C[];

typedef struct {
    u16 pad0[5];
    u16 unkA;
} SubStruct;

typedef struct {
    SubStruct *sub;
    u8 pad4[96];
    s16 unk64;
    s16 unk66;
    void *unk68;
    void *unk6C;
} MainStruct;

/* Decrement the substate value and reset state data when it becomes negative. */
void func_8008BACC(MainStruct *state) {
    state->sub->unkA -= 0x200;
    if ((s16)state->sub->unkA < 0) {
        state->sub->unkA = 0;
        state->unk68 = D_8008BC58;
        state->unk64 = (s8)D_800CFC70[state->unk66];
        state->unk6C = D_800CFC7C[state->unk66];
    }
}
