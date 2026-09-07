#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} StructB;

typedef struct {
    char pad[0x1C];
    StructB *unk1C;
} StructA;

extern StructA *D_80016000;

void func_80016EA4(void) {
    D_80016000->unk1C->unk4 = 800;
    D_80016000->unk1C->unk8 = 736;
}
