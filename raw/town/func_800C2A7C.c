#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FE78();
extern M2C_UNK func_8008EF58();
extern M2C_UNK func_8008F01C();
extern M2C_UNK func_8008FCE0();
extern M2C_UNK func_8008FD48();
extern M2C_UNK func_8009550C();
extern s16 func_800C2AE8();

extern M2C_UNK D_8006ADBC;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800C02C4;
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800D0420;
extern s32 D_800D0438;
extern M2C_UNK D_800FE490;

void func_800C01DC(void) {
    void *temp_v0;

    D_800D0438 = 0;
    temp_v0 = func_8003FE78(0, &D_80083498, 0x22);
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800C02C4;
    M2C_FIELD(temp_v0, M2C_UNK **, 0xC) = &D_80082E80;
    M2C_FIELD(temp_v0, M2C_UNK **, 8) = &D_80083780;
    func_8008EF58();
    func_8008F01C(&D_800CFCB4, &D_80083780, &D_800D0420);
    func_8008FCE0();
    func_8008FD48(&D_800FE490, &D_80083780, &D_800D0420);
    {
        register s8 *base ASM_REG("$4");
        u16 *ptr10;

        base = (s8 *) &D_8006ADBC;
        ptr10 = M2C_FIELD(base, u16 **, 0x10);
        M2C_FIELD(&D_80083780, s16 *, 2) = (s16) (M2C_FIELD(base, u16 *, 0x14) + ptr10[0]);
        M2C_FIELD(&D_80083780, s16 *, 6) = (s16) (M2C_FIELD(base, u16 *, 0x16) + ptr10[1]);
        M2C_FIELD(&D_80083780, s16 *, 0xA) = func_800C2AE8(&D_80083780, ptr10);
    }
    func_8009550C(&D_80083780);
}
