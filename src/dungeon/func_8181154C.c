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

/* Clears the object's buffer and resets its associated state. */
void func_8002654C(s32 objectAddress)
{
    S_8002654C_0 *objectState;

    objectState = (void *)(objectAddress + 0x20);
    memset(objectState->unk_14, 0,
           (D_800294F8[objectState->unk_10] * 2) | 1);
    func_800263C0(objectState->unk_70, objectState->unk_14);
    objectState->unk_08 = 0;
    func_80026370(objectState->unk_70, 0);
}
