#include "common.h"

extern char D_8001B14C[];
extern char D_8001C018[];
extern char D_8001D000[];
extern char D_800227FB[];

extern char *func_80016E48(s32, s32, s32, s32);
extern void func_8001A554(u32);
extern s32 func_8001A64C(u32);

/* Selects text by ID, setting event 0x948 for selector 12. */
char *func_80017F90(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
{
    s32 arg2_val;
    u32 case_index;

    case_index = selector_id - 12;
    arg2_val = selector_id;
    switch (case_index) {
    case 7:
        return D_8001C018;
    case 6:
        return D_800227FB;
    case 0:
        if (func_8001A64C(0x948) == 0) {
            func_8001A554(0x948);
        }
        return D_8001D000;
    case 40:
    case 41:
    case 42:
        return func_80016E48(selector_id, passthru_1, arg2_val, passthru_3);
    default:
        return D_8001B14C;
    }
}
