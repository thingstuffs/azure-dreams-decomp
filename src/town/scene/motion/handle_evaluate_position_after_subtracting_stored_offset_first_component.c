#include "common.h"

extern s16 min_indexed_query(s32 *values, void *ptr, s32 value);
extern s32 D_800CFD58;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} StackRecord;

/* Evaluate a position after subtracting its stored offset from the first component. */
s16 handle_evaluate_position_after_subtracting_stored_offset_first_component(void *position) {
    StackRecord record;

    record.x = *(s32 *)position - *(s32 *)((u8 *)position + 0xC);
    record.y = *(s32 *)((u8 *)position + 4);
    record.z = *(s32 *)((u8 *)position + 8);
    return min_indexed_query(&record.x, &D_800CFD58, 2);
}
