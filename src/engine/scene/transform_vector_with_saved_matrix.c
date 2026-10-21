#include "common.h"
#include "sdk/libgte.h"

typedef struct {
    s16 m[3][3];
    s32 t[3];
} S_8003E0C4_MATRIX;

typedef struct {
    s16 vx, vy, vz, pad;
} S_8003E0C4_SVECTOR;

typedef struct {
    s32 vx, vy, vz;
} S_8003E0C4_VECTOR;

/* Transforms a vector with the supplied matrix while preserving the matrix stack. */
void transform_vector_with_saved_matrix(S_8003E0C4_MATRIX *matrix, S_8003E0C4_SVECTOR *input_vec, S_8003E0C4_VECTOR *output_vec) {
    s32 flag;

    PushMatrix();
    SetTransMatrix(matrix);
    SetRotMatrix(matrix);
    RotTrans(input_vec, output_vec, &flag);
    PopMatrix();
}
