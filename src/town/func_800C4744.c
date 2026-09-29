#include "common.h"
#include "shared/entity_objects.h"

typedef struct {
    void *handler;
    s16 x;
    s16 y;
    s16 limit_x;
    s16 limit_y;
    u8 pad_C[4];
    u16 argument;
    s16 predicate_arg;
    s16 mode;
} Entity;

extern s32 D_800C1F8C;
extern int abs(int);

extern s32 func_80033B2C(s16);
extern void SD_Call(u16);

/* Triggers the entity action and updates its handler when its predicate and distance checks pass. */
void func_800C1EA4(Entity *entity)
{
    s32 x_distance;
    s32 y_distance;

    x_distance = abs(entity->x - D_80083780.x.w.i);
    y_distance = abs(entity->y - D_80083780.y.w.i);

    if (entity->mode == 0) {
        if (func_80033B2C(entity->predicate_arg) == 0) {
            return;
        }
    } else {
        if (func_80033B2C(entity->predicate_arg) != 0) {
            return;
        }
    }

    if ((s16)x_distance > entity->limit_x) {
        return;
    }
    if ((s16)y_distance > entity->limit_y) {
        return;
    }

    SD_Call(entity->argument);
    entity->handler = &D_800C1F8C;
}
