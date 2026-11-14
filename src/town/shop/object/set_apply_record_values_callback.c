#include "common.h"
#include "m2c_compat.h"
#include "town/shop/object.h"
#include "town/shop.h"


typedef struct S_800B2CE8_0 {
    u8 pad_00[0x10];
    void (*unk_10)();
} S_800B2CE8_0;   /* arg0 in set_apply_record_values_callback */

/* Set the object's data pointer when the object is present. */
void set_apply_record_values_callback(S_800B2CE8_0 *object) {
    if (object != NULL) {
        object->unk_10 = &close_item_move_menu;
    }
}
