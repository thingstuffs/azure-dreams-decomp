#ifndef DUNGEON_ITEM_H
#define DUNGEON_ITEM_H

/* Function contracts owned by src/dungeon/item/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void *append_signed_value_bytes(s32 value, u8 *buffer);
u8 *apply_type_based_entry_adjustments(void *entry, u8 *value);
void create_view_color_flash(s32 payload, s16 trigger_event);
void *find_linked_entity_of_type_21(void *entity);
s32 find_padded_rectangle(s32 pos_x, s32 pos_y);
s32 get_direction_toward_target_position(s16 *target_pos);
void initialize_monster_script_counter(void);
void *advance_monster_timed_sequence(void);
s16 *read_monster_script_entry(void);
void inventory_clear_object_field_and_entry(s32 object_addr);
void inventory_process_resources_and_set_flags(void *object);
void inventory_set_embedded_state_four(s32 object_addr);
void set_monster_data_pointer(void);
void tick_monster_spawn_timer(void);




struct DungeonItemEntry;
s32 use_item_to_apply_poison(ActorRecord *entity, struct DungeonItemEntry *item, s16 action_type);

void play_b4_sound(void);
void create_terrain_particle_emitter(s16 tile_x, s16 tile_y, s16 initial_value);


void *write_status_prefix_bytes(void *dst);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);

void adjust_source_value_and_finalize(void *context, const void *source);

/* Callback entry points. */
s32 begin_return_magic_for_player_and_familiars(void);
void update_return_magic_sacrifice(void *effect, void *vertices, void *sprite);

void create_timed_paired_particle_emitter(ObjectPosition *source, s32 effect_param, void *actor);

void *copy_fullwidth_vowel_bytes(void *dst, void *character);
/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *scan_actor_along_heading(ActorRecord *source, s32 start_x, s32 start_y, s16 heading, s16 max_steps);

void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s32 extra_byte);

void *find_monster_special_entry(s32 wanted_kind, s32 wanted_flag);
u8 *find_or_retain_sprite_resource_slot(s32 requested_id, s32 requested_type);

s32 retain_spawn_resource(s16 entry_type, s16 entry_key);


#include "shared/dungeon_item_entries.h"
u8 *append_typed_formatted_value(DungeonItemEntry *data, u8 *buffer);

u8 *append_entity_display_text(void *record, u8 *out);
u8 *clear_byte_and_advance(u8 *byte_ptr);

s32 use_item_to_restore_eyesight(void *entity, DungeonItemEntry *item, s16 effect);

#endif
