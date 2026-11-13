#include "common.h"
#include "town/player/state_update_g00548.h"
#include "shared/town_handler.h"
#include "town/player.h"

extern s32 scene_fallback_request_address;

/* Initialize the record and set its first pointer to D_80093638. */
void initialize_scene_record(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &town_scene_record_handlers, (TownObjectRecord *) record, ptr2);
    *record = &scene_fallback_request_address;
}
