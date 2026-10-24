#include "common.h"
#include "town/player/action_initializers.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_deferred_dispatch_address;
/* Stores the address of D_800933FC in the output pointer. */
void set_item_selection_data_pointer(void *object, void *unused_position, void *unused_context) {
    s32 **out_ptr = object;

    *out_ptr = &scene_deferred_dispatch_address;
}
