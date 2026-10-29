#ifndef TOWN_MENU_H
#define TOWN_MENU_H

#include "common.h"


/* draw_vram_glyph_text.c */
void draw_vram_glyph_text(u8 *text, s16 start_x, s16 y);


/* draw_cached_catalog_text.c */
void draw_cached_catalog_text(u8 *text, s16 x, s16 y);

void initialize_item_menu_state(u8 *owner, s32 base_value);

struct MenuResourceOwner;
s32 load_menu_display_resource(struct MenuResourceOwner *, s32);

/* Callback entry points. */
void decrement_target_halfword_by_four(void *unused_0, void *unused_1, void *target);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct func_8009F880_S_8009CFE0_0;
s32 classify_object_against_bounds(struct func_8009F880_S_8009CFE0_0 *object, void *position_data);

void initialize_object_transform_and_state(s32 slot_id, void *object, s32 object_id);

void create_indexed_effect_object(s32 index, s32 kind);

struct MenuDisplay;
void func_800B47BC(struct MenuDisplay *object);

#include "records/Rec_func_800B2DA0_arg1.h"
void update_and_finalize_record(Rec_func_800B2DA0_arg1 *record);

#include "records/Rec_func_80021E88_arg1.h"
struct S_800A2A18_1;
s32 test_three_axis_box_overlap(struct S_800A2A18_1 *box, Rec_func_80021E88_arg1 *offset);

void create_entry_builder_controller(void);
s32 *initialize_shared_script_data(void);

#include "records/Rec_D_80082D58.h"
s32 classify_record_by_state_and_position(Rec_D_80082D58 *record, void *position_data);

#include "records/Rec_func_80094268_arg0.h"
struct TownObject;
s32 build_filtered_catalog_glyph(s32 char_code, s32 dst_addr);
void *create_configured_object(void *object_data, void *source_position, s32 alternate_callback);
void draw_catalog_primary_detail(void *entry_state);
void draw_catalog_secondary_detail(void *state);
s16 *get_cached_catalog_glyph(s16 char_code);
void initialize_menu_overlay_objects(u8 *owner, s32 value);
void initialize_randomized_scale_timer(Rec_func_80094268_arg0 *object);
u8 is_catalog_entry_available(s32 index);
void no_op_callback_a(void);
void refresh_catalog_entry_grid(struct TownObject *menu);
void refresh_catalog_primary_detail(struct TownObject *obj);
void reset_catalog_scroll_indicators(void *controller);
s32 store_record_value_and_table_lookup(void);

#endif
