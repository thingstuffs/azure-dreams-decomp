#include "common.h"

s32 func_8002191C();
s32 func_800219B8();

asm(".globl func_8002191C\nfunc_8002191C = 0x8002191C");
asm(".globl func_800219B8\nfunc_800219B8 = 0x800219B8");
asm(".globl D_800287CC\nD_800287CC = 0x800287CC");
asm(".globl D_80084120\nD_80084120 = 0x80084120");
asm(".globl D_80084128\nD_80084128 = 0x80084128");

extern s32 D_800287CC;
extern s32 D_80084120[];
extern s32 D_80084128[];

void func_800220DC(void) {
    s32 index;
    s32 value;

    index = D_800287CC != 0;
    value = func_8002191C();
    D_80084128[index] = value;
    D_80084120[index] = func_800219B8(value);
}
