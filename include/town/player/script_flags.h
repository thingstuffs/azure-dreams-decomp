#ifndef TOWN_PLAYER_SCRIPT_FLAGS_H
#define TOWN_PLAYER_SCRIPT_FLAGS_H

/* Indices zero and one are the constant false and true flag queries. */
int get_script_flag_mask(int flag_index);
void set_script_flag_bit(int bit_index);
void clear_script_flag_bit(int bit_index);

#endif
