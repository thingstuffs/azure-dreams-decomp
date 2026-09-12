#include "common.h"

extern void func_80016B88(void);
extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04(u8 *, s32, s32);
extern s32 *func_80019ABC(u8 *, s32 *, s32, s32);
extern s32 func_8001A510(s32);

extern s32 D_8001A974;
extern s32 D_8001B1FC;
extern s32 D_8001B63C;
extern s32 D_8001B6D0;
extern s32 D_8001B824;
extern s32 D_8001C5FB;
extern s32 D_8001C64E;

/* Select a response from the selector, context checks, and event flags. */
s32 *func_80016C00(s32 context, s32 check_value, s32 selector) {
    s32 *response;

    if (selector == 9) {
        if (func_80017E98(context, check_value) != 0) {
            if (func_8001A510(0x798) != 0) {
                return &D_8001B6D0;
            }
            if (func_8001A510(0x47D) == 0) {
                return &D_8001B63C;
            }
        }
        response = func_80019ABC((u8 *)&D_8001A974, &D_8001B1FC, context, selector);
        if (func_80019A04((u8 *)&D_8001A974, context, selector) != 0) {
            response = &D_8001C64E;
        }
    } else if (selector == 1) {
        response = &D_8001B824;
    } else {
        func_80016B88();
        response = &D_8001C5FB;
    }
    return response;
}
