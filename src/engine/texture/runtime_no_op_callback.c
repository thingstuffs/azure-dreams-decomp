#include "slus/gp_shared_8152c.h"



void *load_and_publish_texture_resource_pair(int resource_id)
{
    queue_entity_resource_descriptor_pair(&D_80016000, &D_80023000, (unsigned short)resource_id);
    drain_cd_command_queue();
    runtime_texture_resource_handle = func_80047AB0(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
    return &runtime_texture_resource_handle;
}

void runtime_no_op_callback(void)
{
    runtime_texture_resource_handle = upload_image_tiles(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
}

void advance_effect_state(void)
{
    relocate_sprite_metadata_pointers(&D_80016000);
    patch_sprite_packet_texture_and_palette_ids(&D_80016000, 0xB, 0x7900, 0xD);
    runtime_texture_resource_handle = &D_80016000;
}
void *runtime_texture_resource_handle = 0;
