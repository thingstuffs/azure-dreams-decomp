#ifndef TOWN_SCENE_MOTION_OFFSET_QUERIES_H
#define TOWN_SCENE_MOTION_OFFSET_QUERIES_H

short min_sampled_position_minus_y_offset(void *position);
short query_position_with_first_component_offset(void *position);
short query_position_with_second_component_offset(void *position);

#endif
