#include "common.h"

s32 check_ready_or_run_followup(s32);
s32 func_8001779C(s32);

/* Apply five operations through func_8001779C, then process 0x9E1. */
void run_events_9da_to_9dc(void) {
    func_8001779C(0x12C1);
    func_8001779C(0x12C0);
    func_8001779C(0x9DA);
    func_8001779C(0x9DB);
    func_8001779C(0x9DC);
    check_ready_or_run_followup(0x9E1);
}
