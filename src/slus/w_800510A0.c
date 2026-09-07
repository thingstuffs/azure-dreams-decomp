#include "common.h"

/* summary: forwards &a0->unkC to func_80050FF4, then stores the result of
   func_80126890(a0->unk4) into a0->unk8 */
extern void func_80050FF4(void *a0);
extern s32 func_80126890(void *a0);

typedef struct S_800510A0 {
    s32 unk0;
    void *unk4;
    s32 unk8;
    s32 unkC;
} S_800510A0;

void func_800510A0(S_800510A0 *a0)
{
    func_80050FF4(&a0->unkC);
    a0->unk8 = func_80126890(a0->unk4);
}
