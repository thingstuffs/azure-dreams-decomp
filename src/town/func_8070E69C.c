#include "common.h"

extern void *D_80016390[43];

extern char D_8001B14C[];
extern char D_8001BA48[];
extern char D_8001C6D0[];
extern char D_800213D4[];

extern char *func_80016E48(s32);
extern void func_8001A554(s32);

/* Selects a string and performs any associated action. */
char *func_8001769C(s32 unused_0, s32 unused_1, s32 selection_id)
{
    s32 selector = selection_id;
    u32 table_index;
    static void *const case_labels[] = {
        &&L_case19, &&L_case18, &&L_case52, &&L_case12, &&L_default
    };

    table_index = selector - 12;
    if (table_index >= 43) {
        goto L_default;
    }
    goto *D_80016390[table_index];

L_case19:
    func_8001A554(0x932);
    return D_8001BA48;

L_case18:
    return D_800213D4;

L_case52:
    return func_80016E48(selector);

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
