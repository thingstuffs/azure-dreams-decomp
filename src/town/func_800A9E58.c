#include "common.h"

extern void townCreatePositionedSpriteObject(s32 position, void *state_value, void *graphic_id);
extern u8 D_800A74D8[];
extern u8 D_800D0E04[];

/* Creates an object at the given position with preset state and sprite data. */
void townCreatePresetSpriteObject(s32 position) {
    townCreatePositionedSpriteObject(position, D_800A74D8, D_800D0E04);
}
