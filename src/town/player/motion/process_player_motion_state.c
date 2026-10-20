#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"



void register_node_if_unregistered(void *block_data, s32 registration_id);
extern void initialize_record_with_handler_table();
extern u8 D_800970FC[];


/* Processes the object, clears its indexed flag, and invokes the next handler. */
void process_player_motion_state(Rec_func_80094268_arg0 *object, s32 forwardedArg1, s32 forwardedArg2) {
    register_node_if_unregistered(object, &D_800970FC);
    D_80082660[object->unk_40].unk_00 = 0;
    initialize_record_with_handler_table(object, forwardedArg1, forwardedArg2);
}
