#include "common.h"

extern void func_8004EAC4();
extern void func_800263C0();
extern s32 func_80026388();
extern void func_80026370();

void func_800265B8(s32 arg0, s32 arg1) {
    s32 result;
    s32 *object;

    object = (s32 *)(arg0 + 0x20);
    func_8004EAC4(object[5], arg1, object[2]);
    func_800263C0(object[28], object[5]);
    result = func_80026388(1, object[2], object[4]);
    object[2] = result;
    func_80026370(object[28], result);
}
