#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/libcard/save_menu.h"
#include "frontend/card/save_slot.h"
#include "frontend/card/save.h"
#include "shared/object_node.h"

/* The save branch prepares a0 at 0x80405F54. The call arity is unresolved. */
extern s32 get_table_entry_by_flag();


/* Chooses the next card operation and message callbacks from the selected slot header and table result. */
void select_save_slot_callback(void *inputPtr)
{
    CardMenuCallbackPrefix *menu = inputPtr;
    u8 *base;
    ObjectNodeHeader *header;
    s32 index;
    s32 result;

    base = inputPtr;
    index = *(s32 *)(base + 0x28);
    header = NODE_HEADER(base);
    if (card_slot_header_cache[index].fields.marker == 0) {
        result = get_table_entry_by_flag(header);
        /* Keep the header calculation separate from the summary call. */
        header = 0;
        header = NODE_HEADER(base);
        if (result < 3) {
            menu->saved_callback = handle_object_menu_input;
            forward_value_initcardmessageobject_arguments(header);
        } else {
            card_dev_enter_copying_progress(base);
            return;
        }
    } else {
        menu->saved_callback = refresh_save_slot_selection_and_resume_menu_input;
        forward_target_initcardmessageobject(header);
    }
    NODE_HEADER(base)->update_callback = func_80405A64;
}
