#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef union { s32 word; struct { u16 low, high; } half; } FixedCoord;
typedef struct { FixedCoord x, y, z; } MotionPosition;
typedef struct { u8 pad00[0x14]; s16 direction; u8 pad16[0x1C]; s16 speed; } MotionState;
typedef struct { u8 pad00[6]; u16 count; void *resource; s32 value; u8 pad10[12]; u16 scale_x, scale_y; } MotionDraw;
typedef struct { u8 pad00[8]; MotionPosition *position; MotionDraw *draw; void (*update)(MotionState *, MotionPosition *); u8 pad14[12]; MotionState state; } MotionObject;
extern MotionObject *func_8003FD64(s32 kind, MotionObject *parent);
extern void func_8004491C(MotionObject *, void (*)(void));
extern void func_80045340(void);
extern void func_80174E98(MotionState *, MotionPosition *);
extern u32 func_80069EF8(void);
extern u8 D_80175F9C[];
void func_80174FC0(MotionObject *parent, s16 direction, s32 value) {
    MotionObject *object;
    MotionDraw *draw;
    MotionState *state;
    object = func_8003FD64(0x212, parent);
    if (object != 0) {
        object->update = func_80174E98;
        func_8004491C(object, func_80045340);
        object->position->x.half.high = parent->position->x.half.high + (func_80069EF8() & 0x3F) - 0x20;
        object->position->y.half.high = parent->position->y.half.high + (func_80069EF8() & 0x3F) - 0x20;
        object->position->z.half.high = parent->position->z.half.high + (func_80069EF8() & 0x3F) - 0x20;
        draw = object->draw;
        state = &object->state;
        draw->resource = D_80175F9C;
        draw->scale_x = draw->scale_y = 0x1000;
        draw->value = value;
        draw->count = 8;
        state->direction = direction;
        state->speed = (func_80069EF8() & 0xFF) | 0x80;
    }
}
