#include "common.h"

s32 lookup_signed_index_value();                             /* extern */
void set_flagged_record_values();                /* extern */
extern s32 D_80100E2C[1];

/* Resolve the low-byte index, apply its value, and clear the pending state. */
void apply_pending_indexed_value(s32 index, s32 value) {
    s32 *pending_state;
    set_flagged_record_values(lookup_signed_index_value(index & 0xFF), value);
    pending_state = D_80100E2C;
    *pending_state = 0;
}
