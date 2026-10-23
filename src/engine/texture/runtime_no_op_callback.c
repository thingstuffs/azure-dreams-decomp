/* Texture resource loading, image-tile uploads and sprite metadata relocation. */
#include "slus/gp_shared_8152c.h"



/* Loads paired resource buffers from CD, uploads their image tiles, and returns the texture-handle slot. */
void *load_and_publish_texture_resource_pair(int resource_id)
{
    queue_entity_resource_descriptor_pair(&resource_queue_input_buffer, &D_80023000, (unsigned short)resource_id);
    drain_cd_command_queue();
    runtime_texture_resource_handle = func_80047AB0(&resource_queue_input_buffer, 0xB, 0x7900, 0xD, &D_80023000);
    return &runtime_texture_resource_handle;
}

/* Uploads image tiles from the fixed resource buffers and publishes the texture handle. */
void runtime_no_op_callback(void)
{
    runtime_texture_resource_handle = upload_image_tiles(&resource_queue_input_buffer, 0xB, 0x7900, 0xD, &D_80023000);
}

/* Relocates sprite metadata, patches texture and palette IDs, and publishes the fixed resource buffer. */
void advance_effect_state(void)
{
    relocate_sprite_metadata_pointers(&resource_queue_input_buffer);
    patch_sprite_packet_texture_and_palette_ids(&resource_queue_input_buffer, 0xB, 0x7900, 0xD);
    runtime_texture_resource_handle = &resource_queue_input_buffer;
}
void *runtime_texture_resource_handle = 0;
