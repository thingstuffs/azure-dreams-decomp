#include "script_symbols.h"
#include "common.h"

extern void *D_8001B16C[];
extern u8 D_8001B14C[];
extern u8 D_8001B9E0[];
extern u8 D_8001C6D0[];
extern u8 D_80020934[];

extern void *select_address_based_input(s32, s32);
extern void *get_local_global_table(void);
extern void *award_next_unearned_milestone(s32);
extern void func_8001A554(s32);

/* Select event response data, using a fallback when an event handler returns null. */
void *select_event_response_fallback_event(s32 handler_arg_a, s32 handler_arg_b, s32 selector)
{
    void *result;

    switch (selector - 12) {
    case 7:
        do {
            result = select_address_based_input(handler_arg_a, handler_arg_b);
        } while (0);
        D_8001B16C[0] = result;
        if (result != 0) {
            return result;
        }
        return D_8001B9E0;
    case 6:
        result = get_local_global_table();
        D_8001B16C[0] = result;
        if (result != 0) {
            return result;
        }
        func_8001A554(F_sbs32_pad25);
        return D_80020934;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
