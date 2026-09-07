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

/* Updates the state and selects its next callback based on the current entry check. */
void func_80406AA8(void *state)
{
    void (*next_callback)(void);
    void *state_base;
    s32 check_result;

    func_80406844(0x80010000, FIELD(state, s32 *, 0x2C),
                  FIELD(state, s32 *, 0x24));
    check_result = func_80402084(FIELD(state, s32 *, 0x2C), 0x80010000);
    state_base = (u8 *)state - 0x20;
    if (check_result == 0) {
        FIELD(state, void (**)(void), 0x34) = func_80406DA0;
        func_80403144(state_base);
        next_callback = func_804069FC;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    } else {
        func_80405A00(FIELD(state, s32 *, 4), FIELD(state, s32 *, 0x2C));
        func_80404688(FIELD(state, s32 *,
                            0xC + FIELD(state, s32 *, 0x2C) * 4));
        if (D_80010208 != 0) {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            next_callback = func_80406A74;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        } else {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            next_callback = func_80406DA0;
        }
    }
    FIELD(state, void (**)(void), -0x10) = next_callback;
    func_80400908();
    FIELD(state, s32 *, 0x40) = 0;
}
