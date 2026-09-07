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

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80082E80[];
extern u8 D_80174C84[];
extern s16 D_80083228[5];
extern void *D_80174CE0[];
void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A152C();
M2C_UNK func_800A9C18();
M2C_UNK func_80047784();
M2C_UNK func_80172A14();
extern M2C_UNK D_801730AC;

void func_80173F6C(void) {
    M2C_UNK var_a2;
    void *temp_s0;
    void *temp_s1;
    void *temp_s3;
    void *temp_v0;
    u8 *temp_v1;
    u16 temp_v2;

    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_s1, s8 *, 0x13) = 0x18;
        M2C_FIELD(temp_s1, s8 *, 0x9A) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x96) = 0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801730AC;
        func_8004491C(temp_v0, D_80045340);
        temp_v1 = D_80082E80;
        temp_s3 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s3, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(D_80083498, void **, 8), u16 *, 0xA);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0x24) = (u8) (temp_v1[0x24] + 9);
        M2C_FIELD(temp_s0, u8 *, 0x25) = (u8) (temp_v1[0x25] - 9);
        M2C_FIELD(temp_s0, u8 **, 0x2C) = D_80174C84;
        func_800A9C18(temp_v0, temp_s3, temp_s0, 0);
        M2C_FIELD(temp_s1, s8 *, 0xB6) = 1;
        M2C_FIELD(temp_s1, s16 *, 0x2A) = 0x800;
        func_80047784(temp_s0, M2C_FIELD(temp_s0, u8 **, 0x2C)[((s32) (*D_80083228 + 0x900) >> 9) & 7], 0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        func_8009A3D0(M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25),
                      (M2C_FIELD(temp_s1, s32 *, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        func_8009A028(temp_s1);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (M2C_UNK *) ((s32) M2C_FIELD(temp_v0, M2C_UNK **, 0x10) | 0x80000000);
        func_80172A14(temp_s1, temp_s3, temp_s0);
        temp_v2 = M2C_FIELD(temp_s0, u16 *, 0x14);
        *D_80174CE0 = temp_v0;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (temp_v2 | 0x80);
        func_800A152C(0x18, 1);
    }
}
