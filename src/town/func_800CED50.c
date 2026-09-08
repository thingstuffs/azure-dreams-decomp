#include "common.h"

extern void func_80033AA8(s32);
extern u8 D_800CC524;

typedef struct {
    u8 unk0[0x54];
    void *unk54;
    u8 unk58[0x6C - 0x58];
    u16 unk6C;
} Struct800CED50Arg0;

typedef struct {
    u8 unk0[0xC];
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Struct800CED50Arg2;

// Decrements the countdown and resets the state and color when it expires.
void func_800CC4B0(Struct800CED50Arg0 *state, s32 unusedArg, Struct800CED50Arg2 *color) {
    if ((s16)(--state->unk6C) <= 0) {
        func_80033AA8(0x97);
        state->unk54 = &D_800CC524;
        state->unk6C = 0xA;
        color->unkE = 0x80;
        color->unkD = 0x80;
        color->unkC = 0x80;
    }
}
