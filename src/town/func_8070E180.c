#include "common.h"

extern void *D_8001B16C[];
extern u8 D_8001B14C[];
extern u8 D_8001B9E0[];
extern u8 D_8001C6D0[];
extern u8 D_80020934[];

extern void *func_80016CE4(s32, s32);
extern void *func_80016D18(void);
extern void *func_80016E48(s32);
extern void func_8001A554(s32);

/* Select event response data, using a fallback when an event handler returns null. */
void *func_80017180(s32 handler_arg_a, s32 handler_arg_b, s32 selector)
{
    void *result;

    switch (selector - 12) {
    case 7:
        do {
            result = func_80016CE4(handler_arg_a, handler_arg_b);
        } while (0);
        D_8001B16C[0] = result;
        if (result != 0) {
            return result;
        }
        return D_8001B9E0;
    case 6:
        result = func_80016D18();
        D_8001B16C[0] = result;
        if (result != 0) {
            return result;
        }
        func_8001A554(0x943);
        return D_80020934;
    case 40:
    case 41:
    case 42:
        return func_80016E48(selector);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
