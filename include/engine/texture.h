#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
/* Prototypes of the functions defined in src/engine/texture/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sprite_frame_state.h"

struct ItemMenuPart;
struct DisplayPositionWords;
void set_menu_part_vectors(struct ItemMenuPart **entries, struct DisplayPositionWords *value, s32 count);

struct S_80047738;
struct S_800478E8_0;
struct S_800485E0_Obj;
struct S_800489F4_Obj;
struct S_80048B8C;
struct S_800491F4;

/* build_reverse_indexed_chain.c */
struct S_800491F4 *build_reverse_indexed_chain(struct S_800491F4 **node_table, u8 *indices, s32 index_limit);

/* clear_marked_slot_entries.c */
void clear_marked_slot_entries(void);

/* flush_sprite_resource_slots.c */
void flush_sprite_resource_slots(void);

/* find_free_sprite_resource_slot.c */
s32 find_free_sprite_resource_slot(void);

/* find_sprite_resource_slot_by_id.c */
s32 find_sprite_resource_slot_by_id(s32 slot_id);

/* set_palette_stp_bits.c */
void set_palette_stp_bits(u16 *entry, s32 groupCount, s32 contiguousMode);

/* mark_sprite_resource_for_purge.c */
void mark_sprite_resource_for_purge(s16 lookup_key);

/* mark_sprite_resources_for_purge.c */
void mark_sprite_resources_for_purge(void);

/* offset_sprite_part_chains.c */
void offset_sprite_part_chains(void *data, s32 flagged_x_offset, s32 y_offset, s32 x_offset);

/* prepare_uncached_sprite_resource.c */
void *prepare_uncached_sprite_resource(s16 entity_index);

/* queue_sprite_resource_in_free_slot.c */
s32 queue_sprite_resource_in_free_slot(s32 value);

/* queue_sprite_resource_slot_reads.c */
void queue_sprite_resource_slot_reads(int slot_index, int value);

/* register_and_upload_sprite_resource.c */
void *register_and_upload_sprite_resource(s32 object_type, void *object);

/* register_sprite_resource.c */
void *register_sprite_resource(s32 type_id, void *entity);

/* relocate_sprite_metadata_pointers.c */
s32 relocate_sprite_metadata_pointers(void *object_addr);

/* retain_sprite_resource_in_cache.c */
s32 retain_sprite_resource_in_cache(s16 slot_id);

/* upload_resource_queue_tiles.c */
void *load_and_publish_texture_resource_pair(int resource_id);
void upload_resource_queue_tiles(u32 unused_state);
void prepare_resource_queue_sprites(void);
void func_80047E30(void);

/* select_indirect_table_entry.c */
void select_indirect_table_entry(void *state_data, s16 table_index, s16 entry_index);

/* texture_build_a_byte_two_color_swapped_pattern_blocks_returns_base.c */
void *build_panel_rectangle_packets(void *cursor, void *pattern_data);

/* texture_handle_expands_six_bit_values_runs_one_four_bytes_until.c */
void expand_six_bit_runs(u8 *source, u8 *output);

/* texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags.c */
void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(struct S_800489F4_Obj *object, s16 animation_index, s16 frame_index, s32 unused_context);

/* texture_mark_unprocessed_type_node_sequences_set_low_six_bits.c */
void stamp_sprite_part_chain_values(struct S_80048B8C *entries);

/* init_slot_end_record.c */
void *init_slot_end_record(struct S_800485E0_Obj *obj, s16 slot_index, s16 base_index, s16 entry_index);

/* texture_set_the_active_entries_matching_id_in_type_table_slots.c */
void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(struct S_800478E8_0 *owner, void *value, s32 entry_id);

/* Data declarations. */
extern void *runtime_texture_resource_handle;

#endif
