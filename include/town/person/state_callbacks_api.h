#ifndef TOWN_PERSON_STATE_CALLBACKS_API_H
#define TOWN_PERSON_STATE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct town_person_countdown_state;
struct town_person_value_state;
void advance_person_state_value(struct town_person_value_state *state);
void update_person_countdown_state(struct town_person_countdown_state *record);

#endif
