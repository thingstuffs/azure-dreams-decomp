#include "common.h"
#include "town/minigame.h"

/* Increment the object's 16-bit field at offset 0x18 by 0x20. */
void rotate_gym_mesh_y(s32 unused_0, ObjectPosition *unused_1, u8 *object) {
    *(u16 *)(object + 0x18) += 0x20;
}
