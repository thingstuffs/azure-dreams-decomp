#include "common.h"

extern s32 D_80019AFC;

extern s32 dispatch_state_entry_event_8(s32, s32, s32, s32);
extern s32 process_event_ids_and_succeed(void);
extern s32 run_operation(void);

/* Dispatches to the handler selected by the global mode. */
s32 dispatch_by_global_mode(s32 handler_input_a, s32 handler_input_b, s32 handler_input_c, s32 handler_input_d) {
    if (D_80019AFC == 0) {
        return dispatch_state_entry_event_8(handler_input_a, handler_input_b, handler_input_c, handler_input_d);
    }
    if (D_80019AFC == 1) {
        return process_event_ids_and_succeed();
    }
    if (D_80019AFC == 3) {
        return run_operation();
    }
    return 0;
}
