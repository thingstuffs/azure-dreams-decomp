#include "common.h"

typedef struct S_8002654C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x58];
    s32 unk_70;
} S_8002654C_0;   /* obj in func_8002654C */



extern s32 memset();
extern s32 func_800263C0();
extern s32 func_80026370();
extern volatile u8 D_800294F8[9];

void func_8002654C(s32 arg0)
{
    S_8002654C_0 *obj;

    obj = (void *)(arg0 + 0x20);
    memset(obj->unk_14, 0,
                  (D_800294F8[obj->unk_10] * 2) | 1);
    func_800263C0(obj->unk_70, obj->unk_14);
    obj->unk_08 = 0;
    func_80026370(obj->unk_70, 0);
}
