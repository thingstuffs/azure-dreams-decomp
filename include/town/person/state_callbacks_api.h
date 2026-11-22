#ifndef TOWN_PERSON_STATE_CALLBACKS_API_H
#define TOWN_PERSON_STATE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct TownObjectRecord;
void advance_person_state_value(struct TownObjectRecord *state);
void update_person_countdown_state(struct TownObjectRecord *record);

#endif
