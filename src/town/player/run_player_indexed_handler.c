#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/player.h"
#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"


   /* call_arg0 in run_player_indexed_handler */



extern s32 dispatch_selected_entry_if_nonzero();

/* Run the object's indexed handler, clear its table flag, and reset its state. */
void run_player_indexed_handler(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    dispatch_selected_entry_if_nonzero(object->handler_entries[5], object, sprite);
    *(((u8 *)object_index_slots) + (object->unk_40 * 8)) = 0;
    initialize_record_with_handler_table(object, position, sprite);
}
