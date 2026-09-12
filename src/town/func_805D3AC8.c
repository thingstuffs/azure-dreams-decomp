#include "common.h"

/* Initialize fifteen four-byte records with sequential IDs and append a zero terminator. */
void *func_805D3AC8(void *records) {
    s32 record_count = 0;
    s32 record_id = 1;
    s32 initial_value = 0x19;
    void *record = records;
    s8 *terminator;

    loop_0: {
        *((s8 *)record + 0) = record_id;
        *((s8 *)record + 1) = initial_value;
        *((s8 *)record + 3) = 0;
        *((s8 *)record + 2) = 0;
        record += 4;
        record_id += 1;
        record_count += 1;
    } if (record_id < 0x10) goto loop_0;

    terminator = (s8 *)((u32)(record_count * 4) + (u32)records);
    terminator[1] = 0;
    terminator[0] = 0;
    return records;
}

/* MECHANISM: Frameless leaf; a2 stays natural while a1/a3/v1/v0 hold the retail roles.
   Naming the invariant a3 before the pointer init fixes the opening emission order.
   An ordered u32 tail sum preserves retail's addu v0,v0,a0 operand order. */
