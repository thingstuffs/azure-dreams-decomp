#include "common.h"

extern void *D_80016910[43];

extern char D_8001B14C[];
extern char D_8001C018[];
extern char D_8001D6B5[];
extern char D_8001D7A5[];
extern char D_800227FB[];

extern char *func_80016E48(s32);
extern s32 func_8001A64C(u32);

/* Selects a string, with a state-dependent choice for selector 12. */
char *func_8001825C(s32 unused_0, s32 unused_1, s32 text_id)
{
    register s32 selector = text_id;
    u32 table_index;
    static void *const case_labels[] = {
        &&L_case19, &&L_case18, &&L_case12, &&L_case52, &&L_default
    };

    table_index = selector - 12;
    if (table_index >= 43) {
        goto L_default;
    }
    goto *D_80016910[table_index];

L_case19:
    return D_8001C018;

L_case18:
    return D_800227FB;

L_case12:
    if (func_8001A64C(0x94A) != 0) {
        return D_8001D6B5;
    }
    return D_8001D7A5;

L_case52:
    return func_80016E48(selector);

L_default:
    return D_8001B14C;
}
