#include "common.h"

extern void *D_800162E0[43];

extern char D_8001B14C[];
extern char D_8001B9E8[];
extern char D_8001C6D0[];
extern char D_80021386[];

extern char *func_80016E48(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* Selects a text string, delegating selector 52 to the shared lookup. */
char *func_80017580(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
{
    register s32 selector ASM_REG("$4") = selector_id;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u32 case_index;
    static void *const case_labels[] = {
        &&L_case19, &&L_case18, &&L_case52, &&L_case12, &&L_default
    };

    case_index = selector - 12;
    if (case_index >= 43) {
        goto L_default;
    }
    goto *D_800162E0[case_index];

L_case19:
    return D_8001B9E8;

L_case18:
    return D_80021386;

L_case52:
    return func_80016E48(selector, passthru_1, selector_id, passthru_3);

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
