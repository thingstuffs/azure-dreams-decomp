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

void func_80034EC4(FuncState *arg0) {
    GlobalADBC *data = &D_8006ADBC;

    arg0->unk2 = 2;
    arg0->unk10 = (u8 *)arg0 + 8;
    arg0->unkC = (u8 *)arg0 + 8;
    arg0->unk44 = data->unk20;
    arg0->unk40 = data->unk1c;
}
