#include "common.h"
#include "town/scene.h"

extern s32 get_linked_record_field_2_d_60(s32, s32);
extern void func_80016A78(void);

/* Run the conditional handler for values of at least five, then process the inputs. */
void run_conditional_handler_and_process(s32 input_a, s32 input_b) {
    if (get_linked_record_field_2_d_60(input_a, input_b) >= 5) {
        func_80016A78();
    }
    process_checked_entry(input_a, input_b);
}
