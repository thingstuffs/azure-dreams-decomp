#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "slus.h"

/* Registers two callbacks for event kind 6 using a shared ID. */
void queue_entity_resource_descriptor_pair(s32 first_value, s32 second_value, s16 callback_id) {
    Control_CD(6, build_sprite_metadata_read_descriptor(callback_id, first_value), 0);
    Control_CD(6, build_sprite_image_read_descriptor(callback_id, second_value), 0);
}
