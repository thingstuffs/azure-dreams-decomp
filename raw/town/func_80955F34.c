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

void func_80022F34(void *arg0, void *arg1) {
    s16 temp_v0;
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_a3;
    s32 temp_t0;
    void *temp_base;
    Entry *temp_v1;
    Bounds *p0 = (Bounds *)arg0;
    State *p1 = (State *)arg1;

    temp_a3 = p0->f1;
    temp_t0 = p0->f3;
    temp_base = &D_800240F0;
    temp_v1 = (Entry *)((p1->index * 8) + temp_base);
    temp_a2 = temp_v1->f0;
    if ((temp_a3 >= temp_a2) &&
        ((temp_a2 + temp_v1->f2) >= temp_a3)) {
        temp_a0 = temp_v1->f1;
        if (temp_t0 >= temp_a0) {
            if ((temp_a0 + temp_v1->f3) < temp_t0)
                goto done;
            temp_v0 = (u16)p1->index + 1;
            ((volatile State *)arg1)->index = temp_v0;
            if (temp_v0 >= 0xE) {
                p1->index = 0;
                p1->count = (u16)(p1->count + 1);
            }
        }
    }
done:
    ;
}
