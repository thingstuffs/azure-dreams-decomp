#include "common.h"
#include "town/scene/flags.h"
#include "town/devkit.h"
extern s32 D_A0700A3C[];

/* Run the indexed operation and return the base plus its table value. */
s32 run_indexed_operation_plus_base(s32 table_index, s32 call_input, s32 call_param) {
    dispatch_entry_flags_a0700244(table_index);
    return *(s32 *)0xA0700B38 + D_A0700A3C[table_index];
}

/* MECHANISM: Preserve the seed's 24-byte frame and s0-held index across the call. */
