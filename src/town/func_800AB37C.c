#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    Vec3 first;
    Vec3 second;
} Pair;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused_0C;
    s32 unused_10;
} Work;

extern s32 scaleRandomToUnsignedHalfwordLimit();
extern void townSpawnRadialObjects();
extern void townSpawnRadialEffectObjects();
extern Pair D_80089128;

/* Process a position and its raised copy using a local vector pair. */
void townProcessRaisedPositionPair(s32 unused_arg, s32 *position) {
    Pair pair;
    Work raised_pos;

    pair = D_80089128;
    raised_pos.x = position[0];
    raised_pos.y = position[1];
    raised_pos.z = position[2] + 0x100000;
    townSpawnRadialEffectObjects(position, &pair, (scaleRandomToUnsignedHalfwordLimit(2) & 0xFFFF) + 2);
    townSpawnRadialObjects(&raised_pos, &pair, (scaleRandomToUnsignedHalfwordLimit(2) & 0xFFFF) + 2);
}
