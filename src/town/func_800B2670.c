#include "common.h"

extern void func_80048E00(void *arg0, void *arg1);
extern s32 D_800D15B8;

void func_800AFDD0(void *arg0) {
    func_80048E00(arg0, &D_800D15B8);
    *(u8 *) ((u8 *) arg0 + 0x3C) = *(u8 *) ((u8 *) arg0 + 0x3C) | 0x80;
}
