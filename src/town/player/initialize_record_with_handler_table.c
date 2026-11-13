#include "common.h"
#include "town/player.h"
#include "town/player/handler_reset_data.h"
#include "shared/sprite_frame_state.h"

extern void dispatch_selected_entry_if_nonzero(void *entries, void *record, s32 handler_param);
extern u8 town_scene_record_handlers[];

#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/player/object.h"

/* Initialize the record, assign its handler table, and clear the first flag. */
void initialize_record_with_handler_table(void *record_arg, ObjectPosition *position, SpriteFrameState *sprite) {
    Struct8009B1C8 *record = record_arg;

    clear_entity_record_fields(position);
    dispatch_selected_entry_if_nonzero(town_scene_record_handlers, record, (s32)sprite);
    record->unk4 = dispatch_state_callback_by_mode;
    player_handler_reset_byte = 0;
}
