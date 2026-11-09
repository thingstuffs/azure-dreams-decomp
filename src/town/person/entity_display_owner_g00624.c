/* Entity display owner (G00624). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B678C, CL:town/func_800B6858, CL:town/func_800B6980, CL:town/func_800B6A28, CL:town/func_800B6BF0, CL:town/func_800B6C88, CL:town/func_800B6D34. */
#include "town/person/entity_display_owner_g00624.h"
#include "town/person.h"
#include "shared/object_node.h"
#include "shared/item_menu.h"
#include "town/shop_callbacks_api.h"

/* Initializes two child entries with data addresses and coordinate offsets. */
void initialize_dual_child_entries(StorageMenuObject *owner) {
    owner->parts[30]->handler = owner->data + 0x48;
    owner->parts[30]->position->x = -0x20;
    owner->parts[30]->position->y = -0x18;
    owner->parts[31]->handler = owner->data + 0x90;
    owner->parts[31]->position->x = -0x70;
    owner->parts[31]->position->y = -0x18;
}

/* Processes three data blocks and five table entries for the object. */
void initialize_object_data_blocks_and_entries(StorageMenuObject *object) {
    EntityDisplayLayout *entry_data;
    s32 entry_index;

    entry_index = 0;
    copy_contiguous_display_blocks(object->data);
    copy_display_template_blocks(object->data + 0x48);
    func_800B426C(object->data + 0x90);
    upload_three_color_gradient_palette(0x10, &entity_display_gradient_color, &entity_display_gradient_color, &entity_display_gradient_color, 0, 0xA);
    entry_data = D_800D1658;
    do {
        update_four_slot_element_values_and_positions(object, entry_data, entry_index);
        entry_index += 1;
        entry_data += 1;
    } while (entry_index < 5);
    initialize_dual_child_entries(object);
}

/* Sets the record's base value, offset value, and data pointer. */
void set_record_base_and_data_pointer_alt(void *record_values, s32 base_value) {
    StorageMenuObject *object = record_values;

    object->unk_04 = base_value;
    object->unk_00 = (s32)(base_value + 0x20);
    NODE_HEADER(record_values)->update_callback = update_subobject_and_normalize_color;
}

/*
 * Sets the record base and data pointer, binds three embedded display parts, and initializes the
 * owner data blocks and entries.
 */
void initialize_entity_display_owner(u8 *owner, s32 base_value) {
    set_record_base_and_data_pointer_alt(owner, base_value);
    initialize_entity_display_parts(owner + 0x4C, owner + 0x24, owner + 0x34);
    initialize_object_data_blocks_and_entries((struct StorageMenuObject *)(owner));
}
