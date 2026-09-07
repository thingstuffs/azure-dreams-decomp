#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void func_80406844(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80402084(s32 arg0, s32 arg1);
extern void func_80403144(void *arg0);
extern void func_80405A00(s32 arg0, s32 arg1);
extern void func_80404688(s32 arg0);
extern void func_80400908(void);
extern void func_804069FC(void);
extern void func_80406A74(void);
extern void func_80406DA0(void);
extern s32 D_80010208;

void func_80406AA8(void *arg0)
{
    void (*callback)(void);
    void *call_arg;
    s32 result;

    func_80406844(0x80010000, FIELD(arg0, s32 *, 0x2C),
                  FIELD(arg0, s32 *, 0x24));
    result = func_80402084(FIELD(arg0, s32 *, 0x2C), 0x80010000);
    call_arg = (u8 *)arg0 - 0x20;
    if (result == 0) {
        FIELD(arg0, void (**)(void), 0x34) = func_80406DA0;
        func_80403144(call_arg);
        callback = func_804069FC;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    } else {
        func_80405A00(FIELD(arg0, s32 *, 4), FIELD(arg0, s32 *, 0x2C));
        func_80404688(FIELD(arg0, s32 *,
                            0xC + FIELD(arg0, s32 *, 0x2C) * 4));
        if (D_80010208 != 0) {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            callback = func_80406A74;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        } else {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            callback = func_80406DA0;
        }
    }
    FIELD(arg0, void (**)(void), -0x10) = callback;
    func_80400908();
    FIELD(arg0, s32 *, 0x40) = 0;
}
