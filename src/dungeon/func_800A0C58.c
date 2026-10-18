#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"
#include "m2c_compat.h"

s32 expand_text_control_codes();                  /* extern */
s32 append_typed_formatted_value();                    /* extern */
s32 append_entity_display_text();                        /* extern */
s32 write_status_prefix_bytes();                             /* extern */
extern u8 D_80089000[];
extern M2C_UNK D_800E0A03[];
extern M2C_UNK D_800E0A12[];

/* Builds and displays an item message with the selected phrase and entity name. */
void display_item_status_message(s32 entity, s32 item, s32 message_kind, s32 buffer_arg) {
    s32 message;

    s32 text_end;

    message = get_unused_text_buffer(entity, item, message_kind, buffer_arg);
    if ((s16)message_kind == 0x15) {
        text_end = expand_text_control_codes(D_800E0A03, append_typed_formatted_value(item, message));
    } else {
        text_end = expand_text_control_codes(D_800E0A12, append_typed_formatted_value(item, message));
    }
    func_80099290(write_status_prefix_bytes(expand_text_control_codes(&D_80089000, append_entity_display_text(entity, text_end))));
    display_text_with_fullwidth_adjustment(message);
}
