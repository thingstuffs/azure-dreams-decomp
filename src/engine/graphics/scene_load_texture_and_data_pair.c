#include "common.h"

#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

#ifndef NULL
#define NULL 0
#endif

extern u8 scene_texture_data_resource[];
extern s32 gpu_scratch_write_pointer;

/* Runs two callback sequences, resetting their shared status byte before each. */
void scene_load_texture_and_data_pair(s8 *status) {
    *status = 0;
    Control_CD(6, scene_paired_texture_resource, NULL);
    Control_CD(0xFF, set_byte_one, status);
    drain_cd_command_queue();
    run_image_load_commands(0x80020000, gpu_scratch_write_pointer);
    DrawSync(0);
    *status = 0;
    Control_CD(6, scene_texture_data_resource, NULL);
    Control_CD(0xFF, set_byte_one, status);
    drain_cd_command_queue();
}
