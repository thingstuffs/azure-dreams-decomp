#include "shared/object_node.h"
#include "town/map/animation.h"
#include "common.h"
#include "town/map.h"
#include "town/map/variant_data.h"

typedef struct Obj {
    u8 pad0[0x10];
    void *handler;
    u8 pad14[0xC];
    s16 animation_tick;
    s16 field22;
} Obj;

/* Initialize the object's selection and assign a handler based on the selected entry's kind. */
void initialize_building_selection_handler(void) {
    Obj *obj;
    TownMapVariantRecord *entry_table;
    u8 *entry_indices;
    TownMapVariantRecord *entry;
    u8 entry_index;
    s32 entry_kind;

    obj = allocate_flagged_object_node(0);
    if (obj != 0) {
        entry_table = town_map_variants;
        entry_indices = &town_map_variant;
        obj->animation_tick = 0;
        entry_index = entry_indices[obj->animation_tick];
        entry = &entry_table[entry_index];
        entry_kind = (obj->field22 = entry->entry_kind);

        if (entry_kind != 0x21) {
            if (entry_kind >= 0x21) {
                if (entry_kind < 0x29) {
                    if (entry_kind >= 0x26) {
                        obj->handler = advance_building_texture_and_palette;
                        return;
                    }
                }
            }
        } else {
            obj->handler = advance_building_texture_frame;
            return;
        }
        obj->handler = advance_building_animation_frame;
    }
}
