#include "common.h"

extern s32 apply_record_value_for_either_flag(s32, s32);
extern s32 func_80016A78();
extern s32 func_80016B20();

/* Run the conditional handler for values of at least five, then process the inputs. */
void run_conditional_handler_and_process(s32 input_a, s32 input_b) {
    if (apply_record_value_for_either_flag(input_a, input_b) >= 5) {
        func_80016A78();
    }
    func_80016B20(input_a, input_b);
}
