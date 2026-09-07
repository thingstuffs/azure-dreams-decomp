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

extern void *D_80024020[];
M2C_UNK func_8002403C();
s32 func_800243B8();
s32 func_8003DE58();
s32 func_800A44E0();
M2C_UNK func_800A56E0();
s16 func_800BCB04();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_8006CCD8_2[] __asm__("D_8006CCD8");
extern u16 D_8006CCE8_2[] __asm__("D_8006CCE8");
extern s16 D_8006CCD8_3[] __asm__("D_8006CCD8");
extern s16 D_8006CCE8_3[] __asm__("D_8006CCE8");
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;

typedef struct {
    s32 pos[3];
    u8 pad18[0xC];
    u16 dist[3];
    u8 pad2E[2];
    u16 saved_y;
} Func818AAE60Scratch;

void func_80024660(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    Func818AAE60Scratch scratch;
    s16 *var_a1;
    register s16 *var_a2 ASM_REG("$6");
    register M2C_UNK *var_s3 ASM_REG("$19");
    s16 temp_v0_4;
    s32 temp_v1;
    s16 temp_v1_4;
    s16 temp_v1_7;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1_2;
    register s32 var_v0_5 ASM_REG("$2");
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_7;
    s32 temp_v1_6;
    s32 var_s1;
    register s32 var_v0_2 ASM_REG("$2");
    register s32 var_v0_3 ASM_REG("$3");
    s32 signed_x;
    s32 signed_y;
    u16 temp_v1_3;
    register u16 var_v0 ASM_REG("$2");
    void *temp_a1;
    register void *temp_s0 ASM_REG("$16");
    register void *temp_s7 ASM_REG("$23");
    void *temp_v0;
    void *temp_v1_2;
    void *temp_v1_5;
    register void *var_s0 ASM_REG("$16");
    u16 cnt;

    cnt = M2C_FIELD(arg0, u16 *, 0x10);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    temp_s7 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, u16 *, 0x10) = cnt + 1;
    if ((u32) temp_v1 >= 7U) {
        goto block_52;
    }
    (void)jt_keep; goto *D_80024020[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) (((u16) M2C_FIELD(temp_s7, u16 *, 0x2A) >> 9) & 7);
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
jt_c1:
    temp_s0 = temp_s7 - 0x20;
    temp_a1 = M2C_FIELD(temp_s0, void **, 0xC);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &scratch.dist[0], 0) != 0) {
        goto block_5;
    }
    if (!(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x14) & 0x8000)) {
        goto block_52;
    }
block_5:
    temp_v1_2 = M2C_FIELD(temp_s0, void **, 8);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_v1_2, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_v1_2, u16 *, 6);
    temp_v1_3 = M2C_FIELD(temp_v1_2, u16 *, 0xA);
    M2C_FIELD(arg1, u16 *, 0xA) = temp_v1_3;
    if (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x14) & 0x8000) {
        goto block_7;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + scratch.dist[0]);
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + scratch.dist[1]);
    ASM_SCHED_BARRIER();
    var_v0 = M2C_FIELD(arg1, u16 *, 0xA);
    ASM_KEEP(var_v0);
    {
        register u16 temp_d2 ASM_REG("$3");
        temp_d2 = scratch.dist[2];
        var_v0 = var_v0 + temp_d2;
    }
    goto block_8;
block_7:
    var_v0 = temp_v1_3 - 0x40;
block_8:
    M2C_FIELD(arg1, u16 *, 0xA) = var_v0;
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_52;
    }
    temp_v0 = M2C_FIELD(temp_s7, void **, 0x60);
    var_s1 = 1;
    if (temp_v0 != NULL) {
    var_s3 = M2C_FIELD(temp_v0, M2C_UNK **, -0x18);
    var_a0 = M2C_FIELD(var_s3, s16 *, 2);
    var_a0 -= M2C_FIELD(arg1, s16 *, 2);
    if (var_a0 >= 0) {
        goto block_12;
    }
    var_a0 = 0 - var_a0;
block_12:
    scratch.dist[0] = (u16) var_a0;
    var_v0_2 = M2C_FIELD(var_s3, s16 *, 6);
    var_v0_3 = M2C_FIELD(arg1, s16 *, 6);
    ASM_SCHED_BARRIER();
    var_a1 = (s16 *)((u8 *)&scratch + 2);
    ASM_SCHED_BARRIER();
    var_v0_2 -= var_v0_3;
    if (var_v0_2 >= 0) {
        goto block_14;
    }
    var_v0_2 = 0 - var_v0_2;
block_14:
    scratch.dist[1] = (u16) var_v0_2;
    var_v0_3 = M2C_FIELD(arg1, s16 *, 0xA);
    var_v0_3 += 0x20;
    var_v0_2 = M2C_FIELD(var_s3, s16 *, 0xA) - var_v0_3;
    if (var_v0_2 >= 0) {
        goto block_16;
    }
    var_v0_2 = 0 - var_v0_2;
block_16:
    scratch.dist[2] = (u16) var_v0_2;
    M2C_FIELD(arg0, s16 *, 0x12) = var_a0;
loop_17:
    if (var_a1[12] <= M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_19;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) (u16) var_a1[12];
block_19:
    var_s1 += 1;
    var_a1 += 1;
    if (var_s1 < 3) {
        goto loop_17;
    }
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x12) << 0x10;
    temp_v1_4 = (temp_v0_2 >> 0x14) + (temp_v0_2 >> 0x15);
    M2C_FIELD(arg0, s16 *, 0x12) = temp_v1_4;
    if (temp_v1_4 != 0) {
        goto block_22;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 1;
block_22:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (M2C_FIELD(var_s3, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(var_s3, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) (M2C_FIELD(var_s3, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    func_800A56E0(0x300, var_a1);
    var_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xA) + 1;
    goto block_41;
    } else {
    register s32 temp_a1_3 ASM_REG("$5");
    register s32 temp_a0 ASM_REG("$4");
    register u16 saved_y_t0 ASM_REG("$8");
    register u16 *tptr ASM_REG("$8");
    register u16 *first_ptr ASM_REG("$3");
    register s32 search_z ASM_REG("$6");
    register u32 dead_page ASM_REG("$2");
    s32 var_fp;
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s6 ASM_REG("$22");
    var_s1 = 0;
    temp_v1_5 = M2C_FIELD(temp_s0, void **, 0xC);
    ASM_KEEP(temp_v1_5);
    dead_page = 0x80070000;
    ASM_USE(dead_page);
    var_s4 = M2C_FIELD(temp_v1_5, u8 *, 0x24);
    var_s6 = M2C_FIELD(temp_v1_5, u8 *, 0x25);
    var_fp = var_s4;
    ASM_KEEP(var_fp);
    scratch.saved_y = (u16) var_s6;
    do {
    signed_x = (s16)var_s4;
    signed_y = (s16)var_s6;
    if ((func_800A44E0((signed_x << 6) & 0xFFC0, (signed_y << 6) & 0xFFC0, M2C_FIELD(temp_s7, s16 *, 0x88), (s16) (M2C_FIELD(arg0, u16 *, 0xE) << 9)) << 0x10) != 0) {
        break;
    }
    temp_v0_3 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    tptr = D_8006CCD8;
    first_ptr = &tptr[temp_v0_3];
    search_z = (u16) M2C_FIELD(temp_s7, s16 *, 0x88);
    ASM_KEEP_DEP_NV(search_z, first_ptr);
    search_z = (s16) (search_z - 32);
    ASM_KEEP(search_z);
    tptr = D_8006CCE8;
    temp_a0 = *first_ptr;
    temp_a1_3 = tptr[temp_v0_3];
    temp_a0 = (((signed_x + (s16)temp_a0) << 6) + 32) & 0xFFE0;
    temp_a1_3 = (((signed_y + (s16)temp_a1_3) << 6) + 32) & 0xFFE0;
    temp_v0_4 = func_800BCB04(temp_a0, temp_a1_3, search_z);
    if (temp_v0_4 >= 513) {
        break;
    }
    if ((s16) (temp_v0_4 - (u16) M2C_FIELD(temp_s7, s16 *, 0x88)) < -63) {
        break;
    }
    {
        register s32 next_x ASM_REG("$4");
        register s32 next_y ASM_REG("$2");
        register s32 update_idx ASM_REG("$3");
        register u16 *update_xp ASM_REG("$2");
        register u16 *update_yp ASM_REG("$3");
        tptr = D_8006CCD8_2;
        ASM_KEEP(tptr);
        update_idx = (s16) M2C_FIELD(arg0, u16 *, 0xE);
        var_s1 += 1;
        update_xp = (u16 *) (((unsigned long) update_idx << 1) + (unsigned long) tptr);
        tptr = D_8006CCE8_2;
        update_yp = update_idx + tptr;
        next_x = *update_xp;
        next_y = *update_yp;
        next_x = var_s4 + next_x;
        var_s4 = next_x;
        ASM_KEEP(var_s4);
        next_y = var_s6 + next_y;
        var_s6 = next_y;
        ASM_KEEP(var_s6);
        scratch.saved_y = (u16) next_y;
        var_fp = next_x;
    }
    } while (var_s1 < 8);
block_28:
    ASM_SCHED_BARRIER();
    var_s3 = (M2C_UNK *)&scratch;
    var_s1 = 1;
    ASM_KEEP(var_s1);
    {
        register s16 *tptr3 ASM_REG("$3");
        temp_a1_3 = var_fp << 16;
        ASM_KEEP(temp_a1_3);
        tptr3 = D_8006CCD8_3;
        ASM_KEEP(tptr3);
        temp_a1_3 >>= 10;
        ASM_KEEP(temp_a1_3);
        var_a2 = (s16 *)((u8 *)&scratch + 2);
        temp_a1_3 += ((tptr3[(s16) M2C_FIELD(arg0, u16 *, 0xE)] + 1) << 5);
        tptr3 = D_8006CCE8_3;
        M2C_FIELD(var_s3, s16 *, 2) = temp_a1_3;
        temp_a1_3 = (s16) temp_a1_3;
        saved_y_t0 = scratch.saved_y;
        ASM_KEEP(saved_y_t0);
        temp_a0 = ((s32) (saved_y_t0 << 0x10));
        temp_a0 = (temp_a0 >> 0xA) + ((tptr3[(s16) M2C_FIELD(arg0, u16 *, 0xE)] + 1) << 5);
        M2C_FIELD(var_s3, s16 *, 6) = temp_a0;
        var_v0 = M2C_FIELD(arg1, u16 *, 0xA) + 32;
        temp_a0 <<= 16;
        M2C_FIELD(var_s3, s16 *, 10) = var_v0;
        temp_v1_6 = M2C_FIELD(arg1, s16 *, 2);
        temp_a0 >>= 16;
        var_a1_2 = temp_a1_3 - temp_v1_6;
        ASM_SCHED_BARRIER();
        if (var_a1_2 >= 0) {
            goto block_30;
        }
        var_a1_2 = 0 - var_a1_2;
    block_30:
        scratch.dist[0] = var_a1_2;
        var_v0_5 = var_v0 << 16;
        var_a0_2 = temp_a0 - M2C_FIELD(arg1, s16 *, 6);
        ASM_SCHED_BARRIER();
        if (var_a0_2 >= 0) {
            goto block_32;
        }
        var_a0_2 = 0 - var_a0_2;
    block_32:
        scratch.dist[1] = var_a0_2;
        var_v0_5 >>= 16;
        var_v0_5 -= M2C_FIELD(arg1, s16 *, 10);
        if (var_v0_5 >= 0) {
            goto block_34;
        }
        var_v0_5 = 0 - var_v0_5;
    block_34:
        scratch.dist[2] = var_v0_5;
        M2C_FIELD(arg0, s16 *, 0x12) = var_a1_2;
    }
loop_35:
    if (var_a2[12] <= M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_37;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) (u16) var_a2[12];
block_37:
    var_s1 += 1;
    var_a2 += 1;
    if (var_s1 < 3) {
        goto loop_35;
    }
    temp_v0_7 = (u16) M2C_FIELD(arg0, s16 *, 0x12) << 0x10;
    temp_v1_7 = (temp_v0_7 >> 0x14) + (temp_v0_7 >> 0x15);
    M2C_FIELD(arg0, s16 *, 0x12) = temp_v1_7;
    if (temp_v1_7 != 0) {
        goto block_40;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 1;
block_40:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (M2C_FIELD(var_s3, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(var_s3, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) (M2C_FIELD(var_s3, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    ASM_SCHED_BARRIER();
    var_v0 = 5;
    }
block_41:
    M2C_FIELD(arg0, s16 *, 0xA) = var_v0;
    var_s1 = 0x1F;
    var_s0 = arg0 + 0x7C;
loop_42:
    M2C_FIELD(var_s0, s32 *, 0x18) = func_800243B8(arg0, arg1, var_s3, (s16)var_s1);
    var_s1 -= 1;
    var_s0 -= 4;
    if (var_s1 >= 0) {
        goto loop_42;
    }
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    goto block_52;
jt_c3:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < 0x28) {
        goto block_52;
    }
    func_8002403C(M2C_FIELD(temp_s7, void **, 0x60), M2C_FIELD(arg0, u8 *, 9), temp_s7);
    goto block_49;
jt_c4:
    if (M2C_FIELD(arg0, s16 *, 0x14) != 0) {
        goto block_52;
    }
    D_8008346C = 0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    goto block_52;
jt_c2:
jt_c5:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_52;
    }
block_49:
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    goto block_52;
jt_c6:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < 0x28) {
        goto block_52;
    }
    M2C_FIELD(arg0, s16 *, 0xA) = 4;
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
block_52:
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    return;
}
