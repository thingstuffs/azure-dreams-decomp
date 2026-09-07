#include "common.h"

extern s32 func_80402268(void *arg0);
extern void func_80403234(void *arg0);
extern void func_80403374(void *arg0);
extern void func_80405ED4(void *arg0);
extern void func_80405FA4(void) __attribute__((noreturn));
extern void func_80405FB0(void) __attribute__((noreturn));
extern void func_80406368(void);
extern void func_80405AB4(void);
extern void func_80405A64(void);

extern u8 D_8009DDD8[];

void func_8001EF24(void *arg0)
{
    u8 *base;
    s32 index;
    s32 result;

    base = arg0;
    index = *(s32 *)(base + 0x28);
    arg0 = base - 0x20;
    if (*(s32 *)(D_8009DDD8 + (index << 7)) == 0) {
        result = func_80402268(arg0);
        arg0 = 0;
        arg0 = base - 0x20;
        if (result < 3) {
            *(void (**)(void))(base + 0x34) = func_80406368;
            func_80403234(arg0);
            func_80405FA4();
        }
        func_80405ED4(base);
        func_80405FB0();
    }

    *(void (**)(void))(base + 0x34) = func_80405AB4;
    func_80403374(arg0);
    *(void (**)(void))(base - 0x10) = func_80405A64;
}
