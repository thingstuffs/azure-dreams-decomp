#include "common.h"

/* Initialize fifteen four-byte records with sequential IDs and append a zero terminator. */
void *func_805D3AC8(void *records) {
    s32 record_count = 0;
    register s32 record_id ASM_REG("$5") = 1;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 initial_value = 0x19;
    register void *record ASM_REG("$3") = records;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s8 *terminator;

    do {
        *((s8 *)record + 0) = record_id;
        *((s8 *)record + 1) = initial_value;
        *((s8 *)record + 3) = 0;
        *((s8 *)record + 2) = 0;
        record += 4;
        record_id += 1;
        record_count += 1;
    } while (record_id < 0x10);

    terminator = (s8 *)((u32)(record_count * 4) + (u32)records);
    terminator[1] = 0;
    terminator[0] = 0;
    return records;
}

/* MECHANISM: Frameless leaf; a2 stays natural while a1/a3/v1/v0 hold the retail roles.
   Naming the invariant a3 before the pointer init fixes the opening emission order.
   An ordered u32 tail sum preserves retail's addu v0,v0,a0 operand order. */
