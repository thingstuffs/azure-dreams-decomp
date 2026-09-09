#include "common.h"

typedef struct {
    s8 state;
    u8 pad1;
    u8 value;
    u8 pad3[9];
} Record;

/* Adds successive multiples of the step to record values through the terminal record. */
void func_800A6BBC(Record *record, s16 step)
{
    u8 *value;
    s32 offset;
    s32 wide_step;

    wide_step = step;
    value = &record->value;
    offset = 0;

    for (;;) {
        *value += offset;
        if (record->state < 0) {
            return;
        }
        offset += wide_step;
        value += sizeof(Record);
        record++;
    }
}

/* MECHANISM: retail word 4 (`j 0x800A6BCC` == true_name+0x10) is a loop
   back-edge, not a call -- func_800A6BCC was m2c's fake callee name for the
   function's own mid-body label. Written as the for(;;) it actually is, gcc's
   own dbr sinks record++'s addiu into the back-edge j's delay slot with no
   pin; the former ASM_KEEP(value)/ASM_TAILSLOT_PIN_TIED(record) pair (needed
   only to fake liveness across the old pseudo-call) is gone along with the call. */
