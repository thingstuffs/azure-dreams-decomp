/* Texture resource loading, image-tile uploads and sprite metadata relocation. */
#include "slus/gp_shared_8152c.h"
#include "engine/cd.h"
#include "engine/texture.h"



/* Loads paired resource buffers from CD, uploads their image tiles, and returns the texture-handle slot. */
void *load_and_publish_texture_resource_pair(int resource_id)
{
    queue_entity_resource_descriptor_pair(&resource_queue_input_buffer, &resource_queue_image_buffer, (unsigned short)resource_id);
    drain_cd_command_queue();
    runtime_texture_resource_handle = func_80047AB0(&resource_queue_input_buffer, 0xB, 0x7900, 0xD, &resource_queue_image_buffer);
    return &runtime_texture_resource_handle;
}

/* Uploads image tiles from the fixed resource buffers and publishes the texture handle. */
void upload_resource_queue_tiles(u32 unused_state)
{
    runtime_texture_resource_handle = upload_image_tiles(&resource_queue_input_buffer, 0xB, 0x7900, 0xD, &resource_queue_image_buffer);
}

/* Relocates sprite metadata, patches texture and palette IDs, and publishes the fixed resource buffer. */
void prepare_resource_queue_sprites(void)
{
    relocate_sprite_metadata_pointers(&resource_queue_input_buffer);
    offset_sprite_part_chains(&resource_queue_input_buffer, 0xB, 0x7900, 0xD);
    runtime_texture_resource_handle = &resource_queue_input_buffer;
}
void *runtime_texture_resource_handle = 0;
