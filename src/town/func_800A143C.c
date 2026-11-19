#include "common.h"
#include "town/shop/item_lookup.h"
#include "town.h"

/*
 * Returns zero when get_item_chk finds no item; otherwise updates the indexed item data and
 * removal flags and returns one.
 */
s32 remove_object_if_item_found(void *object, void *unused_subject, struct ObjectPosition *unused_motion,
                                struct SpriteFrameState *unused_sprite, s32 *unused_work) {
    s32 item_index;

    item_index = get_item_chk();
    if (item_index == -1) {
        return 0;
    }
    remove_object_with_item_data(object, item_index);
    return 1;
}
