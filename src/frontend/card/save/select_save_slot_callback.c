#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/libcard/save_menu.h"
#include "frontend/card/save_slot.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "shared/object_node.h"

extern s32 get_table_entry_by_flag();


/* Chooses the next card operation and message callbacks from the selected slot header and table result. */
void select_save_slot_callback(CardSaveOperationBody *base)
{
    ObjectNodeHeader *node;
    s32 index;
    s32 result;

    index = base->entry_index;
    node = NODE_HEADER(base);
    if (card_slot_header_cache[index].fields.marker == 0) {
        result = get_table_entry_by_flag(node);
        node = 0;
        node = NODE_HEADER(base);
        if (result < 3) {
            base->completion_callback = handle_object_menu_input;
            forward_value_initcardmessageobject_arguments(node);
        } else {
            card_dev_enter_copying_progress(base);
            return;
        }
    } else {
        base->completion_callback = refresh_save_slot_selection_and_resume_menu_input;
        forward_target_initcardmessageobject(node);
    }
    NODE_HEADER(base)->update_callback = func_80405A64;
}
