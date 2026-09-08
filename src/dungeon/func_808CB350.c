#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_801237A4_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_801237A4();    /* extern */
typedef struct HalfValue {
    s32 pad[2];
    u16 value;
} HalfValue;

typedef struct ValueLink {
    s32 pad;
    HalfValue *next;
} ValueLink;

extern s32 * volatile D_80129728[28];


void func_801237E8(Rec_func_801237A4_arg0 *arg0) {
    s32 * volatile *var_base;
    s32 * volatile *var_a1;
    s32 * volatile *var_a2;
    s32 *temp_v1;
    s32 temp_a0;
    s32 var_a3;
    u16 temp_a1;
    ValueLink *right;
    ValueLink *left;
    HalfValue *right_value;
    HalfValue *left_value;

    var_a3 = 2;
    var_base = D_80129728;
    var_a1 = var_base + 0x10;
    var_a2 = var_base + 2;
    do {
        temp_v1 = *var_a2;
        var_a2 += 1;
        temp_a0 = *temp_v1;
        var_a3 += 1;
        *temp_v1 = **var_a1;
        **var_a1 = temp_a0;
        var_a1 += 1;
    } while (var_a3 < 0xE);
    right = (ValueLink *) D_80129728[22];
    left = (ValueLink *) D_80129728[8];
    right_value = right->next;
    left_value = left->next;
    temp_a1 = left_value->value;
    left_value->value = right_value->value;
    ((ValueLink *) D_80129728[22])->next->value = temp_a1;
    arg0->unk_16 = (s8) (arg0->unk_16 ^ 1);
    func_801237A4(arg0, temp_a1, var_a2, var_a3);
}
