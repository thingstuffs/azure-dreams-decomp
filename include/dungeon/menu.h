#ifndef DUNGEON_MENU_H
#define DUNGEON_MENU_H
struct ItemMenuPart;
struct ObjectNodeHeader;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_801237A4_arg0.h"
typedef struct InactiveTypeTwelveObjectBody {
    u8 pad_00[0x4];
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_04;
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_08;
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_0C;
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_10;
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_14;
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_18;
    union {
        s32 word;
        struct { union { s16 s; u16 u; } low; union { s16 s; u16 u; } high; } halves;
    } unk_1C;
    u8 pad_20[0xC];
    u16 unk_2C;
    u8 pad_2E[0x2];
} InactiveTypeTwelveObjectBody;
void hud_dispatch_no_op(void *object, struct ItemMenuPart *slot_data);
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
void copy_menu_vram_block(void);
void queue_black_draw_buffer_rectangle(InactiveTypeTwelveObjectBody *object);
void draw_nearby_map_markers(void *ordering_table, InactiveTypeTwelveObjectBody *unused_object);
void append_map_dot_tile(s32 x, s32 y, void *color_data, void *submissionTarget);
void retire_menu_object(void *object);
void select_paired_value_tables(Rec_func_801237A4_arg0 *record);
void set_record_byte_flags_through_end(u8 *record, s32 flags);
void set_record_flags_and_negate_x(u8 *record, s32 flags);


void follow_selection_and_blink_sprite(void *motion_state, ObjectPosition *position, SpriteFrameState *draw_state);


void draw_padded_first_number(s32 first, s32 second, u16 width, s16 y, u16 x, s16 mode);

/* Callback entry points. */
s32 build_transformed_sprite_quads(InactiveTypeTwelveObjectBody *draw_area, ObjectPosition *placement, void *sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void build_owned_floating_number_widget(void *owner, s32 value_a, s32 value_b, s32 style, s16 compact, u16 flags);
void *create_panel_effect_object(ActorRecord *owner);

void *allocate_initialized_child_object(struct ObjectNodeHeader *parent_object, s32 type_code, s32 config_value);
void *create_menu_child_object(s32 parent_obj, s32 descriptor_value);
s8 *find_first_ended_record(s8 *record);
void *get_mapped_menu_table_entry(s32 row_id, s32 entry_index);
void wrap_position_and_set_state_value(s32 state_value);

void copy_cached_hud_rectangle_to_fixed_position(void);
void draw_blue_enabled_entry_markers(void);
void draw_green_type_two_markers(void);
void draw_purple_entry_markers(void);
void draw_red_active_entry_markers(void);
s32 get_masked_grid_nibble(s16 x, s16 y);
void redraw_type_three_floor_markers(void);
void set_scaled_value_and_complement(void *record, s32 input_value);
void submit_activation_command(void);

#endif
