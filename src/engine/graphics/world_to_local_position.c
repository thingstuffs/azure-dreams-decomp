#include "common.h"
#include "engine/graphics.h"

#include "sdk/libgte.h"

/* Transform a position into local coordinates using the current matrix. */
void world_to_local_position(SVECTOR *position, SVECTOR *local_position) {
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
