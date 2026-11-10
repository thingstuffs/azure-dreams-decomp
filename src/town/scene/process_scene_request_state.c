#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"

s32 apply_selected_entry_values(s32, s32);
extern void set_script_flag_bit(s32); /* placed copy of set_script_flag_bit */

typedef struct S_800164E8_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800164E8_0;   /* arg0 in process_scene_request_state */

/* Process the object identifier and 0x50C before forwarding the object and value. */
void process_scene_request_state(S_800164E8_0 *object, s32 value) {
    set_script_flag_bit(object->unk_18);
    clear_script_flag_bit(F_sbs07_pad21);
    apply_selected_entry_values(object, value);
}
