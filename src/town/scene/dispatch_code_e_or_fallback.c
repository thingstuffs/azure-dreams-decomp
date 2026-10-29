#include "common.h"

extern void select_response_and_set_d_80(s32, s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */
extern void *select_data_pointer_based_result(void);

/* Forward values for code 0x1E, otherwise call the fallback handler. */
void dispatch_code_1_e_or_fallback(s32 first_value, s32 second_value, s32 code) {
    if (code != 0x1E) {
        select_data_pointer_based_result();
        return;
    }
    select_response_and_set_d_80(first_value, second_value, 0x1E);
}
