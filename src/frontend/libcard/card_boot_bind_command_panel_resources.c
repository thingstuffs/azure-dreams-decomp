#include "common.h"
#include "shared/resident_resources.h"
#include "frontend/libcard/interfaces.h"
#include "records/Rec_func_800233D0_arg0.h"
#include "frontend/libcard.h"
#include "slus.h"

extern u8 menu_leaf_template_6[];

/* Initialize the object's shared references and three data block references. */
void card_boot_bind_command_panel_resources(CardCommandPanelBody *object)
{

    void *shared_data;
    void *primary_table;
    void *secondary_table;
    void *kind_value;
    s32 slot_index;

    kind_value = get_menu_count_template(3);
    slot_index = 0;
    primary_table = cached_selection_row_left_template;
    secondary_table = cached_selection_row_middle_template;
    shared_data = object->highlight_packets;
    object->heading->payload.data = kind_value;
    object->marker->payload.data = menu_leaf_template_6;
    do {
        object->left[slot_index]->payload.data = primary_table;
        object->right[slot_index]->payload.data = secondary_table;
        object->highlight[slot_index]->payload.data = shared_data;
        object->labels[slot_index]->payload.data = object->label_text[slot_index];
        slot_index++;
    } while (slot_index < 3);
}
