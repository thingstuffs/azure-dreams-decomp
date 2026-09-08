#include "common.h"

extern s16 func_8008CA20(s32 *arg0, void *arg1, s32 arg2);
extern s32 D_800CFD58;

typedef struct {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 unused[3];
} StackRecord;

/* Evaluate a position after subtracting its stored offset from the first component. */
s16 func_8008F3CC(void *position) {
    StackRecord record;

    record.sp10 = *(s32 *)position - *(s32 *)((u8 *)position + 0xC);
    record.sp14 = *(s32 *)((u8 *)position + 4);
    record.sp18 = *(s32 *)((u8 *)position + 8);
    return func_8008CA20(&record.sp10, &D_800CFD58, 2);
}
