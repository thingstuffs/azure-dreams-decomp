#ifndef TOWN_PLAYER_COORDINATES_H
#define TOWN_PLAYER_COORDINATES_H

struct GteShortVector;

int squared_distance_3s(struct GteShortVector *point_a, struct GteShortVector *point_b);
unsigned int points_within_squared_threshold(struct GteShortVector *point_a, struct GteShortVector *point_b, int threshold);

short select_the_smaller_position_query_result_capped_n_64_writes_associated(void *position, int *out_value);

void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(void *position);

#endif
