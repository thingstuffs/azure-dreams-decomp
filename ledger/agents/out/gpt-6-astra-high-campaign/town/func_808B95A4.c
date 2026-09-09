#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700244(s32, s32, s32);                            /* extern */
extern s32 D_A0700A3C[];

/* Run the indexed operation and return the base plus its table value. */
s32 func_808B95A4(s32 table_index, s32 call_input, s32 call_param) {
    func_80700244(table_index, call_input, call_param);
    return *(s32 *)0xA0700B38 + D_A0700A3C[table_index];
}

/* MECHANISM: Preserve the seed's 24-byte frame and s0-held index across the call.
   Naming the indexed fixed-address table as an extern makes gcc emit a symbolic load,
   so maspsx expands it as retail's addu $at,$at,$s0 instead of the commuted form. */
