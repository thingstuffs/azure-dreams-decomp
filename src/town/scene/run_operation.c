#include "common.h"
#include "m2c_compat.h"

void decrement_current_entry_counter_condition(void);                            /* extern */
s32 invoke_system_callback_21_c();         /* extern */
s32 func_80018044(); /* extern */
s32 func_8001894C();                             /* extern */
extern s16 scene_request_flag_id;
extern M2C_UNK D_80018B28;
extern s32 D_80018E38;

/* Runs the operation and invokes the fallback when both checks return zero. */
s32 run_operation(s32 input, s32 unused, s32 aux_input) {
    s32 result;

    result = func_80018044(&D_80018B28, &D_80018E38, input, aux_input);
    if ((func_8001894C(scene_request_flag_id) == 0) && (invoke_system_callback_21_c(&D_80018B28, input, aux_input) == 0)) {
        decrement_current_entry_counter_condition();
    }
    return result;
}
