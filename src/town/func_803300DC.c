#include "common.h"
extern int abs(int);



typedef struct S_8001A8DC_0 {
    s16 unk_00;
    s16 unk_02;
} S_8001A8DC_0;   /* other in func_8001A8DC */

typedef struct S_8001A8DC_1 {
    u16 unk_00;
    u16 unk_02;
} S_8001A8DC_1;   /* base in func_8001A8DC */

typedef struct S_8001A8DC_2 {
    s16 unk_00;
    s16 unk_02;
} S_8001A8DC_2;   /* out in func_8001A8DC */

/* Blend two points using the signed weight over the absolute weight sum; return the scaled y delta. */
s32 func_8001A8DC(void *base_point, void *other_point, s32 blend_weight, s32 other_weight, void *result_point)
{
    s32 scaled_y_delta;
    s32 other_x;
    s32 other_y;
    s32 abs_other_weight;
    s32 base_x;
    s32 base_y;
    void *base;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *other;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 weight;
    s32 total_weight;
    void *out;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    base = base_point;
    other = other_point;
    weight = blend_weight;
    out = result_point;
    ASM_KEEP(out);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    abs_other_weight = other_weight;
    total_weight = weight;
    total_weight = abs(total_weight);
    abs_other_weight = abs(abs_other_weight);
    total_weight += abs_other_weight;
    other_x = ((S_8001A8DC_0 *)other)->unk_00;
    ASM_KEEP(other_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    base_x = ((S_8001A8DC_1 *)base)->unk_00;
    ASM_KEEP(base_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ((S_8001A8DC_2 *)out)->unk_00 =
        base_x
        + ((other_x - (s16)((S_8001A8DC_1 *)base)->unk_00) * weight) / total_weight;
    other_y = ((S_8001A8DC_0 *)other)->unk_02;
    ASM_KEEP(other_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    base_y = ((S_8001A8DC_1 *)base)->unk_02;
    ASM_KEEP(base_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    scaled_y_delta =
        (other_y - (s16)((S_8001A8DC_1 *)base)->unk_02) * weight;
    ((S_8001A8DC_2 *)out)->unk_02 =
        base_y + scaled_y_delta / total_weight;
    return scaled_y_delta;
}
