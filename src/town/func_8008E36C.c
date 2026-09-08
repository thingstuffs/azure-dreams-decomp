#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
} Func8008E36CInner;

typedef struct {
    Func8008E36CInner* inner;
    u8 pad4[0x60];
    s16 unk64;
    s16 index;
    void* unk68;
    void* unk6C;
} Func8008E36CArg;

extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern void* D_800CFC7C[];

/* Decrease the inner value, clamping it to zero and loading indexed state if negative. */
void func_8008BACC(Func8008E36CArg* state) {
    state->inner->unkA -= 0x200;
    if (state->inner->unkA < 0) {
        state->inner->unkA = 0;
        state->unk68 = D_8008BC58;
        state->unk64 = (s8)D_800CFC70[state->index];
        state->unk6C = D_800CFC7C[state->index];
    }
}
