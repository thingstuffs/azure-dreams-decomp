/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef s32 (*Callback)(void *, s32);
typedef struct {
    Callback callback;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} CallbackEntry;

extern s32 check_initial_query_zero_secondary();
extern s32 select_data_array_based_flag();
extern s16 D_800160B2[8];

typedef struct S_80016818_0 {
    s32 unk_00;
    u8 pad_04[0xC];
    CallbackEntry * unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
} S_80016818_0;   /* arg0 in run_flag_test_callbacks */

/* Run callbacks until one returns zero, then return its index. */
s32 run_flag_test_callbacks(S_80016818_0 *context) {
    s32 callback_index;

    if ((((s32) context->unk_00 >> 0x17) & 1) ||
        (select_data_array_based_flag((*(__typeof__(D_800160B2) *)0x800160B2)[0]) == 0)) {
        check_initial_query_zero_secondary(context->unk_14,
                      context->unk_1A);
    }
    callback_index = 0;

    while (context->unk_10[callback_index].callback(context, callback_index) != 0) {
        callback_index++;
    }
    return callback_index;
}
