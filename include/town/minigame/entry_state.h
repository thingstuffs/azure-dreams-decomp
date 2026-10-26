#ifndef TOWN_MINIGAME_ENTRY_STATE_H
#define TOWN_MINIGAME_ENTRY_STATE_H

void advance_bounded_entry_index(void *bounds_data, void *state_data);
void fill_eligible_negative_slots(void *record, short *eligibility, short new_value);

#endif
