#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;

typedef struct {
    char pad[0x1C];
    Inner *inner;
} Outer;

extern Outer *D_80016000;

void func_80016EF4(void) {
    D_80016000->inner->unk4 = 1248;
    D_80016000->inner->unk8 = 1184;
}
