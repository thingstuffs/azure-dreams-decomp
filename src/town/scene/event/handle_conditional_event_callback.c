#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


extern s32 check_callback_record_bytes(s32, s32);
extern void set_current_entry_script_flag(void);
extern void apply_entry_position(void *, void *, s32, s32);
extern void set_script_flag_bit(s32);
extern s32 get_script_flag_mask(s32);
extern M2C_UNK D_8001BE2C;
extern M2C_UNK D_8001BE44;
extern M2C_UNK scene_dispatch_context;


/* Handles the conditional callback and selects data according to flag 0x1460. */
void handle_conditional_event_callback(s32 context, s32 unused, s32 event_code) {
    void *selected_data;

    if ((event_code == 0x1E) && (check_callback_record_bytes(0xD, 1) != 0)) {
        D_80016000->unk_20->callback_078(0);
        set_script_flag_bit(Ftt_fkoya_isaku_scene01_ok);
        set_current_entry_script_flag();
    }

    if (get_script_flag_mask(Ftt_fkoya_isaku_scene01_ok) != 0) {
        selected_data = &D_8001BE2C;
    } else {
        selected_data = &D_8001BE44;
    }
    apply_entry_position(selected_data, &scene_dispatch_context, context, event_code);
}
