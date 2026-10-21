#include "common.h"

typedef struct {
    void *value;
    s32 pad[9];
    void (*callback)(void *);
} State;

extern void reset_or_copy_state_values(void *);
extern u8 town_position_reference_state[];
extern State town_camera_chase_state;

/* tcame_chase_set: Set the camera chase callback and target. */
void tcame_chase_set(void) {
    u8 *state_bytes = (u8 *)&town_camera_chase_state;

    *(void (**)(void *))(state_bytes + 0x28) = reset_or_copy_state_values;
    town_camera_chase_state.value = town_position_reference_state;
}
