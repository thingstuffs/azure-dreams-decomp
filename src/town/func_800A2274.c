#include "common.h"

extern void func_8009F71C(void *arg0, s32 arg1);
extern s32 func_800B28A0(void);
extern u8 D_80010980[];
extern s32 D_800D0728[];

void func_8009F9D4(void) {
    s32 index;

    index = func_800B28A0();
    func_8009F71C((void *)0x80010980, D_800D0728[index]);
}
