#ifndef TOWN_PLAYER_H
#define TOWN_PLAYER_H

#include "common.h"


struct Rec_func_80094268_arg0;
struct S_800935BC_0;
void approach_target_tile_until_timeout(struct Rec_func_80094268_arg0 *target, struct S_800935BC_0 *position, void *transition_arg);

/* get_linked_record_field.c */
s32 get_linked_record_field_2_d_60(void);

struct S_8009A18C_0;
struct S_8009A18C_1;

void tick_player_countdown(void *object, void *state);
void initialize_player_data_reference(struct S_8009A18C_0 *data_ref, struct S_8009A18C_1 *state);

/* Phase-specific names of the existing linked-value and flag helpers. */
s32 get_entry_linked_value(void);
s32 read_entry_linked_value(void);
s32 get_scene_script_flag_mask(s32 flag);
void set_scene_script_flag_bit(s32 flag);
void clear_scene_script_flag_bit(s32 flag);

#endif
