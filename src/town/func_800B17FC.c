#include "common.h"
#include "shared/menu_display.h"
#include "engine/texture.h"
#include "engine/util.h"
#include "town.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "shared/item_menu.h"

/* Initializes the object handle and applies the default configuration on success. */
s32 load_item_menu_display_resource(ItemMenuTransition *object, s32 resource_id) {
    s32 success = 0;
    ItemMenuPart **parts = (ItemMenuPart **)func_80049004((s32 *)object->allocations, resource_id, 8);

    object->rows.as_ptr = parts;
    if (parts != 0) {
        object->part_vector.unk0 = display_vector_defaults.unk0;
        object->part_vector.unk4 = display_vector_defaults.unk4;
        object->part_vector.unk8 = display_vector_defaults.unk8;
        set_menu_part_vectors(parts, &object->part_vector, 0x1A);
        success = 1;
    }
    return success;
}
