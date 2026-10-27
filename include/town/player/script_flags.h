#ifndef TOWN_PLAYER_SCRIPT_FLAGS_H
#define TOWN_PLAYER_SCRIPT_FLAGS_H

/* Indices zero and one are the constant false and true flag queries. */
int get_script_flag_mask(int flag_index);
void set_script_flag_bit(int bit_index);
void clear_script_flag_bit(int bit_index);

/* BYTES: These scene-bank names keep calls bound to the placed bitmap helpers.
 * Replacing them with the resident names changes the linked call targets. */
int func_80018B5C(int flag_index);
int func_8001894C(int flag_index);
void func_80018A64(int bit_index);
void func_80018ADC(int bit_index);

#endif
