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
    register u8 *value ASM_REG("$3");
    register s32 offset ASM_REG("$6");
    register s32 wide_step ASM_REG("$5");

    wide_step = step;
    ASM_KEEP(wide_step);
    value = &record->value;
    offset = 0;
    ASM_KEEP(value);
    ASM_KEEP(offset);

    *value += offset;
    if (record->state < 0) {
        return;
    }
    offset += wide_step;
    value += sizeof(Record);
    record++;
    ASM_KEEP(value);
    ASM_TAILSLOT_PIN_TIED(record);
    func_800A6BCC(record, wide_step, offset);
}

/* MECHANISM: $v1/$a2/$a1 guarded locals preserve the exact frameless body roles.
   The tied tail-slot pin marks record++'s addiu $a0,$a0,12 for LEAD 28b,
   which sinks it into the LEAD-22 tail-j delay slot and removes the +1 drift. */
