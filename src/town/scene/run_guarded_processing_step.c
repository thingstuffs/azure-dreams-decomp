#include "common.h"
#include "town/scene.h"
void func_80016A78(void);
s32 get_linked_record_field_2_d_60(s32, s32);
/* Run the optional pre-step when the guard passes, then the main step. */
void run_guarded_processing_step(s32 target, s32 param)
{
    if (get_linked_record_field_2_d_60(target, param) != 0) {
        func_80016A78();
    }
    process_checked_entry(target, param);
}

/* MECHANISM: Preserve the 0x20 frame and the s0/s1 argument holds across all three calls.
   Calling func_80016A78 with no source arguments reuses a0 from the branch delay slot,
   leaving its jal delay slot nop; the following reload supplies func_80016B20. */
