#ifndef DUNGEON_EFFECT_PARTICLE_VERTEX_TRANSFORM_H
#define DUNGEON_EFFECT_PARTICLE_VERTEX_TRANSFORM_H

#include "sdk/libgte_matrix.h"

/* Stack request consumed by the transform. The vertex arrays may alias. */
typedef struct VertexTransformRequest {
    void *source;
    void *destination;
    SVECTOR rotation;
    SVECTOR translation;
    short count;
    unsigned short rotation_mode;
} VertexTransformRequest;

void transform_rotated_vertices(void *transform_data);

#endif
