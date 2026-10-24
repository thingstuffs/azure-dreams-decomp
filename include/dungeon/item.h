#ifndef DUNGEON_ITEM_H
#define DUNGEON_ITEM_H

/* Function contracts owned by src/dungeon/item/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void *append_signed_value_bytes(s32 value, u8 *buffer);
s32 apply_type_based_entry_adjustments(void *entry, s32 value);
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




s32 use_item_to_apply_poison(ActorRecord *entity, s32 item, s16 action_type);

void play_b4_sound(void);
void create_terrain_particle_emitter(s16 tile_x, s16 tile_y, s16 initial_value);

#endif
