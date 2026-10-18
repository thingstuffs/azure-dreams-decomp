#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void drain_cd_command_queue();                            /* extern */
void clear_marked_slot_entries();                            /* extern */
s32 prepare_uncached_sprite_resource();                             /* extern */
void register_and_upload_three_slot_sprite_resource();                    /* extern */
void mark_sprite_resources_for_purge();                            /* extern */

/* Runs cleanup, allocates an entity slot, and starts loading it if available. */
void load_and_upload_three_slot_sprite_resource(s16 entity_id) {
    s32 entity_slot;

    mark_sprite_resources_for_purge();
    clear_marked_slot_entries();
    entity_slot = prepare_uncached_sprite_resource(entity_id);
    if (entity_slot != 0) {
        drain_cd_command_queue();
        register_and_upload_three_slot_sprite_resource(entity_id, entity_slot);
    }
}
