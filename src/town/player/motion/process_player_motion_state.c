#include "common.h"
#include "town/player.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"

void register_node_if_unregistered(void *block_data, void *registration_id);
#include "town/player/initialize_record_with_handler_table_api.h"

/* Processes the object, clears its indexed flag, and invokes the next handler. */
void process_player_motion_state(Rec_func_80094268_arg0 *object, s32 forwardedArg1, s32 forwardedArg2) {
    register_node_if_unregistered(object, draw_entry_overlays);
    object_index_slots[object->unk_40].unk_00 = 0;
    initialize_record_with_handler_table((Struct8009B1C8 *)(object), forwardedArg1, forwardedArg2);
}
