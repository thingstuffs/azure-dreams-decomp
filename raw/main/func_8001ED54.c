#include "common.h"

extern s32 D_8009DDD8[];
extern void func_804031E4(void *, void *);
extern void func_804032FC(void *);
extern void func_80405D2C(void);
extern void func_80405DC4(void) __attribute__((noreturn));
extern void func_80406368(void);
extern void func_80405A64(void);

void func_8001ED54(void *arg0)
{
    s32 one;
    void *owner;
    s32 index;
    register void (*callback)(void) ASM_REG("$2");

    owner = (u8 *)arg0 - 0x20;
    index = *(s32 *)((u8 *)arg0 + 0x28);
    if (D_8009DDD8[index * 0x20] != 0) {
        one = 1;
        *(s32 *)((u8 *)arg0 + 0x3C) = one;
        func_804031E4(owner, (u8 *)arg0 + 0x40);
        callback = func_80405D2C;
        ASM_KEEP(callback);
        *(s32 *)((u8 *)arg0 + 0x40) = one;
        func_80405DC4();
    }

    *(void (**)(void))((u8 *)arg0 + 0x34) = func_80406368;
    func_804032FC(owner);
    *(void (**)(void))((u8 *)arg0 - 0x10) = func_80405A64;
}
