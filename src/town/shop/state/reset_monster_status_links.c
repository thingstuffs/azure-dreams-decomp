#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "town/shop/state.h"
#include "town/shop/object.h"


/* Clears two linked values and initializes the object's embedded data. */
void reset_monster_status_links(ShopFirstCallbackObject *object) {
    ItemMenuPart *part;
    s32 slotIndex;

    slotIndex = 0x14;
    do {
        part = object->parts[slotIndex];
        slotIndex += 1;
        part->handler = 0;
    } while (slotIndex < 0x16);
    object->parts[23]->handler = object->pad_18;
    set_monster_status_panel_height(object->parts[23]->handler, 0);
}
