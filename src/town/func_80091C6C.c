#include "common.h"

extern s16 func_8008CA20(s32 *values, void *ptr, s32 value);
extern s32 D_800CFD58;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} StackRecord;

/* Evaluate a position after subtracting its stored offset from the first component. */
s16 func_8008F3CC(void *position) {
    StackRecord record;

    record.x = *(s32 *)position - *(s32 *)((u8 *)position + 0xC);
    record.y = *(s32 *)((u8 *)position + 4);
    record.z = *(s32 *)((u8 *)position + 8);
    return func_8008CA20(&record.x, &D_800CFD58, 2);
}
