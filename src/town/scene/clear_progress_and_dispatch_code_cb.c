#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

void clear_progress_and_dispatch_code_12_cb(void *handler_id, s32 handler_arg) {
    ((TownProgressState *)town_scene_root->event_data)->unk_B0 = 0;
    func_8001A418(F_takoyaki_morau);
    func_80019814(handler_id, handler_arg);
}
