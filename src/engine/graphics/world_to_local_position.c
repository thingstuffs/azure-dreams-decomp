#include "common.h"
#include "shared/vector.h"

#include "sdk/libgte.h"

typedef struct {
    u16 vx;
    u16 vy;
    u16 vz;
    u16 pad;
} USVECTOR;

/* Transform a position into local coordinates using the current matrix. */
void world_to_local_position(USVECTOR *position, SVECTOR *local_position) {
    MATRIX current;
    MATRIX transposed;
    SVECTOR delta;

    ReadRotMatrix(&current);
    PushMatrix();

    delta.vx = position->vx - current.t[0];
    delta.vy = position->vy - current.t[1];
    delta.vz = position->vz - current.t[2];

    TransposeMatrix(&current, &transposed);
    ApplyMatrixSV(&transposed, &delta, local_position);
    PopMatrix();
}
