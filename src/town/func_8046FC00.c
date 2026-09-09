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
    u8 *page_base;
    u8 *response_table;
    s32 *response;

    if (selector == 9) {
        if (func_80017E98(context, check_value) != 0) {
            if (func_8001A510(0x798) != 0) {
                page_base = (u8 *)0x80020000;
                ASM_KEEP(page_base);
                return (s32 *)(page_base - 0x4930);
            }
            if (func_8001A510(0x47D) == 0) {
                page_base = (u8 *)0x80020000;
                ASM_KEEP(page_base);
                return (s32 *)(page_base - 0x49C4);
            }
        }
        response_table = (u8 *)0x80020000;
        ASM_KEEP(response_table);
        response_table -= 0x568C;
        response = func_80019ABC(response_table, &D_8001B1FC, context, selector);
        if (func_80019A04(response_table, context, selector) != 0) {
            page_base = (u8 *)0x80020000;
            ASM_KEEP(page_base);
            response = (s32 *)(page_base - 0x39B2);
        }
    } else if (selector == 1) {
        page_base = (u8 *)0x80020000;
        ASM_KEEP(page_base);
        response = (s32 *)(page_base - 0x47DC);
    } else {
        func_80016B88();
        page_base = (u8 *)0x80020000;
        ASM_KEEP(page_base);
        response = (s32 *)(page_base - 0x3A05);
    }
    return response;
}
