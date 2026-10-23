#include "shared/object_node.h"
#include "common.h"

typedef struct Obj {
    u8 pad0[0x10];
    void *handler;
    u8 pad14[0xC];
    s16 field20;
    s16 field22;
} Obj;

extern u8 town_map_variants[];
extern u8 town_map_variant[];
extern s32 building_resource_update_address;
extern s32 D_800B7E78;
extern s32 D_800B7F8C;

/* Initialize the object's selection and assign a handler based on the selected entry's kind. */
void initialize_building_selection_handler(void) {
    Obj *obj;
    u8 *entry_table;
    u8 *entry_indices;
    u8 *entry;
    u8 entry_index;
    s32 entry_kind;

    obj = (Obj *)allocate_flagged_object_node(0);
    if (obj != 0) {
        entry_table = town_map_variants;
        entry_indices = town_map_variant;
        obj->field20 = 0;
        entry_index = entry_indices[obj->field20];
        entry = entry_table + (entry_index << 5);
        entry_kind = (obj->field22 = entry[0]);

        if (entry_kind != 0x21) {
            if (entry_kind >= 0x21) {
                if (entry_kind < 0x29) {
                    if (entry_kind >= 0x26) {
                        obj->handler = &building_resource_update_address;
                        return;
                    }
                }
            }
        } else {
            obj->handler = &D_800B7F8C;
            return;
        }
        obj->handler = &D_800B7E78;
    }
}
