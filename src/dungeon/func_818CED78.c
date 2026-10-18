#include "modules/dungeon_ovl_18ee800.h"
#include "common.h"
#include "shared/object_flags.h"


/* Decrement the record counter and set completion flags when it reaches zero. */
void update_actor_effect_sequence(void *record)
{
    u8 *record_bytes = record;
    u16 counter;

    counter = *(u16 *)(record_bytes + 2);
    D_80025924[0] = 1;
    counter--;
    *(u16 *)(record_bytes + 2) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(record_bytes - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* MECHANISM: A long-lived u8 base preserves the retail may-alias load-delay nops.
   Loading the counter before the global store lets that store cover load latency
   and naturally yields the a1 pointer, a0 constant, and v1 counter roles. */
