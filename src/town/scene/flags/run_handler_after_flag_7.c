#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"

extern s32 func_80017990(s32);
extern void func_80016CD8(void);
extern void get_helper_result(s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */

/* If flag 7 is set, call func_80016CD8 first; then get_helper_result(target, value). */
void run_value_handler_after_flag_check(s32 target, s32 value) {
    if (func_80017990(7) != 0) {
        func_80016CD8();
    }
    get_helper_result(target, value);
}
