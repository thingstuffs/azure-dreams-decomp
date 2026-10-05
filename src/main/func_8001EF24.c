#include "common.h"

extern s32 func_80402268(void *callPtr);
extern void func_80403234(void *callPtr);
extern void func_80403374(void *callPtr);
extern void func_80405ED4(void *base);
extern void func_80406368(void);
extern void func_80405AB4(void);
extern void func_80405A64(void);

extern u8 D_8009DDD8[];

void func_80405F24(void *inputPtr)
{
    u8 *base;
    s32 index;
    s32 result;

    base = inputPtr;
    index = *(s32 *)(base + 0x28);
    inputPtr = base - 0x20;
    if (*(s32 *)(D_8009DDD8 + (index << 7)) == 0) {
        result = func_80402268(inputPtr);
        inputPtr = 0;
        inputPtr = base - 0x20;
        if (result < 3) {
            *(void (**)(void))(base + 0x34) = func_80406368;
            func_80403234(inputPtr);
        } else {
            func_80405ED4(base);
            return;
        }
    } else {
        *(void (**)(void))(base + 0x34) = func_80405AB4;
        func_80403374(inputPtr);
    }
    *(void (**)(void))(base - 0x10) = func_80405A64;
}
