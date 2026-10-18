#include "modules/town_ovl_3ef1c8.h"

void clear_progress_and_dispatch_code_12_cb(s32 handler_id, s32 handler_arg) {
    ((TownProgressState *)D_80016000->unk_40)->unk_B0 = 0;
    func_8001A418(0x12CB);
    func_80019814(handler_id, handler_arg);
}
