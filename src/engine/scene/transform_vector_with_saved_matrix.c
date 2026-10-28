#include "common.h"
#include "shared/vector.h"
#include "sdk/libgte.h"
#include "engine/scene.h"

/* Transforms a vector with the supplied matrix while preserving the matrix stack. */
void transform_vector_with_saved_matrix(GteMatrix *matrix, GteShortVector *input_vec, GteTranslationVector *output_vec) {
    s32 flag;

    PushMatrix();
    SetTransMatrix(matrix);
    SetRotMatrix(matrix);
    RotTrans(input_vec, output_vec, &flag);
    PopMatrix();
}
