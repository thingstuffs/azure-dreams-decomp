#include "common.h"

extern void *D_800167B0[43];

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
    static void *const case_labels[] = {
        &&L_case19, &&L_case18, &&L_case12, &&L_case52, &&L_default
    };

    case_index = selector_id - 12;
    arg2_val = selector_id;
    if (case_index >= 43) {
        goto L_default;
    }
    goto *D_800167B0[case_index];

L_case19:
    return D_8001C018;

L_case18:
    return D_800227FB;

L_case12:
    if (func_8001A64C(0x948) == 0) {
        func_8001A554(0x948);
    }
    return D_8001D000;

L_case52:
    return func_80016E48(selector_id, passthru_1, arg2_val, passthru_3);

L_default:
    return D_8001B14C;
}
