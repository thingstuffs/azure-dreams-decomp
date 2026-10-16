#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void runtimeSetRecordValueAndBuffer();              /* extern */
extern u8 D_80082A38[];

/* Passes the value and the shared object to runtimeSetRecordValueAndBuffer. */
void func_8003528C(s32 value) {
    runtimeSetRecordValueAndBuffer(&D_80082A38, value);
}
