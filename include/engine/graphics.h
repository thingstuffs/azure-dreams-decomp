#ifndef ENGINE_GRAPHICS_H
#define ENGINE_GRAPHICS_H
/* Prototypes of the functions defined in src/engine/graphics/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082A38.h"

struct ItemMenuPart;
void apply_vector_3_template_to_nodes(struct ItemMenuPart **objects, s32 object_count);

struct ObjectPosition;
struct SpriteFrameState;
struct Entry;
struct FrameState;
struct Geometry_80046884;
struct Prim12;
struct RectU16_80046884;
struct S_8003DF0C;
struct S_8003DF74_Vec;
struct S_8003F9E0;
struct S_800475A4_Entry;
struct S_8004761C_Entry;
struct S_80047694;
struct S_80047784;
struct S_800482C8_Entry;
struct S_8004C010;
typedef struct SpriteAttachment {
    /* 0x0 */ u8 flags;   /* bit 0x20 = enabled/active entry, bit 0x80 = last entry */
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} SpriteAttachment; /* size 0xC (12) */
struct S_8004CC38_Node;
struct S_80050550_Outer;
struct S_800505BC;
struct S_800508F0;
struct S_80052C10_Arg1;
struct Tint8004C080;

/* advance_timed_tagged_stream.c */
s32 advance_timed_tagged_stream(struct FrameState *state);

/* apply_block_template_to_nodes.c */
void apply_block_16_template_to_nodes(struct S_8004CC38_Node **nodes, s32 node_count);

/* apply_command_colors.c */
void *apply_command_colors(void *tint0, void *tint1, u8 *packet, void *record, u8 *command, s32 *count);

/* begin_sprite_resource_load_with_completion_flag.c */
void *begin_sprite_resource_load_with_completion_flag(s32 packed_code, s32 *callback_state);

/* build_gouraud_quad_packet.c */
void *build_gouraud_quad_packet(void *tint_a, void *tint_b, void *packet, void *record, void *command);

/* build_screen_outline.c */
void build_screen_outline(struct RectU16_80046884 *rect, struct Geometry_80046884 *geometry, s32 depth);

/* build_sprite_image_read_descriptor.c */
s32 *build_sprite_image_read_descriptor(s16 entry_id, s32 request_arg);

/* build_sprite_metadata_read_descriptor.c */
s32 *build_sprite_metadata_read_descriptor(s16 record_id, s32 packed_value);

/* build_tinted_gradient_rect.c */
void *build_tinted_gradient_rect(u8 *cmd, u8 *rect, u8 *tint);
void *func_800499E8(u8 *cmd, u8 *rect, u8 *tint);

/* clear_alternate_texture_regions.c */
void clear_alternate_texture_regions(s16 use_alt_rect);

/* clear_alternate_texture_regions_second.c */
void load_alternate_sprite_bundle_and_clear_textures(void);

/* clear_graphics_record.c */
void clear_graphics_record(Rec_D_80082A38 *record);

/* convert_hsv_to_rgb.c */
u8 *convert_hsv_to_rgb(u32 hue, s32 saturation, s32 value, u8 *out);

/* copy_processed_vram_tile_backward.c */
s32 copy_processed_vram_tile_backward(s32 tile_index);

/* decompress_lz.c */
u8 *decompress_lz(u8 *src, u8 *dst);
u8 *func_8004068C(u8 *src, u8 *dst);

/* dispatch_registered_draw_callbacks.c */
void dispatch_registered_draw_callbacks(void);

/* draw_double_byte_text.c */
void clear_and_draw_paired_text_rows(s16 row, struct S_80052C10_Arg1 *texts);

/* draw_glyph_row.c */
void draw_glyph_row(s32 x, s32 y, s32 spacing_index, u8 *glyph_codes);

/* draw_linked_sprites.c */
s32 draw_linked_sprites(void *first_payload, struct ObjectPosition *first_coords, struct SpriteFrameState *first_record);

/* draw_linked_sprites_clipped.c */
s32 draw_linked_sprites_clipped(u8 *first_data, s32 link_value, struct SpriteFrameState *value_record);
s32 func_80045C34(u8 *first_data, s32 link_value, struct SpriteFrameState *value_record);

/* draw_shaded_horizontal_line.c */
void draw_shaded_horizontal_line(s16 x, s16 y, s16 width, s16 shade_step);

/* draw_sprite_list.c */
void draw_sprite_list(void);
void func_8003D0F0(void);

/* draw_sprite_parts.c */
void draw_sprite_parts(void *unused, u8 *sprite, s32 ot_depth);

/* draw_tinted_node_sprites.c */
void draw_tinted_node_sprites(u8 *parent, u8 *node);

/* draw_tinted_node_sprites_scratch.c */
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr);
int func_8004CAA0(void *forwarded_ptr, int unused_arg, void *second_ptr);

/* emit_gpu_packets.c */
void *emit_gpu_packets(u32 *ot, u8 *source, u8 **anchor, u8 *entry);

/* fill_primitive_pair.c */
void *fill_primitive_pair(struct S_800508F0 *entry, u8 *template);
void *func_800508F0(struct S_800508F0 *entry, u8 *template);

/* fill_vram_rect.c */
void fill_vram_rect(s16 x, s16 y, s16 width, s16 height, u8 red, u8 green, u8 blue);

/* find_flagged_record_by_id.c */
struct SpriteAttachment *find_flagged_record_by_id(struct SpriteAttachment *entry, u32 target_id);

/* get_glyph_vram_rectangle.c */
void move_glyph_to_grid_position(u8 *image_code, s16 grid_x, s16 grid_y, s32 spacing, s16 base_x, s16 base_y);

/* get_sprite_attachment_vector.c */
struct S_8003DF0C *func_8003DF74(struct S_8003DF0C *table, struct SpriteFrameState *entity, struct S_8003DF74_Vec *out_vec, s16 entry_id);
struct S_8003DF0C *get_sprite_attachment_vector(struct S_8003DF0C *table, struct SpriteFrameState *entity, struct S_8003DF74_Vec *out_vec, s16 entry_id);

/* init_frame_buffers.c */
void init_frame_buffers(void);

/* init_frame_buffers_for_scene.c */
void init_frame_buffers_for_scene(void);

/* init_graphics_state_fields.c */
void func_80034EF8(u8 *state, s32 init_value);
void init_graphics_state_fields(u8 *state, s32 init_value);

/* init_panel_prims.c */
void init_panel_prims(char *object);

/* init_sixteen_packed_templates.c */
void init_sixteen_packed_templates(void);

/* init_tpage_prims.c */
struct Prim12 *init_tpage_prims(struct Prim12 *prim);

/* load_and_upload_sprite_resource.c */
void load_and_upload_sprite_resource(s16 entity_type);

/* load_and_upload_three_slot_sprite_resource.c */
void load_and_upload_three_slot_sprite_resource(s16 entity_id);

/* move_vram_rect.c */
void move_vram_rect(s16 x, s16 y, s16 width, s16 height, s32 move_x, s32 move_y);

/* multiply_rgb_tint_saturated.c */
void * multiply_rgb_tint_saturated(u8 *color, struct S_8004C010 *tint);

/* multiply_rgb_tint_saturated_second.c */
void *build_elliptical_triangle_fan(void *tint_a, void *tint_b, void *primitives, void *color_data, void *style, s32 *out_count, s32 shaded);

/* read_vram_blocks_to_buffer.c */
void read_vram_blocks_to_buffer(void);

/* refresh_vram_blocks_on_flag.c */
void refresh_vram_blocks_on_flag(void *sub_obj);

/* register_sprite_slot.c */
void register_sprite_slot(struct SpriteFrameState *entry, s32 index);

/* reset_callbacks_and_clear_vram.c */
void reset_callbacks_and_clear_vram(void);

/* reset_graphics_state.c */
void reset_graphics_state(void);

/* resource_load_indexed_sprite_bundle.c */
void *resource_load_indexed_sprite_bundle(s32 resource_id);

/* run_cd_image_commands.c */
void func_80041588(u32 *stream_ref, u8 *state, s32 execute);
void run_cd_image_commands(u32 *stream_ref, u8 *state, s32 execute);

/* run_image_load_commands.c */
void func_80041344(s32 data_base, void *scratch);
void run_image_load_commands(s32 data_base, void *scratch);

/* runtime_transform_sprite_attachment_point.c */
void runtime_transform_sprite_attachment_point(void *transform, void *point, void *result);

/* scale_four_points_about_center.c */
void copy_and_scale_screen_outline_points(void);

/* scene_begin_transition_texture_read.c */
void scene_begin_transition_texture_read(unsigned char *task_state);

/* scene_initialize_orbit_motion_sprite.c */
void scene_initialize_orbit_motion_sprite(void *object_ptr, void *slot);

/* scene_load_texture_and_data_pair.c */
void scene_load_texture_and_data_pair(s8 *status);

/* scene_load_variant_texture_set.c */
void scene_load_variant_texture_set(void);

/* select_sprite_entry.c */
void func_80047784(void *object, s16 table_index, s16 entry_index);
void select_sprite_entry(void *object, s16 table_index, s16 entry_index);

/* set_color_components_and_scaled_fields.c */
void set_color_components_and_scaled_fields(struct S_80050550_Outer *outputs, s32 numerator, s32 denominator);

/* set_color_components_and_scaled_fields_second.c */
void advance_gauge_color_then_decay(struct S_800505BC *state, s32 unused_1, s32 unused_2);

/* set_sprite_animation_frame.c */
void set_sprite_animation_frame(struct SpriteFrameState *obj, s16 frame_group, s16 frame_index, s32 slot_index);

/* sprite_projection.c */
s32 func_80045340(void *group_data, s32 context, struct SpriteFrameState *sprite, s32 unused);
s32 project_sprite_chain(void *group_data, s32 context, struct SpriteFrameState *sprite, s32 unused);
void func_800453E0(void *context, void *position, struct Entry *entry, s16 depth_bias);
void project_sprite_commands(void *context, void *position, struct Entry *entry, s16 depth_bias);

/* update_tagged_record_flag.c */
void update_tagged_record_flag_2(u8 *record, s32 set_status_bit);

/* update_vsync_frame_id.c */
s32 func_80044618(s32 id_mode);
s32 update_vsync_frame_id(s32 id_mode);

/* upload_dispatch_entry_vram_rows.c */
void upload_dispatch_entry_vram_rows(u16 entry_index);

/* upload_eligible_entries_by_mode.c */
void upload_eligible_entries_by_mode(struct S_800482C8_Entry *entries, s32 *shared_value);

/* upload_entry_textures.c */
void upload_entry_textures(struct S_80047694 *state);

/* upload_entry_textures_narrow.c */
void upload_entry_textures_narrow(struct S_8004761C_Entry *entries, s32 *source_record_ptr);

/* upload_entry_textures_wide.c */
void upload_entry_textures_wide(struct S_800475A4_Entry *entries, s32 *source_record_ptr);

/* upload_image_blocks.c */
void runtime_upload_image_blocks_vram_offsets_selected_tile_block_indices(s32 image_addr, s32 tile_id, s32 num_blocks);

/* upload_three_color_gradient_palette.c */
void upload_three_color_gradient_palette(s32 palette_slot, u8 *rgb_start, u8 *rgb_mid, u8 *rgb_end, s32 blend_row, s32 semitrans_end);

/* upload_vram_entry_array.c */
void upload_vram_entry_array(struct S_8003F9E0 *entries);

/* upload_vram_row_and_cache.c */
void upload_vram_row_and_cache(s32 src_addr, s32 vram_addr, s32 block_count, s32 skip_flags);

/* Data declarations. */
extern u16 cached_vsync_frame_id;
extern s16 image_block_upload_x;
extern s16 image_block_upload_y;
extern u16 narrow_texture_pack_column_width;
extern u16 narrow_texture_pack_generation;
extern u16 narrow_texture_pack_x;
extern u16 narrow_texture_pack_y;
extern s32 primitive_pair_primary_color;
extern s32 primitive_pair_secondary_color;
extern s32 sprite_command_depth_scale;
extern u16 wide_texture_pack_column_width;
extern u16 wide_texture_pack_generation;
extern u16 wide_texture_pack_x;
extern u16 wide_texture_pack_y;

#endif
