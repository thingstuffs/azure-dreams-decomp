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

void func_800B2DCC(TownObject **objects) {
    s32 i = 0;

    do {
        objects[i]->position->x = (i / 5) * 128 + 88;
        objects[i]->position->y = (i % 5) * 16 + 136;
        i++;
    } while (i < 10);
}

/* MECHANISM: A frameless leaf with no saved registers or stack locals.
   Typed nested records preserve the two retail pointer reloads and color the
   quotient in $a0, producing the retail store-before-remainder schedule. */
