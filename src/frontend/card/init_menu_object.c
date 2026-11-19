#include "shared/object_node.h"
#include "frontend/card/message_display.h"
#include "common.h"
#include "main/data.h"
#include "frontend/card/message.h"

extern void resolve_apply(void *object);
extern void call_handler_with_zero_if_field_is_zero(void);

/* Initialize the object from its table entry and select its callback. */
void init_menu_object(CardDevDialogDisplay *object) {
    void *callback;
    s32 table_offset;

    card_boot_build_four_layout_command_groups(object->command_buffer, object);
    card_boot_position_four_display_items(object);
    table_offset = object->layout_index * 4;
    object->selection = D_80408ADF[table_offset];
    resolve_apply(object);
    callback = card_boot_handle_menu_actions_and_repeat;
    if (object->mode == 2) {
        callback = call_handler_with_zero_if_field_is_zero;
    }
    NODE_HEADER(object)->update_callback = callback;
}
