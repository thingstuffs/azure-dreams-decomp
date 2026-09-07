#include "common.h"

extern void func_800C3050(void *arg0, s32 arg1, void *arg2, void *arg3,
                          void *arg4, void *arg5);

extern s32 D_80081458[];
extern u8 D_800D61C4[];
extern u8 D_800D61CC[];
extern u8 D_800D61F4[];
extern u8 D_800D6200[];

void func_800C8330(void *arg0, s32 arg1, void *arg2) {
    *((s8 *)arg0 + 0x93) = 1;
    *(s32 *)((u8 *)arg2 + 0x28) = D_80081458[0];
    func_800C3050(arg0, 2, D_800D61F4, D_800D6200, D_800D61C4,
                  D_800D61CC);
}
