#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800B93F4;

typedef struct S_800B93FC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B93FC_0;

/* Allocate an object and set its data pointer. */
void townAllocateThirdObjectVariant(void) {
    S_800B93FC_0 *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = &D_800B93F4;
    }
}
