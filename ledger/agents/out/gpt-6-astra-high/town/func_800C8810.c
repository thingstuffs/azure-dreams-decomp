#include "common.h"

extern void func_800C46A8(void *arg0);
extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[][8];
extern s32 D_800C5FDC[];
extern s32 D_800D5590[];

/* Clears the object's table flag, updates the object, and installs D_800C5FDC. */
void func_800C5F70(void *object, s32 unusedArgument, s32 updateValue) {
    void *updateObject;
    s32 stagedUpdateValue;

    D_80082660[*((s32 *)object + 0x18)][0] = 0;
    func_800C46A8(object);
    updateObject = object;
    ASM_KEEP(updateObject);   /* MATCH pin: retail schedule: same instructions, different order without it */
    stagedUpdateValue = updateValue;
    ASM_KEEP(stagedUpdateValue);   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_800C2E84(updateObject, stagedUpdateValue, D_800D5590);
    *((s32 **)object + 0x15) = D_800C5FDC;
}
