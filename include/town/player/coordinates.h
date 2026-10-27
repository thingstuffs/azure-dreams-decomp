#ifndef TOWN_PLAYER_COORDINATES_H
#define TOWN_PLAYER_COORDINATES_H

struct GteShortVector;

void copy_current_record_components_3(void *components);
int squared_distance_3s(struct GteShortVector *point_a, struct GteShortVector *point_b);
unsigned int points_within_squared_threshold(struct GteShortVector *point_a, struct GteShortVector *point_b, int threshold);

#endif
