/* Relink of matched dungeon/func_8002DB7C; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK townApplyObjectSetupAndUpdate();    /* extern */
M2C_UNK townSetRecordDataPointer(void *);                            /* extern */


/* Decrements an object's countdown and invokes both handlers when it expires. */
void advanceObjectCountdownAndInvokeHandlers(Rec_func_80094268_arg0 *object, M2C_UNK handlerContext, M2C_UNK handlerData) {
    u16 remainingCount;

    remainingCount = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remainingCount;
    if ((remainingCount << 0x10) <= 0) {
        townSetRecordDataPointer(object);
        townApplyObjectSetupAndUpdate(object, handlerContext, handlerData);
    }
}
