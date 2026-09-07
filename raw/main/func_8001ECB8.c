#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s32 func_80402154(s32 arg0, s32 arg1);
extern void func_8040325C(void *arg0);
extern void func_80405C44(s32 arg0);
extern void func_80400908(void);
extern void func_80406368(void);
extern void func_80405A3C(void);
extern void func_80405C4C(void);

void func_80405CB8(void *arg0)
{
    void (*callback)(void);
    void *call_arg;
    s32 result;

    result = func_80402154(FIELD(arg0, s32 *, 0x28), 0x80010000);
    call_arg = (u8 *)arg0 - 0x20;
    if (result == 0) {
        FIELD(arg0, void (**)(void), 0x34) = func_80406368;
        func_8040325C(call_arg);
        callback = func_80405A3C;
    } else {
        func_80405C44(0x80010000);
        callback = func_80405C4C;
    }
    FIELD(arg0, void (**)(void), -0x10) = callback;
    func_80400908();
    FIELD(arg0, s32 *, 0x40) = 0;
}
