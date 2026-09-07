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

extern M2C_UNK func_800167B4();
extern s32 func_80016D78();
extern s16 D_800160B2[8];

typedef struct S_80016818_0 {
    s32 unk_00;
    u8 pad_04[0xC];
    CallbackEntry * unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
} S_80016818_0;   /* arg0 in func_80016818 */

s32 func_80016818(S_80016818_0 *arg0) {
    s32 var_s0;

    if ((((s32) arg0->unk_00 >> 0x17) & 1) ||
        (func_80016D78(D_800160B2[0]) == 0)) {
        func_800167B4(arg0->unk_14,
                      arg0->unk_1A);
    }
    var_s0 = 0;
    
    while (arg0->unk_10[var_s0].callback(arg0, var_s0) != 0) {
        var_s0++;
    }
    return var_s0;
}
