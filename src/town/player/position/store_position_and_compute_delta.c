typedef signed int s32;

extern s32 town_collision_motion[6];

// Store the new three-component value and its difference from the previous value.
void store_position_and_compute_delta(s32 *newValue)
{
    town_collision_motion[3] = newValue[0] - town_collision_motion[0];
    town_collision_motion[4] = newValue[1] - town_collision_motion[1];
    town_collision_motion[5] = newValue[2] - town_collision_motion[2];
    town_collision_motion[0] = newValue[0];
    town_collision_motion[1] = newValue[1];
    town_collision_motion[2] = newValue[2];
}
