#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80065820(s32, s32 *);
extern void transformVectorWithSavedMatrix(s32 *, s32 *, M2C_UNK);

/* Builds a transform with a fixed-point offset and passes it to the output helper. */
void dungeonBuildOffsetTransform(s32 source, s32 offset, M2C_UNK output) {
    s32 transform[10];

    transform[7] = 0;
    transform[6] = 0;
    transform[5] = 0;
    transform[8] = 0;
    transform[9] = offset << 0xC;
    func_80065820(source, transform);
    transformVectorWithSavedMatrix(transform, &transform[8], output);
}
