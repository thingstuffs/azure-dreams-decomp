#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void D_800B93B8();

typedef struct S_800B93C0_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B93C0_0;

/* Allocate an object and set its data pointer. */
void allocate_second_object_variant(void) {
    S_800B93C0_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->unk_10 = &D_800B93B8;
    }
}
