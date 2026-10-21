/* G00734: Run the operation selected by the global mode.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_805D29B4, CL:town/func_805D2A4C.
 * Exclude the weaker left CL:town/func_805D29B4 join; complete file edges remain unknown.
 */
#include "town/scene/global_mode_dispatch_g00734.h"

/* Processes the selected entry for event eight, then runs the completion callback. */
s32 run_operation(s32 unused_context, s32 unused_arg, s32 event_kind) {
    s32 result = 0;

    if (event_kind == 8) {
        result = check_inputs_after_threshold_two(D_8001970C[scene_dispatch_mode_index]);
    }
    func_80018570();
    return result;
}

/* Dispatches to the handler selected by the global mode. */
s32 dispatch_by_global_mode(s32 handler_input_a, s32 handler_input_b, s32 handler_input_c, s32 handler_input_d) {
    if (scene_cell_dispatch_code == 0) {
        return dispatch_state_entry_event_8(handler_input_a, handler_input_b, handler_input_c, handler_input_d);
    }
    if (scene_cell_dispatch_code == 1) {
        return process_event_ids_and_succeed();
    }
    if (scene_cell_dispatch_code == 3) {
        return run_operation(handler_input_a, handler_input_b, handler_input_c);
    }
    return 0;
}
