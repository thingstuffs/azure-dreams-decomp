#include "common.h"

typedef struct {
    s8 state;
    u8 pad1;
    u8 value;
    u8 pad3[9];
} Record;

extern void func_800A6BCC(Record *, s32, s32);

void func_800A6BBC(Record *record, s16 step)
{
    u8 *value;
    s32 offset;
    s32 wide_step;

    wide_step = step;
    ASM_KEEP(wide_step);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    value = &record->value;
    offset = 0;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    *value += offset;
    if (record->state < 0) {
        return;
    }
    offset += wide_step;
    value += sizeof(Record);
    record++;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_TAILSLOT_PIN_TIED(record);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    func_800A6BCC(record, wide_step, offset);
}

/* MECHANISM: $v1/$a2/$a1 guarded locals preserve the exact frameless body roles.
   The tied tail-slot pin marks record++'s addiu $a0,$a0,12 for LEAD 28b,
   which sinks it into the LEAD-22 tail-j delay slot and removes the +1 drift. */
