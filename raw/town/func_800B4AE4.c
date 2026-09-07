#include "common.h"

extern void func_800B2190(void *arg0, s32 arg1);
extern s32 func_800B2214(void *arg0, s32 arg1, s32 arg2);
extern u8 D_8001029C_A[];
extern u8 D_8001029C_B[];

__asm__(".set D_8001029C_A, 0x8001029C");
__asm__(".set D_8001029C_B, 0x8001029C");

void func_800B2244(s32 arg0) {
    func_800B2190(D_8001029C_A, func_800B2214(D_8001029C_B, arg0, 0x14));
}
