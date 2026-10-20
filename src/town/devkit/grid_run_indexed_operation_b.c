#include "common.h"

s32 func_80700244(s32, s32, s32);
extern s32 D_A0700A3C[];

/* Run the indexed operation and return the base plus its table value. */
s32 grid_run_indexed_operation_b(s32 table_index, s32 call_input, s32 call_param) {
    func_80700244(table_index, call_input, call_param);
    return *(s32 *)0xA0700B38 + D_A0700A3C[table_index];
}

/* MECHANISM: Preserve the seed's 24-byte frame and s0-held index across the call. */
