#include "common.h"

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

typedef struct {
    s16 pad_0;
    s16 x;
    s16 pad_4;
    s16 y;
} Position;

extern u8 D_80083780[8];
extern s32 D_800C1F8C;

extern s32 func_80033B2C(s16);
extern void func_80053DA8(u16);

/* Triggers the entity action and updates its handler when its predicate and distance checks pass. */
void func_800C1EA4(Entity *entity)
{
    Position *reference_pos;
    register s32 axis_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 x_delta ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 mode;
    s16 x_distance;
    s16 y_distance;

    reference_pos = (Position *)D_80083780;
    ASM_KEEP(reference_pos);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    x_delta = entity->x;
    axis_value = reference_pos->x;
    reference_pos = (Position *)(s32)reference_pos->y;
    x_delta -= axis_value;
    axis_value = entity->y;
    x_distance = x_delta;
    if (x_delta < 0) {
        x_distance = -x_distance;
    }
    axis_value -= (s32)reference_pos;
    mode = entity->mode;
    y_distance = axis_value;
    if (axis_value < 0) {
        y_distance = -y_distance;
    }

    if (mode == 0) {
        if (func_80033B2C(entity->predicate_arg) == 0) {
            return;
        }
        axis_value = x_distance << 16;
    } else {
        if (func_80033B2C(entity->predicate_arg) != 0) {
            return;
        }
        axis_value = x_distance << 16;
    }

    if (entity->limit_x < (axis_value >> 16)) {
        return;
    }
    axis_value = y_distance << 16;
    if (entity->limit_y < (axis_value >> 16)) {
        return;
    }

    func_80053DA8(entity->argument);
    entity->handler = &D_800C1F8C;
}

