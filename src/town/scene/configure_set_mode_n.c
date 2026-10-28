#include "common.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F074_arg0.h"



/*
 * Initializes the scene-list record with the supplied values and sets its mode byte at offset 0x14
 * to 1.
 */
void configure_the_set_mode_n_1(void *record, void *position, void *bounds) {
    TownSceneListNode *node = record;
    handle_insert_initialize_two_values_status_flags(record, position, bounds);
    node->mode = 1;
}
