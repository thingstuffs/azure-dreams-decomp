#include "common.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */


/*
 * Initializes the scene-list record with the supplied values and sets its mode byte at offset 0x14
 * to 2.
 */
void configure_the_set_mode_n_2(void *record, void *position, void *bounds) {
    TownSceneListNode *node = record;
    handle_insert_initialize_two_values_status_flags(record, position, bounds);
    node->mode = 2;
}
