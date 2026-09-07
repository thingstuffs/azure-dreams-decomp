#include "common.h"

typedef struct {
    s8 pad[8];
    s16 x;
    s16 y;
} TownPosition;

typedef struct {
    s32 unk0;
    TownPosition *position;
} TownObject;

/* Position ten objects in two columns of five. */
void func_800B2DCC(TownObject **objects) {
    s32 objectIndex = 0;

    do {
        objects[objectIndex]->position->x = (objectIndex / 5) * 128 + 88;
        objects[objectIndex]->position->y = (objectIndex % 5) * 16 + 136;
        objectIndex++;
    } while (objectIndex < 10);
}
