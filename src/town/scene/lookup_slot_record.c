#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

typedef struct S_806D43CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D43CC_0;   /* arg0 in lookup_slot_record */

/* Performs conditional object setup before forwarding to func_800176B8. */
void lookup_slot_record(S_806D43CC_0 *object, s32 forwardedValue) {
    if (get_script_flag_mask(F_05_niko_and_gosh) != 0) {
        write_script_flag_range(F_sbs34_pad16, 2, 2);
        set_script_flag_bit(object->unk_18);
    }
    apply_selected_entry_values(object, forwardedValue);
}
