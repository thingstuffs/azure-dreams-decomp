#include "common.h"

extern void *func_80016BD0(void *, void *, s32, s32);
extern s32 func_8001764C(u32);

extern u8 D_800176AC[9];
extern u8 D_80017778[9];
extern u8 D_80018ED1[9];

/* Select a result and override it when condition 12 is active. */
void *func_80632120(s32 selection_value, s32 unused, s32 selection_mode) {
    void *result;

    result = func_80016BD0(D_800176AC, D_80017778, selection_value, selection_mode);
    if (func_8001764C(12) != 0) {
        result = D_80018ED1;
    }
    return result;
}
