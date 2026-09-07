/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

typedef s32 (*Callback)(void *, s32);
typedef struct {
    Callback callback;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} CallbackEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800167B4();
extern s32 func_80016D78();
extern s16 D_800160B2[8];

s32 func_80016818(void *arg0) {
    s32 var_s0;

    if ((((s32) M2C_FIELD(arg0, s32 *, 0) >> 0x17) & 1) ||
        (func_80016D78(D_800160B2[0]) == 0)) {
        func_800167B4(M2C_FIELD(arg0, s32 *, 0x14),
                      M2C_FIELD(arg0, s16 *, 0x1A));
    }
    var_s0 = 0;
    
    while (M2C_FIELD(arg0, CallbackEntry **, 0x10)[var_s0].callback(arg0, var_s0) != 0) {
        var_s0++;
    }
    return var_s0;
}
