#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H
/* Prototypes of the functions defined in src/engine/entity/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* 58 independent 24-byte initial-stat records end at D_8006D6D8.
 * The bytes copied by init_monster_from_stats are not presumed padding. */
typedef MonsterInitialStats EntityInitialStats;
extern EntityInitialStats initialStatsTable[58];

/* Species-indexed resident trait words, with two existing address aliases.
 * The complete upper bound is unknown; it is not the initial-stat count. */
extern s32 D_8006D6D8[];
extern s32 monster_native_trait_masks[];

/* Cumulative experience needed for each level, 100 words filling 0x800835E8..0x80083777 up to
 * entity_cubic_table_constant. BSS: build_cubic_cumulative_table builds it once at start-up
 * (initialize_hardware_and_game_state); the EXE bytes at this address lie past the loaded image
 * and never reach RAM, so values read from the file there are not the table. */
extern s32 entity_level_thresholds[100];

struct CallbackObject;
struct S_800423C0_Obj;
struct S_800423C0_Src;

/* apply_entity_effects.c */
void apply_entity_effects(void *entity);
void func_80041E70(void *entity);

/* build_cubic_cumulative_table.c */
void build_cubic_cumulative_table(void);

/* clear_scaled_cell_flags.c */
void clear_scaled_cell_flags_8000(void);

/* entry_set_or_clear_actor_status_slot.c */
void replay_actor_status_slots(struct CallbackObject *object);

/* find_entity_slot_by_field_ac.c */
void apply_actor_template_and_direction(struct S_800423C0_Obj *obj, s16 unused, struct S_800423C0_Src *source);

/* init_monster_from_stats.c */
void func_80042640(void *obj, s16 monsterId);
void init_monster_from_stats(void *obj, s16 monsterId);

/* is_frame_packet_arena_overflowed.c */
short enqueue_audio_command(int value);
s32 clamp_sound_value_to_seven_bits(s16 value);
s32 lookup_patterned_display_icon(s32 index);
s32 lookup_unpatterned_display_icon(s32 index);
void load_primary_optional_resource_descriptor(void);
s32 is_frame_packet_arena_overflowed(u32 limit);
void set_audio_channel_program(unsigned char entry_index, unsigned char value);
void sort_signed_word_array(int count, void *base);
int read_audio_channel_control(int unused_0, short entry_index, int unused_2);

/* reset_entry_flags.c */
void reset_entry_flags(void);

/* reset_state_defaults.c */
void reset_state_defaults(void);

/* reset_tagged_entry_states.c */
void reset_tagged_entry_states(void);

/* runtime_save_or_restore_state.c */
void runtime_save_or_restore_state(void);

/* runtime_test_table_byte_pattern.c */
s32 runtime_test_table_byte_pattern(s16 entry_id);

/* set_scaled_cell_flags.c */
void set_scaled_cell_flags_8000(void);

/* update_owner_class_bits.c */
void func_80042984(void *entity);
void update_owner_class_bits(void *entity);

#endif
