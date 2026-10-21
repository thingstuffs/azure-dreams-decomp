/* G00734: Run the operation selected by the global mode.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_805D29B4, CL:town/func_805D2A4C.
 * Exclude the weaker left CL:town/func_805D29B4 join; complete file edges remain unknown.
 */
#ifndef TOWN_SCENE_GLOBAL_MODE_DISPATCH_G00734_H
#define TOWN_SCENE_GLOBAL_MODE_DISPATCH_G00734_H

#include "common.h"

extern s32 check_inputs_after_threshold_two(s32);
extern void func_80018570(void);
extern s32 D_8001967C;
extern s32 D_8001970C[];
extern s32 D_80019AFC;
extern s32 dispatch_state_entry_event_8(s32, s32, s32, s32);
extern s32 process_event_ids_and_succeed(void);

/* Functions defined in this translation unit. */
s32 run_operation(s32 unused_context, s32 unused_arg, s32 event_kind);
s32 dispatch_by_global_mode(s32 handler_input_a, s32 handler_input_b, s32 handler_input_c, s32 handler_input_d);

#endif
