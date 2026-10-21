#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus/data.h"

extern void Control_CD(s32, void *, void *);
extern void set_byte_one(void);

extern s32 gpu_scratch_write_pointer;
extern u8 town_map_variants[][32];
extern u8 town_map_variant;

/* Loads shared and variant-specific resources, then processes the selected table entry. */
void scene_load_variant_texture_set(void)
{
    u8 load_status;
    u8 *resource;
    s32 command;

    load_status = 0;
    Control_CD(6, scene_common_texture_resource_0, 0);
    Control_CD(0xFF, set_byte_one, &load_status);
    drain_cd_command_queue();
    run_image_load_commands((void *)0x80020000, gpu_scratch_write_pointer);
    DrawSync(0);
    load_status = 0;
    Control_CD(6, scene_common_texture_resource_1, 0);
    Control_CD(0xFF, set_byte_one, &load_status);
    drain_cd_command_queue();
    run_image_load_commands((void *)0x80020000, gpu_scratch_write_pointer);
    DrawSync(0);
    load_status = 0;
    Control_CD(6, scene_common_texture_resource_2, 0);
    Control_CD(0xFF, set_byte_one, &load_status);
    drain_cd_command_queue();
    run_image_load_commands((void *)0x80020000, gpu_scratch_write_pointer);
    DrawSync(0);
    load_status = 0;
    Control_CD(6, scene_common_texture_resource_3, 0);
    Control_CD(0xFF, set_byte_one, &load_status);
    drain_cd_command_queue();
    run_image_load_commands((void *)0x80020000, gpu_scratch_write_pointer);
    DrawSync(0);
    load_status = 0;

    switch (town_map_variant) {
    case 0:
    case 1:
    default:
        switch (D_800136B8) {
        default:
            command = 6;
            resource = scene_variant_texture_resource_0;
            break;
        case 11:
            command = 6;
            resource = scene_variant_texture_resource_1;
            break;
        case 12:
            command = 6;
            resource = scene_variant_texture_resource_2;
            break;
        case 13:
            command = 6;
            resource = scene_variant_texture_resource_3;
            break;
        }
        break;
    case 2:
        command = 6;
        resource = scene_variant_texture_resource_4;
        break;
    case 3:
        switch (D_800136B8) {
        default:
            command = 6;
            resource = scene_variant_texture_resource_5;
            break;
        case 11:
            command = 6;
            resource = scene_variant_texture_resource_6;
            break;
        case 12:
            command = 6;
            resource = scene_variant_texture_resource_7;
            break;
        case 13:
            command = 6;
            resource = scene_variant_texture_resource_8;
            break;
        }
        break;
    }

    Control_CD(command, resource, 0);
    Control_CD(0xFF, set_byte_one, &load_status);
    drain_cd_command_queue();
    run_image_load_commands((void *)0x80020000, gpu_scratch_write_pointer);
    DrawSync(0);
    runtime_load_packed_resource_chunks(town_map_variants[town_map_variant][0], D_8012F004);
}
