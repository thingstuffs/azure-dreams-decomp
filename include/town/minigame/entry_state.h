#ifndef TOWN_MINIGAME_ENTRY_STATE_H
#define TOWN_MINIGAME_ENTRY_STATE_H

struct ObjectPosition;
struct MinigameProgressPair16;
void advance_path_waypoint(struct ObjectPosition *bounds_data, struct MinigameProgressPair16 *progress);
void fill_eligible_negative_slots(void *record, struct MinigameProgressPair16 *progress, short new_value);

#endif
