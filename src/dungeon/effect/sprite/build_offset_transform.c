#include "common.h"

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


s32 func_80065820(s32, s32 *);
void transform_vector_with_saved_matrix(S_8003E0C4_MATRIX *matrix, S_8003E0C4_SVECTOR *input_vec, S_8003E0C4_VECTOR *output_vec);

/* Builds a transform with a fixed-point offset and passes it to the output helper. */
void build_offset_transform(s32 source, s32 offset, s32 output) {
    s32 transform[10];

    transform[7] = 0;
    transform[6] = 0;
    transform[5] = 0;
    transform[8] = 0;
    transform[9] = offset << 0xC;
    func_80065820(source, transform);
    transform_vector_with_saved_matrix(transform, &transform[8], output);
}
