#include "common.h"

extern void *D_80016230[43];

extern char D_8001B14C[];
extern s32 D_8001B16C[];
extern char D_8001B9E0[];
extern char D_8001C6D0[];
extern char D_80020E44[];

extern s32 func_80016CE4(s32, s32);
extern s32 func_80016D18(void);
extern char *func_80016E48(s32);

/* Select event data, using fallback data when an event handler returns null. */
char *func_8001747C(s32 forwarded_arg, s32 forwarded_aux, s32 event_id)
{
    s32 result_addr;
    u32 case_index;
    void **dispatch_table;
    register s32 selector ASM_REG("$6") = event_id;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    static void *const case_labels[] = {
        &&case_19,
        &&case_18,
        &&case_52,
        &&case_12,
        &&default_case
    };

    case_index = event_id - 12;
    if (case_index >= 43) {
        goto default_case;
    }
    dispatch_table = D_80016230;
    (void)case_labels;
    goto *dispatch_table[case_index];

case_19:
    result_addr = func_80016CE4(forwarded_arg, forwarded_aux);
    D_8001B16C[0] = result_addr;
    if (result_addr != 0) {
        goto return_result;
    }
    return D_8001B9E0;

case_18:
    result_addr = func_80016D18();
    D_8001B16C[0] = result_addr;
    if (result_addr == 0) {
        goto case_18_zero;
    }

return_result:
    return (char *)result_addr;

case_18_zero:
    return D_80020E44;

case_52:
    return func_80016E48(selector);

case_12:
    return D_8001C6D0;

default_case:
    return D_8001B14C;
}
