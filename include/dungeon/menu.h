#ifndef DUNGEON_MENU_H
#define DUNGEON_MENU_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_801237A4_arg0.h"
void hud_dispatch_no_op(void *object, s32 slot_data);
void advance_wrapped_cycle_index(void);
void apply_record_flags_through_end(void *record, s32 flag_mask);
void build_floating_number_widget(s16 icon, s32 value_a, s32 value_b, s32 style, s16 compact, u16 unused_flags);
void *copy_records_through_end(void *dest, void *src);
void copy_string_to_object_buffer(s8 *object, s32 sourceString);
void draw_cached_catalog_text(u8 *text, s16 start_x, s16 y);
void draw_filler_first_number(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode);
void draw_vram_glyph_text(u8 *text, s16 x, s16 y);
void initialize_menu_object_state(s32 object_addr, s32 initial_value);
void offset_record_coordinates(u8 *record, s32 x_offset, s32 y_offset);
void pass_global_data_with_fixed_args(void);
void queue_black_draw_buffer_rectangle(s32 draw_param);
void draw_nearby_map_markers(void *ordering_table, s32 unused_mode);
void append_adjusted_type_two_entry(s32 x, s32 y, void *color_data, void *submissionTarget);
void retire_menu_object(void *object);
void select_paired_value_tables(Rec_func_801237A4_arg0 *record);
void set_record_byte_flags_through_end(u8 *record, s32 flags);
void set_record_flags_and_negate_x(u8 *record, s32 flags);


void follow_selection_and_blink_sprite(void *motion_state, ObjectPosition *position, SpriteFrameState *draw_state);


void draw_padded_first_number(s32 first, s32 second, u16 width, s16 y, u16 x, s16 mode);

/* Callback entry points. */
s32 build_transformed_sprite_quads(void *draw_area, void *placement, void *sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void build_owned_floating_number_widget(void *owner, s32 value_a, s32 value_b, s32 style, s16 compact, u16 flags);
void *create_panel_effect_object(void *owner);

#endif
