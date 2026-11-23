#include "common.h"
#include "sdk/libgte.h"
#include "town/map.h"
#include "shared/scratchpad.h"

typedef union Quad {
    u32 words[4];
    s16 vals[8];
} Quad;

typedef struct ScratchQuad {
    u8 pad00[0x6C];
    Quad quad;
    ScratchQuadTurnOutput turn;
} ScratchQuad;

/* Checks the quad's angular gaps against a half-turn limit. */
s32 check_scratch_quad_half_turn_gaps(ScratchQuad *scratch) {
    if (scratch->quad.words[0] == 0) {
        return 1;
    }
    if (scratch->quad.words[3] == 0) {
        return 1;
    }

    scratch->turn.angles[0] = ratan2(scratch->quad.vals[1], scratch->quad.vals[0]);
    scratch->turn.angles[3] = ratan2(scratch->quad.vals[7], scratch->quad.vals[6]);
    scratch->turn.angles[3] -= scratch->turn.angles[0];
    scratch->turn.gaps[2] = (4096 - scratch->turn.angles[3]) & 0xFFF;
    if (scratch->turn.gaps[2] >= 2049) {
        return 0;
    }
    if (scratch->quad.words[2] == 0) {
        return 1;
    }

    scratch->turn.angles[2] = ratan2(scratch->quad.vals[5], scratch->quad.vals[4]);
    scratch->turn.angles[2] -= scratch->turn.angles[0];
    scratch->turn.gaps[1] = (scratch->turn.angles[3] - scratch->turn.angles[2]) & 0xFFF;
    if (scratch->turn.gaps[1] >= 2049) {
        return 0;
    }
    if (scratch->quad.words[1] == 0) {
        return 1;
    }

    scratch->turn.angles[1] = ratan2(scratch->quad.vals[3], scratch->quad.vals[2]);
    scratch->turn.angles[1] = (scratch->turn.angles[1] - scratch->turn.angles[0]) & 0xFFF;
    if (scratch->turn.angles[1] >= 2049) {
        return 0;
    }
    scratch->turn.gaps[0] = (scratch->turn.angles[2] - scratch->turn.angles[1]) & 0xFFF;
    return scratch->turn.gaps[0] < 2049;
}
