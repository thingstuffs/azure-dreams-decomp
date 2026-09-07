#include "common.h"

extern s32 func_80051B50(void *arg0, void *arg1, s32 arg2);
extern s32 D_80084110;
extern s32 D_804005F0;

typedef struct {
    u8 pad8[8];
    s16 unk8;
    s16 unkA;
} SubStruct2;

typedef struct {
    void *unk0;
    SubStruct2 *unk4;
} SubStruct;

void func_8001D0C8(u8 *arg0) {
    SubStruct *temp;

    temp = *(SubStruct **)(arg0 + 0x1F0);
    temp->unk4->unk8 = 0x100;
    temp->unk4->unkA = 0x10;
    temp->unk0 = (void *) &D_80084110;

    temp = *(SubStruct **)(arg0 + 0x1E4);
    temp->unk0 = (void *) func_80051B50(arg0 + 0x5C, &D_804005F0, 1);
    temp->unk4->unk8 = 0x181;
    temp->unk4->unkA = 0x91;

    temp = *(SubStruct **)(arg0 + 0x1F8);
    temp->unk0 = (void *) (arg0 + 0x128);
    temp->unk4->unk8 = 0x112;
    temp->unk4->unkA = 0x18;
}
