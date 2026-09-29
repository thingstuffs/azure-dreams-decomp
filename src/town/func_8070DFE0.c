#include "common.h"

extern void *D_8001B16C[];
extern char D_8001B14C[];
extern char D_8001B8CC[];
extern char D_8001B9E0[];
extern char D_800206CC[];
extern char D_8001C6D0[];

extern void *func_80016CE4(s32, s32);
extern void *func_80016D18(void);
extern void *func_80016E48(s32);
extern s32 func_8001A64C(s32);
extern void func_8001A554(s32);

/* Select event response data and set flags when using fallback responses. */
void *func_80016FE0(s32 handler_arg_a, s32 handler_arg_b, s32 selector)
{
    void *response;

    switch (selector) {
    case 19:
        do {
            response = func_80016CE4(handler_arg_a, handler_arg_b);
        } while (0);
        D_8001B16C[0] = response;
        if (response != 0) {
            return response;
        }
        if (func_8001A64C(0x92C) == 0) {
            func_8001A554(0x92C);
            return D_8001B8CC;
        }
        return D_8001B9E0;
    case 18:
        response = func_80016D18();
        D_8001B16C[0] = response;
        if (response != 0) {
            return response;
        }
        if (func_8001A64C(0xAC) == 0) {
            func_8001A554(0xAC);
        }
        func_8001A554(0x943);
        return D_800206CC;
    case 52:
    case 53:
    case 54:
        return func_80016E48(selector);
    case 12:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
