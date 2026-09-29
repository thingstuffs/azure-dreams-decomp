#include "common.h"

extern char D_8001B14C[];
extern char D_8001C018[];
extern char D_8001C6D0[];
extern char D_8001D000[];
extern char D_8001D3CC[];
extern char D_80022694[];

extern s32 func_8001A8EC(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern char *func_80016E48(s32, s32, s32, s32);

/* Selects a response from the selector and status flags, updating flags for special cases. */
char *func_80017C08(s32 unused, s32 value, s32 selection, s32 extra)
{
    s32 selector = selection;
    s32 arg2_val;
    u32 table_index;

    table_index = selector - 12;
    arg2_val = selector;
    switch (table_index) {
    case 7:
        return D_8001C018;
    case 6:
        return D_80022694;
    case 0:
        if (func_8001A8EC(6) != 0) {
            func_8001A554(0x93A);
        }
        if (func_8001A8EC(0xB) != 0) {
            func_8001A554(0x93B);
        }
        if (func_8001A64C(0x93A) != 0) {
            goto L9;
        }
        if (func_8001A64C(0x93B) != 0) {
            goto L9;
        }
        if (func_8001A64C(0x948) == 0) {
            goto L6;
        }
        {
            s32 flag_94a_set = func_8001A64C(0x94A);
            if (flag_94a_set == 0) {
                goto L7tail;
            }
        }
        goto L6;

L9:
        if (func_8001A64C(0x93A) == 0) {
            goto L10;
        }
        if (func_8001A64C(0x93B) == 0) {
            goto L7tail;
        }

L10:
        if (func_8001A64C(0x93A) != 0) {
            goto L7;
        }
        if (func_8001A64C(0x93B) == 0) {
            goto L7;
        }
        goto L6;

L6:
        func_8001A554(0x948);
        return D_8001D000;

L7:
        if (func_8001A64C(0x93A) == 0) {
            goto L8;
        }
        if (func_8001A64C(0x93B) == 0) {
            goto L8;
        }

L7tail:
        func_8001A554(0x94A);
        func_8001A554(0x12C7);
        return D_8001D3CC;

L8:
        return D_8001C6D0;
    case 40:
    case 41:
    case 42:
        return func_80016E48(selector, value, arg2_val, extra);
    default:
        return D_8001B14C;
    }
}
