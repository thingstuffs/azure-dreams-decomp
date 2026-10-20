#include "common.h"

s32 func_80064B90(void *, void *);
s32 func_80064BC0(void *, void *);
s32 func_80064CF0(void *);
s32 func_80064D80(void *);
s32 func_80065450(void *, void *, s32 *);
s32 func_80065820(void *, void *);
struct S_800AA044_0; struct S_800AA044_1; void copy_even_halfwords_3(struct S_800AA044_0 *, struct S_800AA044_1 *);            /* extern */
extern s32 D_800D11C0[4];

/* Apply rotation, scale, and translation to a vector and copy the result back. */
void transform_vector(s32 transform, void *vector, void *transformed) {
    s32 flags;

    func_80064B90(0x1F800054, &D_800D11C0);
    func_80065820(transform + 8, 0x1F800054);
    func_80064BC0(0x1F800054, transform + 0x10);
    func_80064CF0(0x1F800054);
    func_80064D80(0x1F800054);
    func_80065450(vector, transformed, &flags);
    copy_even_halfwords_3(vector, transformed);
}
