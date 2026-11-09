#ifndef DUNGEON_MENU_H
#define DUNGEON_MENU_H
struct ItemMenuPart;
struct ObjectNodeHeader;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_801237A4_arg0.h"
/* Body of the type 0x12 viewport transition node: create_inactive_type_twelve_object allocates it, installs
 * update_viewport_transition as its update callback and build_transformed_sprite_quads as its draw callback.
 * The creator copies each x/y and width/height pair from the viewport configuration words at
 * 0x80013630/0x80013634 as one word; the callbacks read and write the halves. */
typedef struct InactiveTypeTwelveObjectBody {
    u8 pad_00[0x4];
    /* 0x04 */ s16 view_x; /* current viewport left, eased toward target_x */
    /* 0x06 */ s16 view_y; /* current viewport top, eased toward target_y */
    /* 0x08 */ s16 view_width; /* current viewport width, eased toward target_width */
    /* 0x0A */ s16 view_height; /* current viewport height, eased toward target_height */
    /* 0x0C */ s16 target_x; /* configured viewport left */
    /* 0x0E */ s16 target_y; /* configured viewport top */
    /* 0x10 */ s16 target_width; /* configured viewport width */
    /* 0x12 */ s16 target_height; /* configured viewport height */
    /* 0x14 */ s16 target_center_x; /* configured sprite center X that the follow state eases toward */
    /* 0x16 */ s16 target_center_y; /* configured sprite center Y that the follow state eases toward */
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 state; /* viewport transition state */
    /* 0x1C */ s16 frames_left; /* frames left in the current easing step or hold */
    /* 0x1E */ s16 target_scale; /* sprite scale that the follow state eases toward; stepped by 0x1000 */
    u8 pad_20[0xC];
    /* 0x2C */ u16 idle_frames; /* frames spent in the reset state without the map view held */
    u8 pad_2E[0x2];
} InactiveTypeTwelveObjectBody;
/* Body of a map marker node: create_transformed_render_object allocates it at a projected map position and installs
 * interpolate_delayed_target_values, which waits, fades the node sprite's color in to color, shrinks the sprite and
 * finally sets floor_flags in dungeon_floor_flags (the floor marker drawers pass visibility bits such as
 * FLOOR_MONSTERS_VISIBLE and FLOOR_ELEVATOR_VISIBLE). */
typedef struct MapMarkerRevealBody {
    /* 0x00 */ SpriteColor color; /* marker color the sprite fades in to */
    u8 pad_04[0x16];
    /* 0x1A */ s16 phase; /* 0 wait, 1 fade in, 2 shrink and finish */
    /* 0x1C */ u16 ticks_left; /* updates left in the current phase */
    u8 pad_1E[0xA];
    /* 0x28 */ s32 floor_flags; /* dungeon_floor_flags bits set when the marker finishes */
    u8 pad_2C[0x2];
    /* 0x2E */ s16 mode; /* zero: the creator sets floor flag 0x40000 and the finished marker clears it */
} MapMarkerRevealBody;
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
void interpolate_delayed_target_values(MapMarkerRevealBody *state, ObjectPosition *unused, SpriteFrameState *sprite);
s32 build_transformed_sprite_quads(InactiveTypeTwelveObjectBody *draw_area, ObjectPosition *placement, SpriteFrameState *sprite);

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

s32 create_map_position_object(s32 world_x, s32 world_z);

#endif
