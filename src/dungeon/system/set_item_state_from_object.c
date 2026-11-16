#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item.h"
#include "dungeon/system.h"


typedef struct S_800255AC_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800255AC_0;   /* arg0 in set_item_state_from_object */

/* Passes the object's stored value to select_item_window_final_action. */
void set_item_state_from_object(S_800255AC_0 *object) {
    select_item_window_final_action(object->unk_40);
}
