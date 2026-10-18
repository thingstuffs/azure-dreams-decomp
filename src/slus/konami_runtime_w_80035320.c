#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void runtime_set_record_byte_three();              /* extern */
extern u8 D_80082A38[];

/* Passes the value to runtime_set_record_byte_three with the shared state. */
void func_80035320(s32 value) {
    runtime_set_record_byte_three(&D_80082A38, value);
}
