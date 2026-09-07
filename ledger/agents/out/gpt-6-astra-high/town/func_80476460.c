#include "common.h"

typedef struct {
    u16 values[4];
} TownValues;

extern u8 D_80010000[];
extern s8 D_80016000[];
extern s32 D_80017530;
extern s32 D_8001753C;
extern s32 D_80017598;
extern s32 D_800175A4;
extern s32 func_800198D0();

/* Selects a data pointer based on queried conditions and the current state index. */
void func_80017460(void **out_data) {
    TownValues condition_ids;
    register void *selected_data;
    s32 state_index;
    register TownValues *condition_table;

    condition_table = (TownValues *)(D_80010000 + 0x7134);
    condition_ids = *condition_table;
    if (func_800198D0(0x1391) == 0) {
        goto second_call;
    }
    selected_data = &D_80017530;
    goto out;
second_call:
    if (func_800198D0(0x14) == 0) {
        goto set_3c;
    }
    state_index = *(s32 *)(*(void **)D_80016000 + 8);
    if (func_800198D0(condition_ids.values[state_index]) != 0) {
        goto set_a4;
    }
    selected_data = &D_80017598;
    goto out;
set_a4:
    selected_data = &D_800175A4;
    goto out;
set_3c:
    selected_data = &D_8001753C;
out:
    *out_data = selected_data;
}
