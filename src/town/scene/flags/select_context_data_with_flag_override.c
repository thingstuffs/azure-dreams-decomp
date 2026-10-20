#include "script_symbols.h"
#include "common.h"

extern u8 *apply_entry_position();
extern s32 get_script_flag_mask();
extern u8 D_8001BDB4[16];
extern u8 D_8001C354[16];
extern u8 D_8001E20F[16];

/* Selects context data and overrides it when both event flags are set. */
u8 *select_context_data_with_flag_override(void *context, s32 unused, s32 selector) {
    u8 *selected_data;

    selected_data = apply_entry_position(D_8001BDB4, D_8001C354, context, selector);
    if (get_script_flag_mask(F_engei_build) != 0) {
        if (get_script_flag_mask(*(s16 *)((u8 *)context + 0x18)) != 0) {
            selected_data = D_8001E20F;
        }
    }
    return selected_data;
}
