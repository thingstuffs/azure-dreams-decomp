#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/texture.h"

/* Initializes an entity by type, running housekeeping first for type 0x38. */
void load_and_upload_sprite_resource(s16 entity_type)
{
    void *entity;

    if (entity_type == 0x38) {
        mark_sprite_resources_for_purge();
        clear_marked_slot_entries();
    }
    entity = prepare_uncached_sprite_resource(entity_type);
    if (entity) {
        drain_cd_command_queue();
        if (entity_type == 0x38) {
            register_and_upload_three_slot_sprite_resource(0x38, entity);
        } else {
            register_and_upload_sprite_resource(entity_type, entity);
        }
    }
}
