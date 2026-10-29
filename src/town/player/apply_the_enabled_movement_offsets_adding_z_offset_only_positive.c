#include "common.h"
#include "shared/vector.h"
#include "town/player.h"

typedef struct TownMoveInner {
    s32 unk0[3];
    s32 x;
    s32 y;
    s32 z;
} TownMoveInner;

typedef struct TownMoveMiddle {
    s32 unk0[2];
    TownMoveInner *inner;
} TownMoveMiddle;

typedef struct TownMoveGlobal {
    s32 unk0[8];
    TownMoveMiddle *middle;
    u8 unk24[0x17];
    u8 enabled;
} TownMoveGlobal;


extern TownMoveGlobal town_actor_control;

/* Applies the enabled movement offsets, adding the z offset only when positive. */
void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(IntVector3 *out) {
    s32 z_offset;

    if (town_actor_control.enabled != 0) {
        out->x += town_actor_control.middle->inner->x;
        out->y += town_actor_control.middle->inner->y;
        z_offset = town_actor_control.middle->inner->z;
        if (z_offset > 0) {
            out->z += z_offset;
        }
    }
}
