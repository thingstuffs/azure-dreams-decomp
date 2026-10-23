#ifndef TOWN_PLAYER_H
#define TOWN_PLAYER_H

#include "common.h"


/* get_linked_record_field.c */
s32 get_linked_record_field_2_d_60(void);

struct S_8009A18C_0;
struct S_8009A18C_1;

void tick_player_countdown(void *object, void *state);
void initialize_player_data_reference(struct S_8009A18C_0 *data_ref, struct S_8009A18C_1 *state);

#endif
