#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item.h"
#include "dungeon/system.h"


typedef struct S_800255AC_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800255AC_0;   /* arg0 in set_item_state_from_object */

/* Passes the object's stored value to inventory_set_embedded_state_four. */
void set_item_state_from_object(S_800255AC_0 *object) {
    inventory_set_embedded_state_four(object->unk_40);
}
