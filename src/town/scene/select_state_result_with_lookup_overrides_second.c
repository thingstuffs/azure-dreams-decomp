#include "script_symbols.h"
#include "common.h"

extern void func_800193E0(s32);
extern void *check_inputs_after_threshold_two(void *);

extern s32 D_8001967C[3];
extern void *D_80019688[3];
extern u8 D_8001A730[9];
extern u8 D_8001AAEC[9];
extern u8 D_8001DE58[9];

/* Returns data for the request type and current selection. */
void *select_state_result_with_lookup_overrides(s32 unused_0, s32 unused_1, s32 request_type) {
    void *result = 0;

    if (request_type == 8) {
        func_800193E0(Ft_paty_new);
        result = check_inputs_after_threshold_two(D_80019688[D_8001967C[0]]);
    } else if (request_type == 6) {
        result = D_8001A730;
    } else if (request_type == 1) {
        if (D_8001967C[0] != 3) {
            result = D_8001DE58;
        } else {
            result = D_8001AAEC;
        }
    }

    return result;
}
