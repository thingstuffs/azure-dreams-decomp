#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void runtimeSetRecordByteThree();              /* extern */
extern u8 D_80082A38[];

/* Passes the value to runtimeSetRecordByteThree with the shared state. */
void func_80035320(s32 value) {
    runtimeSetRecordByteThree(&D_80082A38, value);
}
