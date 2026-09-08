#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[2];
    u8 unk2;
    u8 pad3[9];
    void *unkC;
    void *unk10;
    u8 pad14[0x2c];
    u32 unk40;
    u32 unk44;
} FuncState;

typedef struct {
    u8 pad0[0x1c];
    u32 unk1c;
    u32 unk20;
} GlobalADBC;

extern GlobalADBC D_8006ADBC;

/* Initializes state pointers and copies the global default values. */
void func_80034EC4(FuncState *state) {
    GlobalADBC *defaults = &D_8006ADBC;

    state->unk2 = 2;
    state->unk10 = (u8 *)state + 8;
    state->unkC = (u8 *)state + 8;
    state->unk44 = defaults->unk20;
    state->unk40 = defaults->unk1c;
}
