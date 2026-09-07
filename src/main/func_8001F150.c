#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void func_804032FC(void *arg0);
extern void func_80406368(void);
extern void func_80405A64(void);
extern void func_80405FC4(void);
extern s32 D_8009DDD8[];

void func_80406150(void *arg0)
{
    void (*callback)(void);
    void *call_arg;
    s32 index;
    s32 active;

    index = FIELD(arg0, s32 *, 0x28);
    active = *(s32 *)((u8 *)D_8009DDD8 + index * 0x80);
    call_arg = (u8 *)arg0 - 0x20;
    if (active != 0) {
        callback = func_80405FC4;
        FIELD(arg0, s32 *, 0x2C) = index;
    } else {
        FIELD(arg0, void (**)(void), 0x34) = func_80406368;
        func_804032FC(call_arg);
        callback = func_80405A64;
    }
    FIELD(arg0, void (**)(void), -0x10) = callback;
}
