#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

void clear_progress_and_dispatch_code_12_cb(void *handler_id, s32 handler_arg) {
    town_scene_root->event_data->unk_B0 = 0;
    set_script_flag_bit(F_takoyaki_morau);
    apply_selected_entry_values(handler_id, handler_arg);
}
