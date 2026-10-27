#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void D_800B2C6C(void *record);

typedef struct S_800B2CE8_0 {
    u8 pad_00[0x10];
    void (*unk_10)();
} S_800B2CE8_0;   /* arg0 in set_object_data_pointer_if_present */

/* Set the object's data pointer when the object is present. */
void set_object_data_pointer_if_present(S_800B2CE8_0 *object) {
    if (object != NULL) {
        object->unk_10 = &D_800B2C6C;
    }
}
