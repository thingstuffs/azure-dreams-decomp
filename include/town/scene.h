#ifndef TOWN_SCENE_H
#define TOWN_SCENE_H

#include "common.h"
#include "town/map/variant_data.h"

struct TownObjectSet;


/* select_data_by_cell_code.c */
s32 select_data_by_cell_code(s32 input_a, s32 input_b, s32 input_c, s32 input_d);

/* process_town_records.c */
void process_town_records(u32 records_address, s32 record_count);


/* select_data_for_requested_kind.c */
void *select_data_for_requested_kind(s32 lookup_id, s32 lookup_index, s32 data_kind);

/* dispatch_first_rejected_entry_b.c */
s32 dispatch_first_rejected_entry_b(void);

/* is_next_entry_zero_after_skipping.c */
s32 is_next_entry_zero_after_skipping(s32 list_index);


/* check_progress_against_callback.c */
s32 check_progress_against_callback(void);


/* get_record_value_tier.c */
s32 get_record_value_tier(void);

void *resolve_event_response_key(s32 unused_a, void *unused_b, s32 key);
void *dispatch_event_request(s32 request, void *data, s32 mode);

void *select_first_or_later_use_value(s32 unused_0, s32 unused_1, s32 selector);
void *return_zero_event_value(s32 unused);
extern void *D_800166F8[];
extern void *D_80016718[];

s32 match_request_input_to_state(void *request_value);
s32 process_entry_and_clear_cell_code(struct TownObjectSet *context, s32 entry_index);

s32 apply_scene_override_flag(s32 unused_first, s32 unused_second);
s32 check_any_entry_matches_predicate(void);
void *lookup_variant_with_special_overrides(struct TownObjectSet *lookup_key, s32 unused, s32 entry_id);
s32 consume_required_flag_once(s32 requiredFlag, s32 completionFlag);
void *select_mode_response_marking_paty_new(s32 unused_0, s32 unused_1, s32 request_type);
s32 *select_response_by_town_state_count(s32 first_value, s32 second_value, s32 unused_context);

void reset_sbs11_flags_and_counter(void);
s32 bump_event_counter_to_three(void);

s32 check_counter_threshold(void);
void subtract_threshold_from_counter(void);

void request_handler_state_9(void);
void request_handler_command_17(void);

s32 set_indexed_entry_flag_when_dac_flag_set(struct TownObjectSet *object, s32 entry_index);

s32 process_entry_with_script_flag(struct TownObjectSet *object, s32 entry_index);

/* Map-exit callback invoked by change_map. */
struct MapRuntimeState;
void reserve_town_monster_load_two(struct MapRuntimeState *unused_transition, void *unused_map_data);

/* Complete TOWN callbacks at the validated phase load addresses. */
s32 process_entry_marking_flag_if_nonzero(struct TownObjectSet *object, s32 entry_index);
s32 process_entry_marking_flag_at_five(struct TownObjectSet *object, s32 entry_index);
s32 set_entry_flag_when_enabled(struct TownObjectSet *object, s32 entry_index);
void set_script_flag_sbs32_pad34(void);
void start_keima_and_clear_flag(void);
void set_active_entry_script_flag(void);
void mark_active_entry_script_flag(void);
s32 process_checked_scene_entry(void *object, s32 entry_index);
s32 process_checked_entry_flags(void *object, s32 entry_index);
void set_indexed_scene_entry_flag(void *object, s32 entry_index);
extern u8 D_8001798C[];
extern u8 *D_80017AA4;

s32 process_entry_with_exit_flag(struct TownObjectSet *, s32);

struct SceneActionEntry;
s32 initialize_scene_action_state(struct SceneActionEntry *object, s32 value);
s32 update_scene_and_select_action(struct SceneActionEntry *object, s32 value);

/* Signed scene-position deltas. */
struct S_80019DE0_0;
void apply_signed_stat_deltas(void *stat_deltas);
void apply_half_step_position_deltas(struct S_80019DE0_0 *deltas);
void apply_position_offset_pair(void *offsets);
/* Index-returning flag-table dispatchers. */
s32 call_indexed_callback_failed_test(void);
s32 dispatch_first_failed_entry_b(void);

#include "sdk/libgpu_types.h"
/* The two fixed RAM buffers used by scene image transfers. */
#define SCENE_IMAGE_BUFFER_0 ((u32 *)0x80020000)
#define SCENE_IMAGE_BUFFER_1 ((u32 *)0x80024000)
void store_scene_image_pair(void);

/* Calls the scene service at +0x258 with value one. */
void call_scene_service_one(void);

/* Return the selected scene text, including flag-selected alternatives. */
char *resolve_scene_entry_text(struct TownObjectSet *context, s32 unused, s32 selection);

/* Return the stored state byte as the word consumed by scene tests. */
s32 get_state_record_byte(void);

/* Callback entry points. */
s32 *get_data_pointer_1691_c(void);
struct S_func_80811C54_1;
struct ObjectPosition;
void update_slot_machine(struct S_func_80811C54_1 *self, struct ObjectPosition *position);

/* Square-scene choice records. Consumers index 16-byte entries, call the
 * predicate at +0, call the text selector at +4, and read the flag at +12. */
typedef struct TownObjectSet SquareSceneEntry;
typedef s32 (*TownChoicePredicate)(SquareSceneEntry *, s32);
typedef void *(*TownChoiceText)(SquareSceneEntry *, s32, s32);
/* The choice stores a pointer to a prepared data block or a live scene record. */
typedef void *TownChoiceData;
typedef struct {
    TownChoicePredicate predicate;
    TownChoiceText text;
    TownChoiceData value;
    s16 script_flag;
    s16 reserved;
} TownSceneChoice;

/* One flag-dependency row of an object set (8 bytes): each row names a source flag, a flag to clear and a flag to set
 * when the source is on. process_town_records walks the rows; resolve_entry_flag and apply_entry_position read them
 * by the selector of a position entry. */
typedef struct TownFlagDependency {
    s16 source_flag;
    s16 clear_flag;
    s16 target_flag;
    u8 pad_06[2];
} TownFlagDependency;

/* One 0x1C-byte row of the scene's object-set table. The table is retail data in each scene image; a zero first
 * word ends it. build_object_set_and_select_lists walks it, find_eligible_entry and the choice callbacks receive a
 * row, and save_context_and_dispatch_entry_type indexes it by the root's current entry. */
typedef struct TownObjectSet {
    /* +0x00 is one word: the builder rewrites its low byte, shifts and masks it, and passes it whole to
     * populate_and_dispatch_entry_records. Low byte: the selected choice. Bit 15: hidden from the select lists.
     * Bits 8-13: a 6-bit id copied into the spawn entries. Bits 16-29: the 14-bit key that
     * find_masked_record_and_initialize matches (bit 23 also picks the group bank, bits 24-29 the group). */
    s32 flags;
    /* +0x04 the first spawn entry this row produced; the builder stores it and copies it into the select lists. */
    TownSpawnEntry *object_record;
    /* +0x08 a CD header block {data offset, id}; non-zero means +0x10 is a choice table. */
    s32 *cd_header;
    /* +0x0C the row's data inside the scene image; its offset is written into the CD header at +0x08. */
    s8 *data;
    TownSceneChoice *choices;
    TownFlagDependency *flag_dependencies;
    s16 entry_flag;
    s16 flag_dependency_count;
} TownObjectSet;
s32 apply_entry_mia_bikou_start(SquareSceneEntry *entry, s32 entry_index);
s32 apply_entry_selfy_rescued(SquareSceneEntry *entry, s32 entry_index);
s32 apply_checked_entry_selfy_rescued(SquareSceneEntry *entry, s32 entry_index);
s32 apply_entry_selfy_got_egg(SquareSceneEntry *entry, s32 entry_index);
s32 apply_entry_selfy_all_talk(SquareSceneEntry *entry, s32 entry_index);
void *select_square_entry_or_fallback(SquareSceneEntry *entry, s32 entry_index, s32 selection);
void *select_square_entry_or_alternate(SquareSceneEntry *entry, s32 entry_index, s32 selection);
s32 flag_entry_if_record_eleven(SquareSceneEntry *entry, s32 entry_index);
extern TownSceneChoice square_gate_choices[4];
extern TownSceneChoice square_progress_choices[6];
extern TownSceneChoice square_flag_choices[17];
extern TownSceneChoice square_record_choices[4];


/* A terminal scene choice accepts unconditionally and has an argument-free
 * action. The layout is the ordinary 16-byte scene choice record. */
typedef s32 (*TownTerminalPredicate)(void);
typedef s32 (*TownTerminalAction)(void);
typedef u8 *TownTerminalData;
typedef struct {
    TownTerminalPredicate predicate;
    TownTerminalAction action;
    TownTerminalData value;
    s16 script_flag;
    s16 reserved;
} TownTerminalChoice;

/* Street-event opcode 0x4C callbacks. */
void set_script_flag_db3(void);
void clear_script_flag_db3(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_D_800FE490.h"
struct FallingObjectState;
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void func_800C8D34(struct FallingObjectState *object, ObjectPosition *context, SpriteFrameState *sprite);
struct TownMotionListNode;
struct Box;
void init_secondary_list_record(struct TownMotionListNode *record, ObjectPosition *position, struct Box *bounds);

struct TownMotionListNode *find_overlapping_active_node(struct TownMotionListNode *origin);

s32 count_listed_enabled_records(void);

void advance_event_dispatch_state(void);
s32 advance_to_next_enabled_entry(void);
s32 apply_selected_entry_values(struct TownObjectSet *record, s32 entry_index);
s32 check_callback_record_bytes(s32 expected_second, s32 expected_first);
s32 count_enabled_town_entries(void);
s32 find_first_enabled_entry_id(void);
s32 *get_special_data_for_low_value_id(s32 id);
s32 process_checked_entry(struct TownObjectSet *object, s32 entryIndex);
s32 select_status_code_from_callback(void);

void dispatch_paired_table_values(void);
void process_flagged_goods_entries(void);

struct S_func_8001A854_4;
s32 blend_point_2s_by_signed_weight(void *base_point, void *other_point, s32 blend_weight, s32 other_weight, void *result_point);
void fetch_scene_position_xy(struct S_func_8001A854_4 *output, s32 handler_arg);

void copy_words_backward_from_offset(s32 dest_addr, s32 src_addr, s32 byte_count);

struct S_8001A188_0;
struct S_8001A188_1;
void *build_entry_list(s32 entry_index);
u8 *build_selected_entry_output(s32 selected_index);
s32 build_three_value_block(void);
void init_scene_node_mode_3(void *record, struct ObjectPosition *position, void *bounds);
void copy_town_record_pair_fields(struct S_8001A188_0 *dest, struct S_8001A188_1 *src);
void copy_words(s32 *dst, s32 *src, s32 count);
s32 *find_entry_by_paired_key(s32 *entries, s32 key);
s32 find_entry_index_by_grid_bytes(s32 match_byte_1, s32 match_byte_0);
u8 *get_special_data_by_id(s32 id);
s32 has_matching_entry_result(s32 first_value, s32 second_value);
void invoke_match_callback_or_lookup(void);
s32 *lookup_with_override_fallback(struct TownObjectSet *key, s32 unused, s32 context);
void post_slot_ready_code(s32 group, s32 slot);
u8 *prepare_stored_value_pair(void);
u8 *prepare_stored_value_block(void);
void print_scene_sequence_number_sno(s32 kind);
void process_flagged_entries_after_header(u8 *entries);
void load_record_list_by_mode(s32 table_index, s32 mode);
s32 has_entry_at_grid_position(s32 grid_y, s32 grid_x);

u8 *select_town_response_data(void);

void init_scene_node_mode_1(void *record, struct ObjectPosition *position, void *bounds);

#include "shared/town_object.h"
s32 advance_counter_modulo_eight(void);
void advance_town_events_and_dispatch_entry(void);
s32 apply_record_value_when_enabled(struct TownObjectSet *entry, s32 entry_index);
s32 blit_default_rectangle(void);
s32 is_bar_top_flag_set(void);
void init_scene_node_mode_4(void *record, struct ObjectPosition *position, void *bounds);
void set_dispatch_mode_two(s32 state_input);
s32 find_eligible_entry(void *context, s32 unused_group_bits);
s32 get_linked_record_value(void);
s32 get_min_surface_probe_capped(ObjectPosition *source, s32 *out_detail);
s32 is_angle_within_tolerance(s32 value_a, s32 value_b);
void lookup_entry_after_grid_match(struct TownObjectSet *dispatch_context, s32 unused, s32 dispatch_arg);
s32 apply_entry_and_write_flag_range(struct TownObjectSet *entry, s32 entry_index);
char *select_address_based_input(void);
void *select_data_for_pad82_flag(s32 unused_value, s32 unused_special_value, s32 unused_code);
void *select_data_pointer_based_result(void);
s32 *select_item_gift_response(s32 unused_first_value, s32 unused_second_value, s32 unused_code);
void load_fixed_record_list(s32 unused_list_length, s32 unused_record_value);
struct CardDevSlotDetails;
struct ObjectNodeHeader;
void write_value_through_pointer(struct CardDevSlotDetails *panel, struct ObjectNodeHeader *owner);

void fall_to_ground_height(s32 unused, ObjectPosition *position);

struct Entry;
struct ScenePositionEntry;
void apply_entry_keyed_values(struct ScenePositionEntry *entryTable, struct TownObjectSet *resource, s32 entryKey);
s32 find_entry_index_or_assert(struct Entry *entries, s32 key);
s32 lookup_entry_value_and_set_flag(struct ScenePositionEntry *entries, struct TownObjectSet *context, s32 lookup_key);
void process_flagged_entries_mode_append(void *entries);
s32 *select_fallback_when_below_threshold(void *input);
/* Address-qualified entries of distinct diagnostic devkit builds. */
s32 is_next_entry_zero_after_skipping_80700ce8(s32 list_index);

s32 *select_alternate_data_for_conditions(s32 **out_data);

struct TownInput;
void initialize_falling_object_sprite(struct FallingObjectState *object, ObjectPosition *context, SpriteFrameState *sprite);
s32 match_input_low_bits_to_state(struct TownInput *input);
s32 is_player_in_target_region(void);
s32 find_first_enabled_paired_entry(void);
s32 are_all_checks_set(void);
s32 find_eight_byte_entry_or_assert(struct ScenePositionEntry *entries, s32 entry_id);
void *init_sequential_command_records(void *records);

s32 sum_flagged_terminated_entries(void *entry, s32 callback_mode);
void update_dependent_entry_ids(s16 checked_id, s16 first_id, s16 second_id);

void initialize_circular_list_head(void);
void init_town_motion_list(void);
void pass_pair_table_values(void);
void *populate_and_dispatch_entry_records(void *records, void *entries, s32 flags, s32 tag);
s32 select_first_unmet_table_entry(void);

void remove_scene_runtime_callback(void);

u8 *copy_records_with_control_bits(u8 *dst, u8 *src, s32 control_bits, u8 byte_value);
s32 *prepare_selected_entry_buffer(s32 entryIndex);

#endif
