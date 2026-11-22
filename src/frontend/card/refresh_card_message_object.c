#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

#include "frontend/card/message_display.h"
extern s32 card_ui_dirty_flags[3];
extern s32 D_8008DAB4_2[];

/* Processes the global state, optionally flags its linked object, and returns the state value. */
s32 refresh_card_message_object(s32 flag_linked_object) {
    ObjectNodeHeader *linked_object;
    CardDevDialogDisplay *state_data = NODE_BODY(card_message_object);

    if (func_80047FD8(NODE_HEADER(state_data)) != 0) {
        if (flag_linked_object != 0) {
            linked_object = state_data->owner;
            linked_object->flags |= 0x2000;
        }
        process_four_referenced_values(state_data);
        NODE_HEADER(state_data)->flags = (u16) (NODE_HEADER(state_data)->flags | 0x8000);
        D_8008DAB4_2[0] = card_ui_dirty_flags[0] | 0x8000;
    }
    return state_data->selection;
}
