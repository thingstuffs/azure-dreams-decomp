#include "common.h"

typedef void (*Func)(u32);

extern Func D_800294B8[];

/* Calls the selected callback with its stored argument and clears the preceding state field. */
void func_80025548(s32 *callback_data) {
    s32 callback_index = callback_data[3];

    D_800294B8[callback_index](callback_data[callback_index + 8]);
    callback_data[-4] = 0;
}
