#include "common.h"

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 DrawSync(s32);
extern s32 Control_CD();
extern s32 drain_cd_command_queue(void);
extern s32 run_image_load_commands();
extern u8 scene_texture_data_resource[];
extern u8 scene_paired_texture_resource[];
extern s32 gpu_scratch_write_pointer;
extern void set_byte_one();

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
