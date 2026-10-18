#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"

extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 append_typed_formatted_value(void *data, s32 buffer);
extern s32 append_entity_display_text(void *record, u8 *out);
extern s32 write_status_prefix_bytes(s32 dst);
extern u8 D_80089000[];
extern u8 D_800E0A1B[];

void display_actor_item_status_message(s32 actor, void *item, s32 buffer_arg2, s32 buffer_arg3) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    adjusted_value = append_typed_formatted_value(item, current_value = get_unused_text_buffer());
    original_value = current_value;
    current_value = adjusted_value;
    func_80099290(write_status_prefix_bytes(expand_text_control_codes(D_80089000,
        append_entity_display_text(actor, expand_text_control_codes(D_800E0A1B, current_value)))));
    display_text_with_fullwidth_adjustment(original_value);
}
