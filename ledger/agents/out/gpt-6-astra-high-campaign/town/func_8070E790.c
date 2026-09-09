#include "common.h"

extern void *D_80016440[43];

extern char D_8001B14C[];
extern char D_8001BCB4[];
extern char D_8001C6D0[];
extern char D_80021484[];

extern char *func_80016E48(s32, s32, s32, s32);
extern void func_8001A554(s32);

/* Selects a response string and triggers the event for selector 18. */
char *func_80017790(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
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
    goto *D_80016440[case_index];

L_case19:
    return D_8001BCB4;

L_case18:
    func_8001A554(0x933);
    return D_80021484;

L_case52:
    return func_80016E48(selector, passthru_1, selector_id, passthru_3);

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
