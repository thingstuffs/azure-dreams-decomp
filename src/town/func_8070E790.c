#include "common.h"

extern char D_8001B14C[];
extern char D_8001BCB4[];
extern char D_8001C6D0[];
extern char D_80021484[];

extern char *func_80016E48(s32, s32, s32, s32);
extern void func_8001A554(s32);

/* Selects a response string and triggers the event for selector 18. */
char *func_80017790(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
{
    s32 arg2_val;
    u32 case_index;

    case_index = selector_id - 12;
    arg2_val = selector_id;
    switch (case_index) {
    case 7:
        return D_8001BCB4;
    case 6:
        func_8001A554(0x933);
        return D_80021484;
    case 40:
    case 41:
    case 42:
        return func_80016E48(selector_id, passthru_1, arg2_val, passthru_3);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
