/* Arrange ten objects in menu columns. */
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


/*
 * Places ten objects in two columns of five, with X positions -48/80 and Y positions starting at
 * 22 in steps of 16.
 */
void arrange_ten_objects_in_menu_columns(TownObject **objects) {
    s32 objectIndex = 0;

    do {
        objects[objectIndex]->position->x = (objectIndex / 5) * 128 - 48;
        objects[objectIndex]->position->y = (objectIndex % 5) * 16 + 22;
        objectIndex++;
    } while (objectIndex < 10);
}
