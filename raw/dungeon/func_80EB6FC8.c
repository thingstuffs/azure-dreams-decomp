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
typedef struct {
    u8 pad_00[0x12];
    u8 type;
    u8 pad_13;
} DungeonEntry;

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

extern void *D_80170838[];
s32 func_8003F270();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0();
M2C_UNK func_800DB2DC();
extern DungeonEntry D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_801711A4;
extern u8 D_8017418C;
extern u8 D_801741B4;
extern u8 D_801741BC;

void func_801727C8(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u8 *var_a1;
    M2C_UNK *var_v0_3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_s5;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v0_3;
    u8 *var_s1;
    s32 temp_v1;
    s32 state_selector;
    void *temp_s6;
    void *temp_s7;
    void *temp_v1_3;
    void *var_v0;

    var_s5 = 0;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0xA4);
    state_selector = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_s6 = temp_v0 + 0x20;
    temp_s7 = temp_v0 + 0x28;
    if (state_selector == 1) {
        goto block_37;
    }
    if ((s32) state_selector >= 2) {
        goto block_4;
    }
    if (state_selector == 0) {
        goto block_7;
    }
    return;
block_4:
    if (state_selector == 2) {
        goto block_40;
    }
    if (state_selector == 3) {
        goto block_45;
    }
    return;
block_7:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000)) {
        goto block_13;
    }
    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0_2 - 1) >= 7U) {
        goto block_21;
    }
    (void)jt_keep; goto *D_80170838[(u32)((temp_v0_2) - 1)];
jt_c7:
    var_s5 = 1;
    goto block_18;
jt_c6:
    var_s5 = 1;
    goto block_19;
jt_c5:
    var_s5 = 1;
    goto block_20;
block_13:
    temp_v1_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if (temp_v1_2 == 2) {
        goto block_19;
    }
    if (temp_v1_2 >= 3) {
        goto block_17;
    }
    var_s1 = NULL;
    if (temp_v1_2 == 1) {
        goto block_20;
    }
    goto block_22;
block_17:
    var_s1 = NULL;
    if (temp_v1_2 != 3) {
        goto block_22;
    }
jt_c3:
block_18:
    var_s1 = arg3 + 0xE;
    goto block_22;
jt_c2:
block_19:
    var_s1 = arg3 + 0xB;
    goto block_22;
jt_c1:
block_20:
    var_s1 = arg3 + 8;
    goto block_22;
jt_c4:
block_21:
    var_s1 = NULL;
block_22:
    if (*var_s1 == 0) {
        goto block_36;
    }
    *(volatile u16 *)((s8 *)arg0 + 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
    {
        register s32 special_test ASM_REG("$2");

        ASM_SCHED_BARRIER();
        special_test = var_s5;
        ASM_KEEP(special_test);
        if (special_test == 0) {
            goto block_25;
        }
    }
    var_v0 = D_800814A8;
    M2C_FIELD(arg3, void **, 0x60) = var_v0;
    goto block_27;
block_25:
    if (D_8006DE24[*var_s1].type != 2) {
        goto block_28;
    }
    var_v0 = M2C_FIELD(arg3, void **, 0x60);
    var_a1 = (u8 *)0x80170000;
    if (var_v0 == NULL) {
        goto block_34;
    }
block_27:
    {
        register void *owner ASM_REG("$2") = var_v0;

        temp_v1_3 = M2C_FIELD(owner, void **, -0x14);
        ASM_USE(owner);
        M2C_FIELD(arg3, s8 *, 0x72) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x24);
        M2C_FIELD(arg3, s8 *, 0x73) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x25);
    }
    goto block_33;
block_28:
    {
        void *spawned;

        spawned = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
        M2C_FIELD(arg3, void **, 0x60) = spawned;
        ASM_SCHED_BARRIER();
    }
    var_v0_2 = M2C_FIELD(arg3, s8 *, 0x72);
    var_v1 = M2C_FIELD(arg3, s8 *, 0x73);
    if (var_v0_2 >= 0) {
        goto block_30;
    }
    var_v0_2 = 0 - var_v0_2;
block_30:
    if (var_v1 >= 0) {
        goto block_32;
    }
    var_v1 = 0 - var_v1;
block_32:
    M2C_FIELD(arg3, s8 *, 0x72) = var_v0_2;
    M2C_FIELD(arg3, s8 *, 0x73) = var_v1;
block_33:
    var_a1 = (u8 *)0x80170000;
block_34:
    var_a1 += 0x41B4;
    M2C_FIELD(temp_s6, u16 *, 4) = (u16) (M2C_FIELD(temp_s6, u16 *, 4) & 0x7FFF);
    M2C_FIELD(temp_s7, M2C_UNK **, 0x2C) = var_a1;
    func_80047784(temp_s7, *((u8 *) ((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + (s32) var_a1)), 0);
    if (func_800A94A0(arg3, var_s1, var_s5, arg0 + 0x98) == 0) {
        goto block_54;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    func_800DB2DC(arg1, arg2, arg3, 0xA);
    func_800A56E0(0x703);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    ASM_SCHED_BARRIER();
    {
        register s32 next_state ASM_REG("$3") = 6;

        ASM_KEEP(next_state);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16)next_state;
    }
    goto block_44_increment;
block_36:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    D_8008346C = 0;
    M2C_FIELD(D_800814A8, u16 *, 0xA6) = (u16) (M2C_FIELD(D_800814A8, u16 *, 0xA6) - 1);
    func_800A4ACC(arg3);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801711A4;
    M2C_FIELD(arg3, s8 *, 0x73) = 0;
    M2C_FIELD(arg3, s8 *, 0x72) = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
    return;
block_39:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_40:
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        goto block_42;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_54;
    }
block_42:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_54;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801741BC;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801741BC), 0);
block_44:
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
block_44_increment:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (temp_v1 + 1);
    return;
block_45:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_54;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_8017418C) {
        var_v0_3 = &D_80083460;
        goto block_50;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        goto block_49;
    }
    M2C_FIELD(temp_s6, u16 *, 4) = (u16) (M2C_FIELD(temp_s6, u16 *, 4) | 0x8000);
    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8017418C;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8017418C), 0);
block_49:
    var_v0_3 = &D_80083460;
block_50:
    if (M2C_FIELD(var_v0_3, s32 *, 0xC) != 0) {
        goto block_54;
    }
    M2C_FIELD(var_v0_3, u16 *, 0xA) = (u16) (M2C_FIELD(var_v0_3, u16 *, 0xA) - 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801711A4;
    func_800A4ACC(arg3);
    if ((s8) M2C_FIELD(arg3, u8 *, 0x6D) <= 0) {
        goto block_53;
    }
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
block_53:
    M2C_FIELD(arg3, s8 *, 0x73) = 0;
    M2C_FIELD(arg3, s8 *, 0x72) = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    func_800A56E0(0xB4);
block_54:
    return;
}
