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

M2C_UNK func_807001B4();
M2C_UNK func_80700244();
s32 func_8070042C();
M2C_UNK func_80700488();
M2C_UNK func_807008D0();
extern u8 D_A0700000[];
extern u8 D_A0700120[];
extern u8 D_A0700134[];

s32 func_808B94E0(void) {
    s32 *held = (s32 *)(D_A0700000 + 0xB40);

    func_807001B4(*held);
    func_80700244(0);
    func_80700488();
    *(s32 *)(D_A0700000 + 0x9D4) = func_8070042C();
    M2C_FIELD(*(void **)(D_A0700000 + 0xB50), M2C_UNK (**)(M2C_UNK, M2C_UNK, M2C_UNK), 0x64)(
        (s32)D_A0700120, (s32)D_A0700134, 0xC9);
    M2C_FIELD(*(s32 *)(D_A0700000 + 0xB50), M2C_UNK (**)(M2C_UNK), 0x6C)(0);
    func_807001B4(*held);
    func_807008D0(*(s32 *)(D_A0700000 + 0x9D4), *(s32 *)(D_A0700000 + 0x9D8));
    return *(s32 *)(D_A0700000 + 0x9D4);
}
