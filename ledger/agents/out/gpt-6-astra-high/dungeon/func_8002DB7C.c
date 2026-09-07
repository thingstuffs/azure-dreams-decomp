#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800CB04C(void *, M2C_UNK, M2C_UNK);                            /* extern */

typedef struct S_800CB2DC_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CB2DC_0;   /* arg0 in func_800CB2DC */

/* Decrements an object's countdown and invokes both handlers when it expires. */
void func_800CB2DC(S_800CB2DC_0 *object, M2C_UNK handlerContext, M2C_UNK handlerData) {
    u16 remainingCount;

    remainingCount = object->unk_6C - 1;
    object->unk_6C = remainingCount;
    if ((remainingCount << 0x10) <= 0) {
        func_800CB04C(object, handlerContext, handlerData);
        func_800C4174(object, handlerContext, handlerData);
    }
}
