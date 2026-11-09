#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "records/Rec_func_800233D0_arg0.h"
#include "frontend/libcard.h"
#include "slus.h"

extern u8 menu_leaf_template_6[];
extern u8 D_80077EF0[];
extern u8 D_80077EFC[];

/* Initialize the object's shared references and three data block references. */
void card_boot_bind_command_panel_resources(CardCommandPanelBody *object)
{

    void *shared_data;
    void *primary_table;
    void *secondary_table;
    void *kind_value;
    s32 slot_index;
    s32 block_offset;

    kind_value = get_menu_count_template(3);
    slot_index = 0;
    primary_table = D_80077EF0;
    secondary_table = D_80077EFC;
    shared_data = (u8 *)object + 4;
    block_offset = 0x90;
    object->heading->payload.data = kind_value;
    object->marker->payload.data = menu_leaf_template_6;
    do {
        object->left[slot_index]->payload.data = primary_table;
        object->right[slot_index]->payload.data = secondary_table;
        object->highlight[slot_index]->payload.data = shared_data;
        object->labels[slot_index]->payload.data = (u8 *)object + block_offset;
        block_offset += 0x48;
        slot_index++;
    } while (slot_index < 3);
}
