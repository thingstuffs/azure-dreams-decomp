#ifndef ENGINE_RESOURCE_H
#define ENGINE_RESOURCE_H
/* Prototypes of the functions defined in src/engine/resource/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "shared/runtime_dispatch.h"

struct S_8003C0A4_1;
struct S_80040490_RECT;

/* activate_scene_resource_and_clear_view_callbacks.c */
void activate_scene_resource_and_clear_view_callbacks(void);

/* alloc_gpu_scratch_ring.c */
void *alloc_gpu_scratch_ring(s32 size);

/* cd_resource_queue.c */
void *create_callback_pair_default(int value);
void *func_8004B404(int value);
void *queue_cd_resource(s32 id);

/* clear_flags_on_resource_list.c */
void clear_flags_on_resource_list(void);

/* decode_and_upload_image.c */
s32 decode_and_upload_image(u8 *compressed_image, struct S_80040490_RECT *rect);

/* decode_or_copy_resource_pixels.c */
u8 *decode_or_copy_resource_pixels(u8 *src_start, u8 *dst_start);

/* entry_advance_timed_entity_motion.c */
void compose_and_install_camera_transform(void);

/* entry_file_load_com.c */
void mark_object_removal_for_inner_release(unsigned short *object);
void adjust_resource_decode_buffer_capacity(int amount);
void load_scene_texture_resource(void);
void flag_object_for_removal(unsigned short *object);

/* entry_scene_begin_transition_data_read.c */
void load_transition_image_and_begin_data_read(void *state);

/* entry_sd_call.c */
void request_scene_dispatch_state(s16 requested_state);

/* entry_set_scene_phase_callback.c */
void begin_scene_dispatch_resource_loading(void);

/* find_sentinel_table_value.c */
s32 lookup_sentinel_resource_value_or_zero(s32 lookup_key);

/* has_table_entry.c */
s32 has_table_entry(s32 unused, s32 entry_index);

/* konami_runtime_gp_count.c */
void bind_and_load_indexed_resource_record(void *data, s32 entry_index);

/* load_dispatch_entry_files.c */
void load_dispatch_entry_files(u16 entry_index);

/* move_entry_to_front.c */
s32 activate_indexed_resource_and_upload_images(s32 entry_group, s32 entry_index);

/* reserve_gpu_scratch_tail.c */
s32 reserve_gpu_scratch_tail(s32 byte_count);

/* run_dispatch_entry_callbacks.c */
s32 run_dispatch_entry_callbacks(u16 entry_id);

/* run_runtime_callbacks.c */
void run_runtime_callbacks(void);

/* runtime_clear_record_field.c */
void runtime_clear_record_field_04(Rec_D_80082D58 *record);

/* runtime_copy_three_global_blocks.c */
void runtime_copy_three_global_blocks(void);

/* runtime_estimate_vector_length.c */
s32 runtime_estimate_vector_length(s32 x, s32 y);

/* runtime_find_sentinel_table_value.c */
u32 runtime_find_sentinel_table_value(s32 value);

/* runtime_get_mode_indexed_value.c */
u32 runtime_get_mode_indexed_value(s32 index);

/* runtime_move_entry_to_front.c */
void runtime_move_entry_to_front(s32 index);

/* runtime_scale_four_points_about_center.c */
void runtime_scale_four_points_about_center(s16 *points, s32 scale_num, s32 scale_den);

/* runtime_set_destination_flag_from_source.c */
void runtime_set_destination_flag_from_source(struct S_8003C0A4_1 *dest, RuntimeSourceValueView *source);

/* Data declarations. */
extern void *runtime_resource_load_target;

#endif
