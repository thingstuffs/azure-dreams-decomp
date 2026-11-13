#ifndef TOWN_PLAYER_COORDINATES_H
#define TOWN_PLAYER_COORDINATES_H

struct SVECTOR;
struct ObjectPosition;

int squared_distance_3s(struct SVECTOR *point_a, struct SVECTOR *point_b);
unsigned int points_within_squared_threshold(struct SVECTOR *point_a, struct SVECTOR *point_b, int threshold);

short query_capped_surface_height(void *position, int *out_value);

void step_perpendicular_to_input(struct ObjectPosition *position);

#endif
