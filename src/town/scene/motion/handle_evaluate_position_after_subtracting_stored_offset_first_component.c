#include "common.h"

extern s16 min_indexed_query(s32 *values, void *ptr, s32 value);
extern s32 D_800CFD58;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} StackRecord;

/*
 * Copies the position with its stored X offset subtracted and returns the minimum indexed query
 * over two D_800CFD58 entries.
 */
s16 handle_evaluate_position_after_subtracting_stored_offset_first_component(void *position) {
    StackRecord record;

    record.x = *(s32 *)position - *(s32 *)((u8 *)position + 0xC);
    record.y = *(s32 *)((u8 *)position + 4);
    record.z = *(s32 *)((u8 *)position + 8);
    return min_indexed_query(&record.x, &D_800CFD58, 2);
}
