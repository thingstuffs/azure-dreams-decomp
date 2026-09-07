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

void func_800C1EA4(Entity *entity)
{
    Position *position;
    register s32 scratch ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 x_distance ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 mode;
    s16 abs_x;
    s16 abs_y;

    position = (Position *)D_80083780;
    ASM_KEEP(position);   /* MATCH pin: retail immediate-load split depends on it */
    x_distance = entity->x;
    scratch = position->x;
    position = (Position *)(s32)position->y;
    x_distance -= scratch;
    scratch = entity->y;
    abs_x = x_distance;
    if (x_distance < 0) {
        abs_x = -abs_x;
    }
    scratch -= (s32)position;
    mode = entity->mode;
    abs_y = scratch;
    if (scratch < 0) {
        abs_y = -abs_y;
    }

    if (mode == 0) {
        if (func_80033B2C(entity->predicate_arg) == 0) {
            return;
        }
        scratch = abs_x << 16;
    } else {
        if (func_80033B2C(entity->predicate_arg) != 0) {
            return;
        }
        scratch = abs_x << 16;
    }

    if (entity->limit_x < (scratch >> 16)) {
        return;
    }
    scratch = abs_y << 16;
    if (entity->limit_y < (scratch >> 16)) {
        return;
    }

    func_80053DA8(entity->argument);
    entity->handler = &D_800C1F8C;
}

/* MECHANISM: The internal 0x800C1F30 jump is a shared CFG label, not a callee.
   A guarded v1 Position base and split v1 mode role reproduce the retail prefix;
   branch-local shifted-x values fill both predicate delay slots and merge in v0. */
