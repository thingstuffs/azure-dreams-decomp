#ifndef SHARED_VECTOR_H
#define SHARED_VECTOR_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Two signed screen components used for ellipse triangle vertices. */
typedef struct ScreenPoint16 {
    short vx;
    short vy;
} ScreenPoint16;

/* Three-word translation passed by address to the GTE helpers; retains the local 12-byte extent. */
/* Three-word GTE translation result, stored in caller-local work.
 * compose_and_install_camera_transform fills it through RotTrans and passes it to TransMatrix. */
typedef struct GteTranslationVector {
    int vx; /* transformed X translation component */
    int vy; /* transformed Y translation component */
    int vz; /* transformed Z translation component */
} GteTranslationVector;

/* Three signed words used as coordinates or vectors in caller-owned storage.
 * This type supplies no allocation or common scale: read each producer for world/fixed-point units and lifetime. */
typedef struct IntVector3 {
    int x;
    int y;
    int z;
} IntVector3;

/* Two signed words in the angle record rooted at D_80100D60. */
typedef struct PositionRotationPair { short field_0; short angle; } PositionRotationPair;

/* Signed two-coordinate value used by interpolation and grid callers. */
typedef struct SignedPair16 {
    short unk_00;
    short unk_02;
} SignedPair16;

/* Matrix passed to ReadRotMatrix/RotMatrix/CompMatrix/TransMatrix and the
 * GTE matrix setters. Rotation is nine signed halfwords; translation is
 * three signed words at +0x14. The explicit halfword keeps the 0x20 extent. */
typedef struct GteMatrix {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} GteMatrix;

/* Signed GTE vector supplied to RotTrans/ApplyMatrixSV or the angle argument
 * of RotMatrix. Keep the fourth halfword and eight-byte local extent. */
typedef struct GteShortVector {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} GteShortVector;

/* Orientation results reused as indexed distances in movement scratch storage. */
typedef union GteOffset {
    GteShortVector orientation;
    u16 distance[4]; /* BYTES: retain unsigned indexed halfword loads. */
} GteOffset;

#endif
