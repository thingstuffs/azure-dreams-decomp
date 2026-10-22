/* Squared distance.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00705 - CL:town/func_80330320.
 */
#include "town/player/squared_distance_g00705.h"

/* Compute the squared distance between two 3D points. */
s32 squared_distance_3s(Vec3s *point_a, Vec3s *point_b) {
    s32 diff;
    s32 total;

    diff = point_b->x;
    diff -= point_a->x;
    total = diff * diff;
    diff = point_b->y;
    diff -= point_a->y;
    total += diff * diff;
    diff = point_b->z;
    diff -= point_a->z;
    return total + diff * diff;
}

/* Returns the lowest-valued entry and reports a player.c assertion if none is selected. */
s32 find_nearest_point_3s(s32 entries, s32 eval_context, s32 entry_count) {
    s32 best_entry;
    s32 best_value;
    s32 index;
    s32 value;
    void *object;
    void *dispatch;
    TownCopyFn report_assert;
    TownSetFn set_fn;

    best_value = 0x7FFFFFFF;
    best_entry = 0;
    for (index = 0; index < entry_count; index++) {
        value = squared_distance_3s(entries, eval_context);
        if (value < best_value) {
            best_entry = entries;
            best_value = value;
        }
        entries += 8;
    }

    if (best_entry == 0) {
        object = *(void **)((s8 *)(&D_80016000));
        dispatch = *(void **)((s8 *)object + 0x20);
        report_assert = *(TownCopyFn *)((s8 *)dispatch + 0x168);
        report_assert(D_80016130, D_80016158, 0x40);

        object = *(void **)((s8 *)(&D_80016000));
        dispatch = *(void **)((s8 *)object + 0x20);
        set_fn = *(TownSetFn *)((s8 *)dispatch + 0x174);
        set_fn(1);
    }
    return best_entry;
}
