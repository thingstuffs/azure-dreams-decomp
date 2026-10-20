#include "script_symbols.h"
#include "common.h"

s32 check_ready_or_run_followup(s32);
s32 func_8001779C(s32);

/* Apply five operations through func_8001779C, then process 0x9E1. */
void run_events_9da_to_9dc(void) {
    func_8001779C(F_hal_cansel);
    func_8001779C(F_hal_build);
    func_8001779C(F_sbs36_pad04);
    func_8001779C(F_sbs36_pad05);
    func_8001779C(F_sbs36_pad06);
    check_ready_or_run_followup(F_sbs36_pad11);
}
