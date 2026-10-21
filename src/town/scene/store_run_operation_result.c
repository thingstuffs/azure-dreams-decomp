/* Relinked copy of town/func_804712E0 (func_804712E0.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 run_operation(void *entries, s32 value);
extern s32 scene_money_adjustment;
extern s32 D_800188D0[];

/* Stores the result of run_operation for D_800188D0 in D_800188C8. */
void store_run_operation_result(void) {
    scene_money_adjustment = run_operation(D_800188D0, 1);
}
