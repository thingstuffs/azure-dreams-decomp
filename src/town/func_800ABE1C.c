#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033CD8();
extern s16 func_800374F4();
extern M2C_UNK func_800A8BBC();
extern M2C_UNK D_800A9528[3];
extern M2C_UNK D_800A9624[3];
extern M2C_UNK D_800A970C[3];

/* Initialize object tables, settings, and randomized state. */
void func_800A957C(void *object, void *random_state, void *settings) {
    *(M2C_UNK **)((s8 *)object - 0x10) = D_800A9624;
    *(M2C_UNK **)((s8 *)object + 0x50) = D_800A970C;
    *(s16 *)((s8 *)settings + 0x1C) = 0x37;
    *(s16 *)((s8 *)settings + 0x1E) = 0x37;
    *(u16 *)((s8 *)settings + 0x20) = 0xFF00;
    *(s16 *)((s8 *)random_state + 0x0E) = func_800374F4(0xFFFF);
    *(s16 *)((s8 *)random_state + 0x12) = func_800374F4(0xFFFF);
    *(s16 *)((s8 *)random_state + 0x16) = func_800374F4(0xFFFF);
    func_80033CD8(object, D_800A9528);
    func_800A8BBC(0x10, 0x11, 0x12, 0x13, random_state);
}
