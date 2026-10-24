#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/texture.h"

/* Runs cleanup, allocates an entity slot, and starts loading it if available. */
void load_and_upload_three_slot_sprite_resource(s16 entity_id) {
    void * entity_slot;

    mark_sprite_resources_for_purge();
    clear_marked_slot_entries();
    entity_slot = prepare_uncached_sprite_resource(entity_id);
    if (entity_slot != 0) {
        drain_cd_command_queue();
        register_and_upload_three_slot_sprite_resource(entity_id, entity_slot);
    }
}
