#include "script_symbols.h"
#include "common.h"
#include "shared/town_dispatch_object.h"
#include "m2c_compat.h"

s32 apply_entry_position(); /* extern */
void set_script_flag_bit();                     /* extern */
extern M2C_UNK D_8001BB44;

/* Process ID 0x145C and dispatch through D_8001BB44 and D_8001C358. */
void process_event_145_c_and_dispatch(s32 dispatch_value, s32 unused, s32 dispatch_context) {
    set_script_flag_bit(F_05_niko_and_gosh);
    apply_entry_position(&D_8001BB44, active_scene_dispatch_context, dispatch_value, dispatch_context);
}
