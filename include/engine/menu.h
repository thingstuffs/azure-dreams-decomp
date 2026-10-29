#ifndef ENGINE_MENU_H
#define ENGINE_MENU_H
/* Prototypes of the functions defined in src/engine/menu/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct ObjA464;
struct S_80049F68_Obj;
struct S_8004A4E4;
struct S_8004EEBC_Obj;
struct S_8004F330_Entity;
struct S_8004F684;
struct S_8004F780;
struct S_8004F95C;
struct S_8004F9AC_Obj;
struct S_8004FA2C;
struct S_8004FAA4_1;
struct S_8004FC2C;
struct S_8004FF20;
struct S_800500B4_0;
struct S_800500B4_1;
struct S_800506BC_Ctx;
struct S_800506BC_Obj;
struct S_80053A88_Node;

/* advance_index_with_directional_clamp.c */
s32 advance_index_with_directional_clamp(s32 index, s32 step, s32 count);

/* animate_selection_menu_entry_spacing.c */
void animate_selection_menu_entry_spacing(struct S_8004F9AC_Obj *obj);

/* animate_selection_menu_index_transition.c */
void animate_selection_menu_index_transition(struct S_8004F95C *state);

/* animate_six_entry_selection_cursor.c */
void animate_six_entry_selection_cursor(struct S_800500B4_1 *widgets, struct S_800500B4_0 *anim);

/* apply_scaled_byte_modifier_clamp_one.c */
s32 apply_scaled_byte_modifier_clamp_one(s32 base_value, struct S_8004A4E4 *modifier);

/* begin_selection_menu_index_change.c */
void begin_selection_menu_index_change(struct S_8004FA2C *object, int target);

/* build_menu_line_tile_packets.c */
s32 build_menu_line_tile_packets(struct S_80053A88_Node *first_node);

/* call_state_callback.c */
s32 call_state_callback(struct S_8004FF20 *obj);

/* create_animated_selection_menu.c */
void *create_animated_selection_menu(void *init_data);

/* create_animated_selection_menu_owner.c */
void *create_animated_selection_menu_owner(void *unused, void *source);
/* Registered code-address alias of create_animated_selection_menu_owner. */
void *D_8004F5F4(void *unused, void *source);

/* create_or_reset_seven_entry_menu_backdrop.c */
void *create_or_reset_seven_entry_menu_backdrop(s32 owner, s32 state);

/* destroy_animated_selection_menu_owner.c */
void destroy_animated_selection_menu_owner(void *object);

/* find_resolved_selection_menu_index.c */
s32 find_resolved_selection_menu_index(void *id_list_data, void *object);

/* flag_object_and_release_inner.c */
void flag_object_and_release_inner(struct ObjA464 *obj, s32 unused);

/* handle_animated_selection_menu_cancel.c */
void handle_animated_selection_menu_cancel(void *payload);

/* handle_animated_selection_menu_input.c */
void handle_animated_selection_menu_input(struct S_8004FAA4_1 *menu);

/* handle_object_input.c */
void handle_object_input(void *object);

/* init_paired_packet_records.c */
void *init_paired_packet_records(void *record, void *source);

/* init_sub_record_pair.c */
void func_80049D80(void *record_pair, void *init_data);
void init_sub_record_pair(void *record_pair, void *init_data);

/* initialize_menu_backdrop_display_nodes.c */
void initialize_menu_backdrop_display_nodes(struct S_8004F330_Entity *entity, s32 node_count);

/* initialize_menu_backdrop_layout.c */
void initialize_menu_backdrop_layout(int *object, int initial_value);

/* initialize_seventeen_object_pointers.c */
void initialize_seventeen_object_pointers(s32 *objects, s32 *group_bases);

/* interpolate_selection_menu_entry_coordinates.c */
void interpolate_selection_menu_entry_coordinates(struct S_8004F684 *state);

/* interpolate_selection_menu_entry_shade.c */
void interpolate_selection_menu_entry_shade(struct S_8004F780 *state);

/* lookup_first_mask_value.c */
s32 lookup_first_mask_value(s32 flags);

/* lookup_item_category_mapped_value.c */
s32 lookup_item_category_mapped_value(s32 category_index, s32 record_index);

/* reset_six_object_leaf_records.c */
void reset_six_object_leaf_records(void *slots);

/* reset_six_object_leaf_records_second.c */
void initialize_gauge_menu_display_rows(struct S_800506BC_Obj *obj, struct S_800506BC_Ctx *ctx);

/* run_state_callback_and_restore.c */
s32 run_state_callback_and_restore(void *state);

/* set_object_cleanup_flag.c */
void set_object_cleanup_flag(unsigned short *object_fields);

/* sound_initialize_ordered_elements.c */
void sound_initialize_ordered_elements(struct S_80049F68_Obj *obj);

/* update_animated_selection_menu.c */
void update_animated_selection_menu(struct S_8004FC2C *object);

/* update_menu_backdrop_variant.c */
void update_menu_backdrop_variant(struct S_8004EEBC_Obj *object);

/* Data declarations. */
extern u8 menu_element_order[ 4 ];

#endif
