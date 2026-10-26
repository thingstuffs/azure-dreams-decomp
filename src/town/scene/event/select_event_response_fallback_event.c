#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"


extern u8 scene_string_fallback[];
extern u8 D_8001B9E0[];
extern u8 event_string_fallback[];
extern u8 D_80020934[];

extern void *select_address_based_input(s32, s32);


extern void func_8001A554(s32);

/* Select event response data, using a fallback when an event handler returns null. */
void *select_event_response_fallback_event(s32 handler_arg_a, s32 handler_arg_b, s32 selector)
{
    void *result;

    switch (selector - 12) {
    case 7:
        /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: town/func_8070E180). */
        do {
            result = select_address_based_input(handler_arg_a, handler_arg_b);
        } while (0);
        scene_event_results[0] = result;
        if (result != 0) {
            return result;
        }
        return D_8001B9E0;
    case 6:
        result = get_local_global_table();
        scene_event_results[0] = result;
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
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
