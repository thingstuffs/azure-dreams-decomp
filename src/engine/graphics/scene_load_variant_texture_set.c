#include "common.h"

extern void DrawSync(s32);
extern void Control_CD(s32, void *, void *);
extern void drain_cd_command_queue(void);
extern void run_image_load_commands(void *, s32);
extern void runtime_load_packed_resource_chunks(u8, void *);
extern void set_byte_one(void);

extern u8 D_800136B8;
extern u8 scene_common_texture_resource_0[8];
extern u8 scene_common_texture_resource_1[8];
extern u8 scene_common_texture_resource_2[8];
extern u8 scene_common_texture_resource_3[8];
extern u8 scene_variant_texture_resource_0[8];
extern u8 scene_variant_texture_resource_1[8];
extern u8 scene_variant_texture_resource_2[8];
extern u8 scene_variant_texture_resource_3[8];
extern u8 scene_variant_texture_resource_4[8];
extern u8 scene_variant_texture_resource_5[8];
extern u8 scene_variant_texture_resource_6[8];
extern u8 scene_variant_texture_resource_7[8];
extern u8 scene_variant_texture_resource_8[8];
extern s32 gpu_scratch_write_pointer;
extern u8 D_800D2FB4[][32];
extern u8 D_800D381A;
extern u8 D_8012F004[];

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

    switch (D_800D381A) {
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
    runtime_load_packed_resource_chunks(D_800D2FB4[D_800D381A][0], D_8012F004);
}
