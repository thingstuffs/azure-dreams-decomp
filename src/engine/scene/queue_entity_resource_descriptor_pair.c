#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "slus.h"

/* Queue the sprite metadata read and the sprite image read for one resource ID. */
void queue_entity_resource_descriptor_pair(s32 first_value, s32 second_value, s16 callback_id) {
    Control_CD(6, build_sprite_metadata_read_descriptor(callback_id, first_value), 0);
    Control_CD(6, build_sprite_image_read_descriptor(callback_id, second_value), 0);
}
