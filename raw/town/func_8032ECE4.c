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

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef void (*Callback3)(M2C_UNK *, M2C_UNK *, M2C_UNK);

__asm__(".set D_80010000, 0x80010000");
extern s8 D_80010000[];
extern M2C_UNK D_80016064;
extern M2C_UNK D_8001608C;

s32 func_800194E4(void *arg0, s32 arg1) {
    s32 var_s1;
    Callback3 callback;
    void *root;
    void *callbacks;

    var_s1 = 0;
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
loop_2:
        if (M2C_FIELD((s8 *)arg0 + var_s1 * 8, s16 *, 0) != arg1) {
            var_s1 += 1;
            if (M2C_FIELD((s8 *)arg0 + var_s1 * 8, s32 *, 4) != 0) {
                goto loop_2;
            }
        }
        if (M2C_FIELD((s8 *)arg0 + var_s1 * 8, s32 *, 4) == 0) {
            goto block_5;
        }
    } else {
block_5:
        do { root = M2C_FIELD(D_80010000, void **, 0x6000); } while (0);
        do { callbacks = M2C_FIELD(root, void **, 0x20); } while (0);
        callback = M2C_FIELD(callbacks, Callback3 *, 0x168);
        callback(&D_80016064, &D_8001608C, 0x28);
        M2C_FIELD(M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
    }
    return var_s1;
}
