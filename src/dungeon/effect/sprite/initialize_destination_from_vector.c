#include "dungeon/effect/sprite/linked_object_chain.h"
#include "sdk/libgte.h"

/* Build the chain node's matrix from its selected rotation, translation and scale. */
void initialize_destination_from_vector(MATRIX *dest, LinkedSpriteFrame *source) {
    VECTOR scale;

    RotMatrix(&source->rotation, dest);
    scale.vx = source->scale.vx;
    scale.vy = source->scale.vy;
    scale.vz = source->scale.vz;
    ScaleMatrix(dest, &scale);
    dest->t[0] = source->translation.vx;
    dest->t[1] = source->translation.vy;
    dest->t[2] = source->translation.vz;
}
