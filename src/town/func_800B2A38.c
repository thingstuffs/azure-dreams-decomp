#include "common.h"
#include "shared/item_menu.h"
#include "engine/util.h"
#include "engine/texture.h"
#include "town.h"

extern s32 display_vector_defaults[];


/* Allocates actor display entries, shares a default vector across 40 entries, and reports success. */
s32 load_actor_display_resource(ItemMenuObject *object, s32 entry_count) {
    s32 success = 0;
    ItemMenuPart **parts = rebuild_pointer_pool(object->allocations, entry_count, 12);

    object->parts = parts;
    if (parts != 0) {
        object->part_vector.unk0 = display_vector_defaults[0];
        object->part_vector.unk4 = display_vector_defaults[1];
        object->part_vector.unk8 = display_vector_defaults[2];
        set_menu_part_vectors(parts, &object->part_vector, 40);
        success = 1;
    }
    return success;
}
