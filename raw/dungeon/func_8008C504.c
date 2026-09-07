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

extern void *D_800889A8[];
void func_80048A44();
s32 func_800644B8();
s32 func_80064584();
M2C_UNK func_800A2B04();
M2C_UNK func_800A56E0();
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_8008EAC8;
extern u8 D_800DD038[];
extern u8 D_800DD058[];

void func_80091C64(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK *var_v0;
    M2C_UNK *var_v1;
    s16 temp_a0;
    u8 temp_v1;
    register u8 temp_state ASM_REG("$2");
    register u16 temp_duration ASM_REG("$3");
    s32 temp_byte;
    s32 temp_coord;
    register s32 temp_y_work ASM_REG("$2");
    register s32 temp_y_num ASM_REG("$3");
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 5U) {
        goto block_19;
    }
    (void)jt_keep; goto *D_800889A8[(u32)(temp_v1)];
jt_c0:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((s16) temp_v0 >= 9) {
        goto block_19;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD038;
    func_80048A44(arg2, D_800DD038[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0xC);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A56E0(0x701);
    return;
jt_c1:
    if (M2C_FIELD(arg0, s16 *, 0x96) == 0) {
        goto block_6;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + (func_80064584(M2C_FIELD(arg3, s16 *, 0x2A) + 0x400) << 6));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (func_800644B8(M2C_FIELD(arg3, s16 *, 0x2A) + 0x400) << 6));
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((s32) (0 - func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x96) << 8)) >> 8);
block_6:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_19;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD058;
    func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    temp_state = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, s16 *, 0x92) = 0;
    goto block_10;
jt_c2:
    if (D_8008346C != 0) {
        goto block_19;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD038;
    func_80048A44(arg2, D_800DD038[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    temp_state = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_duration = 8U;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_duration;
block_10:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (temp_state + 1);
    return;
jt_c3:
    temp_a0 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
    if (temp_a0 == 0) {
        goto block_13;
    }
    temp_byte = M2C_FIELD(arg2, u8 *, 0x24) << 6;
    temp_coord = M2C_FIELD(arg1, s16 *, 2) - 0x20;
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + ((temp_byte - temp_coord) << 0x10) / temp_a0);
    temp_y_num = M2C_FIELD(arg2, u8 *, 0x25);
    ASM_SCHED_BARRIER();
    temp_y_work = M2C_FIELD(arg1, s16 *, 6);
    temp_y_num <<= 6;
    ASM_SCHED_BARRIER();
    temp_y_work -= 0x20;
    temp_y_num = (temp_y_num - temp_y_work) << 0x10;
    temp_y_work = M2C_FIELD(arg0, s16 *, 0x96);
    temp_y_num /= temp_y_work;
    temp_y_work = M2C_FIELD(arg1, s32 *, 4) + temp_y_num;
    M2C_FIELD(arg1, s32 *, 4) = temp_y_work;
    M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((s32) (0 - func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x96) << 8)) >> 8);
block_13:
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_19;
    }
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg0, s16 *, 0x92) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD058;
    func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    return;
jt_c4:
    var_v1 = &D_80083460;
    M2C_FIELD(var_v1, u16 *, 0xA) = (u16) (M2C_FIELD(var_v1, u16 *, 0xA) - 1);
    M2C_FIELD(arg3, s16 *, 0x2A) = (s16) M2C_FIELD(arg0, u16 *, 0x11A);
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x100000)) {
        goto block_17;
    }
    var_v0 = &D_8008EAC8;
    goto block_18;
block_17:
    var_v0 = &D_8008ACDC;
block_18:
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = var_v0;
    M2C_FIELD(arg3, s32 *, 0x14) = (s32) (M2C_FIELD(arg3, s32 *, 0x14) & 0xFFFDFFFF);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) | 0x10);
block_19:
    return;
}
