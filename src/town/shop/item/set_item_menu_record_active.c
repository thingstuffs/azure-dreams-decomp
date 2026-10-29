#include "common.h"
#include "m2c_compat.h"
#include "town/shop/item.h"

typedef struct S_800B0418_0 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_800B0418_0;   /* arg0 in set_item_menu_record_active */

/* Sets the object's unk_30 field to one. */
void set_item_menu_record_active(S_800B0418_0 *object) {
    object->unk_30 = 1;
}
