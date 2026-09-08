#include "common.h"



typedef s32 M2C_UNK;

typedef struct {
    s16 f0;
    s16 f1;
    s16 f2;
    s16 f3;
} Bounds;

typedef struct {
    u16 count;
    s16 index;
} State;

typedef struct {
    s16 f0;
    s16 f1;
    s16 f2;
    s16 f3;
} Entry;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_800240F0;


/* Advance the entry index when the point is inside its bounds, counting completed cycles. */
void func_80022F34(void *bounds_data, void *state_data) {
    s16 next_index;
    s16 entry_y;
    s16 entry_x;
    s16 point_x;
    s32 point_y;
    void *entries;
    Entry *entry;
    Bounds *bounds = (Bounds *)bounds_data;
    State *state = (State *)state_data;

    point_x = bounds->f1;
    point_y = bounds->f3;
    entries = &D_800240F0;
    entry = (Entry *)((state->index * 8) + entries);
    entry_x = entry->f0;
    if ((point_x >= entry_x) &&
        ((entry_x + entry->f2) >= point_x)) {
        entry_y = entry->f1;
        if (point_y >= entry_y) {
            if ((entry_y + entry->f3) < point_y)
                goto done;
            next_index = (u16)state->index + 1;
            ((volatile State *)state_data)->index = next_index;
            if (next_index >= 0xE) {
                state->index = 0;
                state->count = (u16)(state->count + 1);
            }
        }
    }
done:
    ;
}
