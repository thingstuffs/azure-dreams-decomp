#include "common.h"
#include "m2c_compat.h"
#include "town/shop/object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void D_800B1664(void *object);

typedef struct S_800B1718_0 {
    u8 pad_00[0x10];
    void (*unk_10)();
} S_800B1718_0;   /* arg0 in set_shop_object_data_if_present */

/* Sets the object's data pointer when the object is present. */
void set_shop_object_data_if_present(S_800B1718_0 *object) {
    if (object != NULL) {
        object->unk_10 = &D_800B1664;
    }
}
