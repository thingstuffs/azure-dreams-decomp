#include "common.h"

#include "common.h"
#include "sdk/libgte.h"

typedef struct {
    s16 m[3][3];
    s16 pad;
    u16 t[3][2];
} MATRIX;

typedef struct {
    u16 vx;
    u16 vy;
    u16 vz;
    u16 pad;
} USVECTOR;

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVECTOR;

/* Transform a position into local coordinates using the current matrix. */
void world_to_local_position(USVECTOR *position, SVECTOR *local_position) {
    MATRIX current;
    MATRIX transposed;
    SVECTOR delta;

    ReadRotMatrix(&current);
    PushMatrix();

    delta.vx = position->vx - current.t[0][0];
    delta.vy = position->vy - current.t[1][0];
    delta.vz = position->vz - current.t[2][0];

    TransposeMatrix(&current, &transposed);
    ApplyMatrixSV(&transposed, &delta, local_position);
    PopMatrix();
}
