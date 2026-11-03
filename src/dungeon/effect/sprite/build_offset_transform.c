#include "common.h"
#include "dungeon/effect/sprite.h"
#include "engine/scene.h"
#include "sdk/libgte.h"

/* Builds a transform with a fixed-point offset and passes it to the output helper. */
void build_offset_transform(s32 source, s32 offset, s32 output) {
    s32 transform[10];

    transform[7] = 0;
    transform[6] = 0;
    transform[5] = 0;
    transform[8] = 0;
    transform[9] = offset << 0xC;
    RotMatrix(source, transform);
    transform_vector_with_saved_matrix(transform, &transform[8], output);
}
