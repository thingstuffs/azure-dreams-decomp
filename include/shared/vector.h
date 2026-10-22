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

/* Three signed coordinate/vector words; units remain defined by the caller. */
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

#endif
