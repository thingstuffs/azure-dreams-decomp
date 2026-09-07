#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A0F10();                                /* extern */
s32 func_8009F9A4();                                /* extern */
M2C_UNK func_8009A8EC();                            /* extern */
M2C_UNK func_800A0CA8();                            /* extern */
M2C_UNK func_8009A99C();                            /* extern */
extern M2C_UNK D_800A0CF8;
extern M2C_UNK D_800A0CC0;

void func_800A0C30(void *arg0, void *arg1, void *arg2) {
    if (func_800A0F10() != 0) {
        if (func_8009F9A4() < 6) {
            M2C_FIELD(arg0, s16 *, 0x90) = 6;
            M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800A0CF8;
            func_8009A8EC(M2C_FIELD(arg0, s16 *, 0x72), M2C_FIELD(arg2, s16 *, 2), M2C_FIELD(arg2, s16 *, 6));
            func_800A0CA8();
            return;
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800A0CC0;
        func_8009A99C(M2C_FIELD(arg0, s16 *, 0x72));
    }
}
