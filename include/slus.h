#ifndef SLUS_H
#define SLUS_H

struct ObjectNodeHeader;
/* Prototypes of the functions defined in src/slus/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sound_volume.h"

struct ObjectPosition;
struct SpriteFrameState;
struct Dst;
struct Elem;
struct RuntimeContext;
struct S8004CBFC_a0;
struct S8004CBFC_a1;
struct S_8004EFF4;
struct S_80050E20;
struct Struct_C_next;
struct VtableObj;

/* code.c */
void initialize_memory_card_services(s32 enable_pad);
void zero_words(int *dst, int count);
void copy_words_forward(int *dst, int *src, int count);
void select_record_entry_and_value(void *state, void *entries, short index);
void swap_int_values(int *left, int *right);
void set_byte_one(unsigned char *flag);
int identity_int(int value);
int *read_sound_stream_cue_pointer(void);
int read_sound_payload_slot(void);
void set_sound_payload_slot(int value);
void wait_512_vertical_syncs(void);
void pack_tagged_resource_descriptor(int tag, int id, int *record, int value);
void push_node_onto_free_list(struct ObjectNodeHeader *node);
void mark_resource_list_flags_ten_and_eleven(void);
int count_null_terminated_pointers(void **entries);
void append_terminated_runtime_word(int value);
short get_bounded_stride_index(unsigned int value, unsigned int base, unsigned short stride, unsigned short limit);
void apply_actor_template_and_class(void *entity, int value, void *source);
void set_cd_cue_and_submit_sound_command(int first, int second, int third, int fourth);
int read_stream_cue_start_offset(void);
int draw_linked_lit_meshes(void *object, int value, void *record);
short draw_linked_sprites_and_narrow_result(void *payload, struct ObjectPosition *coords, struct SpriteFrameState *record);
void advance_sprite_animation_and_textures(void *entity);
void clear_sprite_work_table(void);
void *get_sprite_resource_slot_buffer(s32 index);
int get_image_palette_address(int value);
s32 get_resource_block_index_from_address(void *address);
void load_default_object_palette(short index);
int load_equipment_palette_for_category_sixteen(short index);
void load_equipment_change_palette(short index);
int load_dungeon_sprite_bundle(void);
int load_town_sprite_bundle(void);
int load_alternate_town_sprite_bundle(void);
int read_display_spacing_word(int index);
unsigned char read_display_spacing_byte(int index);
s32 count_nonzero_word_prefix(s32 *entries, s32 limit);
void append_linked_chain(struct Struct_C_next *tail, struct Struct_C_next *node);
int is_type_twenty(int type);
int get_item_name_with_shared_text_table(void *object);
int read_item_category_flag_ten(void *item);
int get_low_flag_priority(int flags);
int set_flag_and_return_success(int *flag);
void initialize_packet_pair_from_record(void *packets, void *record);
int advance_index_with_single_wrap(int index, int delta, int limit);
#include "slus/menu_count_template.h"
int read_second_argument_scaled_byte(void *unused, void *object);
s32 func_8004A618(void *item);
s32 get_item_sell_money(void *item);
s32 func_8004A638(void *item);
s32 get_item_buy_money(void *item);
void clear_floor_resource_state_table(void);
int subtract_pointed_int_values(int *left, int *right);
s32 count_pointer_list_entries(void **entries);
int compare_mapped_leading_bytes(unsigned char **left, unsigned char **right);
void forward_selection_sort_request(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *));
void create_single_callback_payload(void *object);
struct ObjectNodeHeader *find_active_list_node(struct ObjectNodeHeader *target);
void submit_global_cd_command_six(void);
void load_bin_nametwin(void);
int create_item_view_without_event(int object, int value);
void initialize_scaled_entry_cursor(struct S8004CBFC_a0 *state, struct S8004CBFC_a1 *entry, int *cursor);
void *advance_packed_record_by_type(void *object);
void decode_glyph_id_to_byte_rectangle(u32 value, u8 *record);
void set_descriptor_grid_byte_coordinates(signed char *record, int width, int height, int column, int row);
void set_message_mode(int value);
void clear_message_command_words(void);
void clear_resident_bitmap_bit_two(void);
void set_glyph_style_index(void *record, int index);
unsigned char *read_decimal_digit_value(unsigned char *text, int *digit);
void format_reversed_decimal_space_padded(int value, unsigned short width, char *buf);
void noop_release_notification(void);
void flag_optional_object_for_removal(void *object);
void flag_optional_object_for_removal_b(void *object);
void noop_display_setup_hook(void);
void clear_vram_callback_state(void);

#include "slus/resource_transition_task.h"
void build_menu_backdrop_display_buffers(void *object);
void link_menu_backdrop_display_nodes(void *entries);
void set_menu_backdrop_initial_value(int *dst, int value);
void noop_selection_menu_animation_idle(void);
int read_selected_menu_entry_word(char *object);
void resolve_selected_menu_entry(char *object);
void forward_object_input_handler(void *object);
void invoke_leading_object_callback(struct VtableObj *object, void *position, void *sprite);
void link_seventeen_indexed_entries(void *entries);
void submit_enabled_saved_display_value(void);
void run_town_movie_callbacks(void);
void run_town_transition_callbacks(void);
void load_direct_resource_descriptor(void);
void submit_cd_command_six_and_drain(void *record);
short SD_Call(int flags);
void sound_set_cd_playback_volume_scale(short value);
void sound_set_voice_gain_scale(short value);
int func_800542A4(void);
int select_audio_mode_attenuation(int mode);
void func_800555FC(void);
void func_80055604(void);
void stop_matching_effect_voices(s32 packed_key, s32 packed_channel);
void clear_audio_command_queue(void);
void initialize_audio_ramp_defaults(SoundTask *state);
void func_80055CEC(void);
void func_80055E6C(void);
void noop_voice_start_notification(void);
void noop_channel_control_notification(void);
void func_80056D3C(void);
void noop_midi_a0(void);
void noop_midi_d0(void);
void tick_enabled_sequence_tracks(void);
void func_800587F8(void);
unsigned int pack_big_endian_word(int byte_3, int byte_2, int byte_1, int byte_0);
int pack_big_endian_halfword(int high, int low);
int add_to_sequence_counter(int *counter, int delta);
void noop_sequence_status_hook(u8 status);
void service_audio_timer_callback(void);
void set_audio_timer_state(int value);
void run_enabled_sound_sequence_update(void);
void clear_cd_audio_mix_mode(void);
void noop_audio_init_hook(void);
void reset_voices_slots_and_stop_spu_service(void);
void set_sound_flag_update_suppression(short value);
void flush_pending_sound_voice_flags(void);
void enable_available_spu_reverb(void);
int submit_shifted_stereo_sound_parameters(short x, short y);
int read_sequence_tempo_step(void);
void set_audio_channel_volume_control(int unused, short index, int value);
void set_audio_channel_pan_control(int unused, short index, int value);
void func_8005C980(void);
void func_8005C988(void);
void func_8005C990(void);
void func_8005C998(void);
void func_8005C9A0(void);
void set_spu_master_volume_pair(s16 first, s16 second);
void reset_and_release_audio_sequence_banks(void);
void submit_audio_driver_byte_command(s32 first, s32 second, s32 third);
void submit_audio_driver_scaled_pair(unsigned char code, short first, short second);
void dispatch_audio_driver_halfword_flags(s32 value);
void reset_audio_sequence_state_default(void);
void _spu_FsetDelayW(void);
void _spu_FsetDelayR(void);
void set_dma_channel_4_callback(int callback);
s32 is_tone_parameter_flag_set(void);
s32 update_spu_register_pair_cc_cd(s32 first, s32 second);
s32 read_spu_register_pair_cc_cd(void);
void apply_voice_attributes_and_key_on(void *object);

/* code2.c */
void set_scene_phase_callback(int value);
void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
void reset_scene_frame_callback_list(void);
void bind_view_triplet_source(void *state);
void initialize_timed_motion_step(unsigned short countdown, unsigned int amount);
void bind_global_triplet_source(void *state);
int audio_enable_mono_mix(void);
void audio_set_all_track_tempo_steps(int unused, int value);
void set_current_and_previous_menu_selection(void *object, s32 value);
int cancel_pending_sound_selection(void);
void invalidate_four_sprite_resource_slots(void);
int monster_get_species_name_text(int index);
void clear_runtime_slot_word_table(void);
void item_clear_recorded_category_pair(int first_value, int second_value);
void scene_save_previous_mode_and_reset_callbacks(void);
u8 select_display_spacing_table_entry(s32 index, s32 count);
void load_secondary_optional_resource_descriptor(void);
u8 get_previous_cd_command_byte(void);
void audio_disable_reverb(void);
int audio_get_channel_pan(int unused, short index);
int audio_get_channel_pitch_bend(int unused, short index);
void audio_set_channel_pitch_bend_value(s32 unused, s16 index, s32 value);
void resource_load_current_optional_descriptor(void);

/* konami_runtime_directory.c */
s32 find_runtime_table_key_index(s32 key);
s32 find_or_load_runtime_resource_key(s32 key);
void initialize_runtime_resource_directory(void);

/* konami_runtime_w_80038AB8.c */
s32 interpret_script_opcodes_until_action_changes(struct RuntimeContext *context, u8 *owner);

/* konami_runtime_w_80038C40.c */
s32 is_message_byte_in_lookup_set(s8 value);

/* sound_dma_lifecycle.c */
s32 _spu_init(s32 warm);
void _spu_FwriteByIO(u16 *src, u32 bytes_left);
void _spu_FiDMA(void);
void _spu_Fr_(s32 ram_address, s16 spu_address, s32 block_count);
void _spu_Fw1ts(void);

/* sound_key_buffer.c */
u32 modify_spu_register_bit_pair(s32 mode, u32 value, s32 low_index, s32 high_index);
void SpuSetKey(s32 key_on, u32 voices);

/* sound_streaming_transfer.c */
s32 SpuClearReverbWorkArea(s32 voice);

/* w_8003E34C.c */
void reset_cd_command_retry_state(void);

/* w_8003E4FC.c */
s32 Control_CD(s32 event_code, void *event_data, s32 payload);
s32 func_8003E4FC(s32 event_code, void *event_data, s32 payload);

/* w_8003E758.c */
void service_cd_command_queue(void);

/* w_8003F368.c */
s32 query_validated_cd_sector_with_retry(void);

/* w_8003F5AC.c */
s32 get_cd_flags_with_conditional_bit(void);

/* w_8003F624.c */
void cd_set_mode_with_retry(void);

/* w_80041094.c */
void request_scene_state_with_parameters(u16 notify_value, s16 state_10, s16 state_12, s16 state_14, s32 state_16);

/* w_80041134.c */
void remove_runtime_callback(s32 value);

/* w_80049E88.c */
u8 select_mapped_object_status_code(void *object);

/* w_8004DCA8.c */
void runtime_register_object_or_fallback_slot(void *object);

/* w_8004DCEC.c */
void runtime_call_selected_mode_handler(void);

/* w_8004DD2C.c */
void submit_script_with_registered_context(void *context);

/* w_8004DDE4.c */
void build_object_registration_script(void *data);

/* w_8004DE88.c */
void runtime_dispatch_control_coded_message(char *message);

/* w_8004DF8C.c */
void runtime_dispatch_and_reset_control_string(char *text);

/* w_8004E130.c */
void enqueue_script_message_command(void);

/* w_8004EF90.c */
void *init_object_header_a(void *cursor);

/* w_8004EFF4.c */
void *init_object_header_b(struct S_8004EFF4 *record);

/* w_8004F068.c */
void *init_object_header_c(void *cursor);

/* w_80050DA8.c */
void begin_selection_menu_teardown_and_fade(u8 *object);

/* w_80050E20.c */
void destroy_selection_menu_and_release_owner(struct S_80050E20 *object);

/* w_80053EF0.c */
s32 read_sound_mode_blocking_status(s32 mode);

/* w_8005ACDC.c */
void drain_ready_sound_voice_flags(void);

/* w_8005AE08.c */
s16 allocate_sequence_bank_slot(void *header, s32 sequence_id);

/* Data declarations. */
extern u8 D_80080AD0;
extern u8 cd_command_mode_byte;
extern u16 cd_command_poll_ticks;
extern u8 cd_command_read_index;
extern void *cd_event_payload;
extern s32 cd_queue_buffered_argument_word_0;
extern s32 cd_read_sync_result;
extern u32 cd_read_tail_word_address;
extern u16 cd_retry_counters_pending;
extern u8 *current_sort_rank_table;
extern u8 indexed_byte_table_count_plus_five;
extern u8 indexed_byte_table_double_count_plus_five;
extern s32 message_command_start_index;
extern s32 message_command_write_index;
extern s32 message_handler_mode;
extern s32 message_output_control_word;
extern s32 runtime_directory_entry_count;
extern s32 saved_value_output_enabled;
extern s32 selection_menu_saved_value;
extern int sound_payload_buffer;

#endif
