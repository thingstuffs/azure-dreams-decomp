#include "common.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"

extern void clear_entity_record_fields(ObjectPosition *record); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern u8 town_scene_record_handlers[];

extern s8 player_handler_reset_byte[16];

#include "town/player/initialize_record_with_handler_table_api.h"

/* Initialize the record, assign its handler table, and clear the first flag. */
void initialize_record_with_handler_table(void *record_arg, ObjectPosition *position, SpriteFrameState *sprite) {
    Struct8009B1C8 *record = record_arg;

    clear_entity_record_fields(position);
    call_the_handler_selects_nonzero_entry(town_scene_record_handlers, record, (s32)sprite);
    record->unk4 = dispatch_state_callback_by_mode;
    player_handler_reset_byte[0] = 0;
}
