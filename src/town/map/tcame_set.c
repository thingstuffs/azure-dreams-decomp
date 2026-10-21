#include "common.h"

extern u8 D_800A4D4C[];
extern u8 town_position_reference_state[];

typedef struct {
    void *value;
    s32 pad[2];
} State;

extern State town_camera_chase_state;

/* tcame_chase2_set: Set the alternate camera chase handler and target pointers. */
void tcame_chase2_set(void) {
    u8 *state = (u8 *)&town_camera_chase_state;

    *(void **)(state + 0x28) = D_800A4D4C;
    town_camera_chase_state.value = town_position_reference_state;
    *(void **)(state + 0x2C) = town_position_reference_state;
}
