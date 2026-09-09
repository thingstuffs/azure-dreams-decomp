#include "common.h"
#include "m2c_compat.h"

void *func_800A0988(M2C_UNK);                              /* extern */

typedef struct S_800A0A54_0 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A0A54_0;   /* temp_v0 in door_atari_on_off */

/* door_atari_on_off: Set the collision flag for the selected door. */
void door_atari_on_off(M2C_UNK door_id, s16 collision_enabled) {
    S_800A0A54_0 *door;

    door = func_800A0988(door_id);
    if (door != NULL) {
        door->unk_88 = collision_enabled;
    }
}
