#include "common.h"

typedef struct StructB {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} StructB;

typedef struct StructA {
    u8 pad[0x1C];
    StructB *unk1C;
} StructA;

extern StructA *D_80016000;

void func_80016F68(void) {
    D_80016000->unk1C->unk4 = 1248;
    D_80016000->unk1C->unk8 = 992;
}
