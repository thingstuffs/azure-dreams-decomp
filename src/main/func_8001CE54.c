#include "common.h"

extern s32 func_80051B50(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80402268(void);
extern s32 D_8008432C;
extern s32 D_80408CB0[];

typedef struct {
    u8 pad8[8];
    s16 unk8;
    s16 unkA;
} SubStruct2;

typedef struct {
    void *unk0;
    SubStruct2 *unk4;
} SubStruct;

void func_8001CE54(u8 *arg0) {
    SubStruct *temp;
    s32 idx;

    temp = *(SubStruct **)(arg0 + 0x1DC);
    idx = func_80402268() >= 3;
    temp->unk0 = (void *) func_80051B50(arg0 + 8, D_80408CB0[idx], 1);
    temp->unk4->unk8 = 0xF0;
    temp->unk4->unkA = 0x91;

    temp = *(SubStruct **)(arg0 + 0x1EC);
    temp->unk4->unk8 = 0x70;
    temp->unk4->unkA = 0x10;
    temp->unk0 = (void *) &D_8008432C;

    temp = *(SubStruct **)(arg0 + 0x1F4);
    temp->unk0 = (void *) (arg0 + 0xB0);
    temp->unk4->unk8 = 0xAE;
    temp->unk4->unkA = 0x18;
}
