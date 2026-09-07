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

struct PackedTownEntry {
    s32 word0;
    s32 word4;
    s8 byte8;
    s8 byte9;
} __attribute__((packed));

struct TownCopy84 {
    s32 words[21];
};

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();                   /* extern */
void *func_8003C06C();               /* extern */
M2C_UNK func_8003E188();        /* extern */
M2C_UNK func_800422DC();            /* extern */
M2C_UNK func_800423C0();      /* extern */
M2C_UNK func_80042640();               /* extern */
M2C_UNK memset(); /* extern */
M2C_UNK func_8009DC8C();    /* extern */
extern M2C_UNK D_80010A80;
extern M2C_UNK D_80010AB4;
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009F374;
extern M2C_UNK D_80100A10;
extern struct TownCopy84 D_80100AF8;
extern u8 D_80010000[];

void func_8009F4C0(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    void *var_s1;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s5;
    register s32 temp_s3;
    void *temp_v0;
    void *temp_v1;
    void *temp_v2;
    register void *baseD ASM_REG("$6");

    temp_s5 = M2C_FIELD(arg0, u8 *, 0x95);
    func_80033CD8(arg0, &D_80045340);
    temp_v2 = (temp_s5 * 4) + 0x80010000;
    M2C_FIELD(temp_v2, s8 *, 0x981) = 0x13;
    memset(&D_80100A10, 0, 0x54);
    func_80042640(&D_80100A10, M2C_FIELD(arg0, u8 *, 0x4C));
    temp_s3 = temp_s5;
    func_800423C0(&D_80100A10, M2C_FIELD(arg0, u8 *, 0x4C), 0);
    func_800422DC(&D_80100AF8, &D_80100A10);
    *(struct TownCopy84 *)((u8 *)0x80010A80 + (temp_s3 * 0x54)) = D_80100AF8;
    var_s1 = (void *) 0x80010AB4;
    temp_s0 = temp_s3 * 0x54;
    var_s1 = (u8 *)var_s1 + temp_s0;
    temp_v0 = func_8003C06C(M2C_FIELD(arg0, u8 *, 0x4C));
    *(struct PackedTownEntry *)var_s1 = *(struct PackedTownEntry *)temp_v0;
    baseD = (void *) 0x80010000;
    temp_v1 = (temp_s5 * 4) + (u8 *)baseD;
    M2C_FIELD(temp_v1, u8 *, 0x983) = (u8) ((M2C_FIELD(temp_v1, u8 *, 0x983) & 0xC0) | temp_s3);
    M2C_FIELD((temp_s0 + (u8 *)baseD), u8 *, 0xAC3) = temp_s5;
    M2C_FIELD(arg0, u8 *, 0x4D) = (u8) M2C_FIELD(temp_v1, u8 *, 0x981);
    M2C_FIELD(arg0, u8 *, 0x4F) = (u8) M2C_FIELD(temp_v1, u8 *, 0x983);
    temp_s3 = (u8) (M2C_FIELD(((M2C_FIELD(arg0, u8 *, 0x95) * 4) + (u8 *)baseD), u8 *, 0x983) & 0x3F);
    temp_s0_2 = M2C_FIELD(((temp_s3 * 0x54) + (u8 *)baseD), s32 *, 0xA94);
    func_8003E188(M2C_FIELD(arg0, u8 *, 0x4C), 1, baseD);
    func_8009DC8C(arg0, arg3, M2C_FIELD(arg0, u8 *, 0x4C), temp_s0_2);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_8009F374;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0xA;
}
