#include "common.h"
#include "shared/types3a_types.h"

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


extern TownMoveGlobal D_800CFCB4;

/* Applies the enabled movement offsets, adding the z offset only when positive. */
void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(IntVector3 *out) {
    s32 z_offset;

    if (D_800CFCB4.enabled != 0) {
        out->x += D_800CFCB4.middle->inner->x;
        out->y += D_800CFCB4.middle->inner->y;
        z_offset = D_800CFCB4.middle->inner->z;
        if (z_offset > 0) {
            out->z += z_offset;
        }
    }
}
