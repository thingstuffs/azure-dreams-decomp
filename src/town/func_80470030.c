#include "common.h"

extern void func_80019618(s32, s32);
extern void func_80019928(s32, s32);
extern s32 func_8001A510(s32);

/* Dispatch to a handler based on condition 0x798, returning 1 when it is clear. */
s32 func_80017030(s32 handler_arg_a, s32 handler_arg_b) {
    if (func_8001A510(0x798) != 0) {
        func_80019928(handler_arg_a, handler_arg_b);
        return;
    }
    func_80019618(handler_arg_a, handler_arg_b);
    return 1;
}
