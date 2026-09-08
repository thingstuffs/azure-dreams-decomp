#include "common.h"

typedef void (*Func)(u32);

extern Func D_800294B8[];

/* Calls the indexed handler with its record argument and clears the record state. */
void func_80025548(s32 *record) {
    s32 handler_index = record[3];

    D_800294B8[handler_index](record[handler_index + 8]);
    record[-4] = 0;
}
