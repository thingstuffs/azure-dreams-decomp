#ifndef DUNGEON_EFFECT_TRAVEL_WARP_PHASE_EFFECT_H
#define DUNGEON_EFFECT_TRAVEL_WARP_PHASE_EFFECT_H

#include "common.h"

/* Body allocated by create_warp_phase_effect and advanced by
 * advance_effect_phases. The source node address is stored at body offset 8. */
typedef struct WarpPhaseEffectBody {
    u8 pad_00[0x8];
    s32 source_node_address;
    u8 pad_0C[0x18];
    u16 offset_x;
    u16 offset_y;
    s16 offset_z;
    u8 pad_2A[0x2];
    s16 phase;
    s16 initialized;
} WarpPhaseEffectBody;

#endif
