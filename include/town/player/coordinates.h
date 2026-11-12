#ifndef TOWN_PLAYER_COORDINATES_H
#define TOWN_PLAYER_COORDINATES_H

struct SVECTOR;
struct ObjectPosition;

int squared_distance_3s(struct SVECTOR *point_a, struct SVECTOR *point_b);
unsigned int points_within_squared_threshold(struct SVECTOR *point_a, struct SVECTOR *point_b, int threshold);

short select_the_smaller_position_query_result_capped_n_64_writes_associated(void *position, int *out_value);

void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(struct ObjectPosition *position);

#endif
