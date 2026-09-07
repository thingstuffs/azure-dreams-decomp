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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern void *D_80088A10[];
void func_80040AA0();
void func_80041094();
s32 func_800429E4();
void func_80043568();
void func_800481E0();
M2C_UNK func_800945E8();
M2C_UNK func_800948BC();
M2C_UNK func_800A56E0();
s32 func_800A613C();
M2C_UNK func_800A6780();
void func_800B2074();
M2C_UNK func_800C542C();
extern s32 D_80010234;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} __attribute__((packed)) UnalignedCopy3;
extern UnalignedCopy3 D_80012080;
extern UnalignedCopy3 D_80013710;
extern M2C_UNK D_80013714;
extern M2C_UNK D_80021268;
extern u16 D_8008146C;
extern u8 D_80082E6B;
extern u16 D_80082E76;
extern s32 D_80082EB8;
extern M2C_UNK D_80083160;
extern s16 D_800DCED4[];
extern s32 D_800DCF64;
extern M2C_UNK D_800E296C;
extern M2C_UNK D_800E3CD0;
extern M2C_UNK D_800E4938;

void func_800930F0(void *arg0, s32 arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17 };
    M2C_UNK *var_v0;
    M2C_UNK *var_v1;
    u8 *var_s0;
    register s32 *var_s2 ASM_REG("$18");
    register s32 var_s1 ASM_REG("$17");
    s32 temp_s0;
    s32 temp_v0_2;
    u16 temp_v0;
    u8 temp_v1;
    void *temp_v0_3;
    s16 *var_s4;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 0x12U) {
        goto block_25;
    }
    (void)jt_keep; goto *D_80088A10[(u32)(temp_v1)];
jt_c0:
    var_s1 = 1;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    func_800B2074((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20);
    var_s4 = &D_800DCED4;
    var_s2 = (s32 *)arg0 + 1;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
    do {
        temp_s0 = M2C_FIELD(var_s2, s32 *, 0xAC);
        if (temp_s0 != 0) {
            func_800C542C(temp_s0, var_s4[func_800429E4(temp_s0)], (s16)var_s1, 0);
        }
        var_s1 -= 1;
        var_s2 -= 1;
    } while (var_s1 >= 0);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c1:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((s16) temp_v0 < 0x3D) {
        goto block_26;
    }
    var_v1 = (M2C_UNK *)0x800E0000;
    var_s0 = (u8 *)0x80010000;
    if (M2C_FIELD(var_s0, u16 *, 0x3714) & 4) {
        goto block_21;
    }
    func_800945E8(arg0);
    func_800948BC();
    ASM_KEEP(var_s0);
    {
        register UnalignedCopy3 *copy_src ASM_REG("$5");
        register UnalignedCopy3 *copy_dst ASM_REG("$4");
        register s32 copy_v0 ASM_REG("$2");
        register s32 copy_v1 ASM_REG("$3");

        copy_src = (UnalignedCopy3 *)0x80013710;
        copy_dst = (UnalignedCopy3 *)0x80012080;
        ASM_KEEP(copy_dst);
        copy_v0 = copy_src->unk0;
        copy_v1 = copy_src->unk4;
        copy_dst->unk0 = copy_v0;
        copy_dst->unk4 = copy_v1;
        copy_v0 = copy_src->unk8;
        copy_dst->unk8 = copy_v0;
        ASM_MEM_BARRIER();
        M2C_FIELD(var_s0, s16 *, 0x3714) = 0;
        M2C_FIELD(var_s0, s16 *, 0x3716) = 0;
        M2C_FIELD(var_s0, s16 *, 0x3718) = 0;
        M2C_FIELD(var_s0, s16 *, 0x371A) = 0;
        func_800A6780(copy_dst, copy_src);
    }
    if (M2C_FIELD(var_s0, s32 *, 0x2090) == 0) {
        goto block_12;
    }
    if (M2C_FIELD(var_s0, s32 *, 0x2090) != 1) {
        goto block_12;
    }
    M2C_FIELD(var_s0, s32 *, 0x234) = (s32) (M2C_FIELD(var_s0, s32 *, 0x234) + 1);
    func_80043568();
    M2C_FIELD(var_s0, s32 *, 0x2090) = 0;
    goto block_13;
block_12:
    M2C_FIELD(var_s0, s32 *, 0x234) = (s32) (M2C_FIELD(var_s0, s32 *, 0x234) + 1);
block_13:
    func_800A56E0(0x514);
    M2C_FIELD(&D_800E4938, M2C_UNK **, 0) = &D_80021268;
    D_80082EB8 = 0;
    (*(s32 *)&D_800E296C) = (s32) (M2C_FIELD(&D_800E296C, s32 *, 0) | 0x2000);
    goto block_24;
jt_c2:
    temp_v0_2 = func_800A613C();
    D_800DCF64 = temp_v0_2;
    if (temp_v0_2 == 0) {
        goto block_25;
    }
    goto block_24;
jt_c3:
    temp_v0_3 = M2C_FIELD(&D_800E4938, void *(**)(s32, s32), 0)(M2C_FIELD(&D_800E4938, s32 *, 4), M2C_FIELD(&D_800E4938, s32 *, 8));
    M2C_FIELD(arg0, void **, 0xC8) = temp_v0_3;
    if (temp_v0_3 == NULL) {
        goto block_27;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c4:
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), u16 *, 0x1E) & 0x8000)) {
        goto block_25;
    }
    func_80040AA0(D_80082E6B);
    D_8008146C = *(u16 *)0x80010234;
    func_800481E0();
    goto block_24;
jt_c16:
    var_v1 = (M2C_UNK *)0x800E0000;
    if (!(M2C_FIELD(&D_80013714, u16 *, 0) & 4)) {
        goto block_23;
    }
block_21:
    if (M2C_FIELD(var_v1, u8 *, 0x3CD0) != 0) {
        goto block_26;
    }
    M2C_FIELD(var_v1, s8 *, 0x3CD0) = 1;
    func_80040AA0(3U);
    goto block_26;
block_23:
    func_800945E8(arg0);
    func_800948BC();
    {
        register s32 call_a0 ASM_REG("$4");
        register s32 call_a1 ASM_REG("$5");
        register s32 call_a2 ASM_REG("$6");
        register s32 call_a3 ASM_REG("$7");
        register u8 *store_base ASM_REG("$3");
        register u16 store_value ASM_REG("$2");

        call_a0 = 6;
        call_a1 = 0;
        call_a2 = call_a1;
        call_a3 = call_a1;
        ASM_KEEP4_NV(call_a0, call_a1, call_a2, call_a3);
        store_base = (u8 *)0x80080000;
        ASM_KEEP(store_base);
        store_value = 0x8000;
        M2C_FIELD(store_base, u16 *, 0x2E76) = store_value;
        func_80041094(call_a0, call_a1, call_a2, call_a3, 0x8000);
    }
block_24:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c17:
block_25:
    goto block_26;
block_26:
    var_v0 = &D_80083160;
    M2C_FIELD(var_v0, s32 *, 0xCC) = 0;
    M2C_FIELD(var_v0, s32 *, 0x154) = 0;
    (*(s32 *)&D_800E296C) = (s32) (M2C_FIELD(&D_800E296C, s32 *, 0) | 0x40000);
block_27:
    return;
}
