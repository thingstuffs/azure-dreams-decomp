#include "engine/scene/cd_cohort_types.h"

/* Reset the global state fields and initialize the status bytes to 2 and 255. */
void reset_cd_command_retry_state(void) {
    *(u8 *)0x800814D2 = 2;
    *(u8 *)0x800814D3 = 0xFF;
    cd_driver_prefix[0].unk0 = 0;
    cd_command_read_index = 0;
    *(u8 *)0x800814D1 = 0;
    cd_driver_prefix[0].unk4 = 0;
    cd_driver_prefix[0].unk5 = 0;
    D_80080AD0 = 0;
    cd_event_payload = 0;
    cd_retry_counters_pending = 0;
    cd_driver_prefix[0].counter1 = 0;
    cd_driver_prefix[0].counter2 = 0;
}
