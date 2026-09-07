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

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define MULT_HI(a, b) (0)

void func_8003DB94();
void *func_8003FC64();
void func_800419EC();
M2C_UNK func_8004491C();
M2C_UNK func_800A56E0();
M2C_UNK func_80165018();
M2C_UNK func_80167A98();
extern s32 D_800814A0[3];
extern void *D_800814A8;
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_80166D14;
extern M2C_UNK D_80167C30;
extern PositionTableEntry D_80175DD8[];

void func_80167C74(void *arg0, void *arg1, void *arg2) {
    register void *self ASM_REG("$21") = arg0;
#define arg0 self
    u8 *var_v0;
    register u8 *table_join ASM_REG("$6");
    register u8 *clamp_base ASM_REG("$8");
    register u8 *var_v0_2 ASM_REG("$2");
    s16 *temp_v1_3;
    s16 *temp_v1_4;
    s16 temp_v0_5;
    s16 temp_v1;
    s32 temp_v1_2;
    s32 scaled_z;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    register s32 temp_a0_6 ASM_REG("$4");
    register void *interp_call_a0 ASM_REG("$4");
    register s32 temp_a2_2 ASM_REG("$6");
    register s32 interp_call_a2 ASM_REG("$6");
    s32 temp_a3;
    s32 temp_fp;
    s32 temp_s6;
    s32 temp_s7;
    register s32 object_limit ASM_REG("$23");
    s32 temp_t1_2;
    s32 temp_t2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_4;
    s32 var_a2;
    register s32 var_a2_clamp ASM_REG("$6");
    register s32 var_a2_4 ASM_REG("$6");
    register s32 var_a3 ASM_REG("$7");
    register s32 var_a3_2 ASM_REG("$7");
    register s32 var_s0 ASM_REG("$16");
    register s32 var_s1 ASM_REG("$17");
    register s32 var_s1_2 ASM_REG("$17");
    register s32 var_s1_3 ASM_REG("$17");
    s32 var_s2;
    s32 var_s3;
    register s32 var_s3_2 ASM_REG("$19");
    s32 var_s4;
    register s32 var_s4_2 ASM_REG("$20");
    register s32 var_t1 ASM_REG("$9");
    register s32 var_t0_2 ASM_REG("$8");
    s32 var_t2;
    s32 var_t2_2;
    s32 var_t2_3;
    register s32 var_t3 ASM_REG("$11");
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    register s32 clamp_row ASM_REG("$2");
    register s32 clamp_index ASM_REG("$3");
    register s32 clamp_min ASM_REG("$2");
    u16 *temp_a1_2;
    u16 *var_a2_2;
    u16 *var_a3_3;
    u16 copy_value;
    s16 temp_v0;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_a1_3;
    void *temp_a1_4;
    void *temp_a1_5;
    void *temp_a1_6;
    void *temp_a1_7;
    register u8 *temp_s2 ASM_REG("$18");
    void *temp_t1;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    void *temp_v0_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *table_base;
    register u8 *case_base ASM_REG("$5");
    u8 *interp_base;
    u8 *copy_dst;
    u8 *copy_src;
    register u8 *object_table_base ASM_REG("$5");
    register u8 *object_base ASM_REG("$22");
    void *temp_v1_7;
    register u8 *var_a1_3 ASM_REG("$5");
    register u8 *var_t0 ASM_REG("$8");
    register s32 object_offset ASM_REG("$12");
    register s32 object_copy_index ASM_REG("$2");
    ASM_KEEP(self);

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x12);
    temp_t1 = M2C_FIELD(arg0, void **, 0x24);
    switch (temp_v1) {
    case 0:
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x60);
        var_a2 = 0;
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) ((M2C_FIELD(arg0, s32 *, 0x5C) * 4) / 5);
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x1C);
        M2C_FIELD(arg0, s32 *, 0x60) = (s32) ((temp_a0 * 4) / 5);
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) ((M2C_FIELD(arg0, s32 *, 0x64) * 4) / 5);
        if (temp_v1_2 == 0) var_a2 = 0x46;
        if (temp_v1_2 == 1) var_a2 = 0x32;
        if (temp_v1_2 == 2) var_a2 = 0x1E;
        var_v0 = (u8 *)0x80170000;
        if (var_a2 >= M2C_FIELD(arg0, s16 *, 0x18)) {
            M2C_FIELD(arg0, s16 *, 0x12) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x12) + 1);
            case_base = (u8 *)D_80175DD8;
            M2C_FIELD(arg0, s32 *, 0x68) = (s32) ((s32) ((M2C_FIELD(temp_t1, s32 *, 0) - (M2C_FIELD(arg0, s32 *, 0x5C) * 0x14)) - (M2C_FIELD(arg1, s32 *, 0) + (*(s16 *)(case_base + (M2C_FIELD(arg0, s16 *, 0x1C) * 0x60)) << 0x11))) >> 7);
            M2C_FIELD(arg0, s32 *, 0x6C) = (s32) ((s32) ((M2C_FIELD(temp_t1, s32 *, 4) - (M2C_FIELD(arg0, s32 *, 0x60) * 0x14)) - (M2C_FIELD(arg1, s32 *, 4) + (*(s16 *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + case_base + 2) << 0x11))) >> 7);
            scaled_z = (M2C_FIELD(arg0, s32 *, 0x64) * 0x14) + 0x200000;
            M2C_FIELD(arg0, s32 *, 0x70) = (s32) ((s32) ((M2C_FIELD(temp_t1, s32 *, 8) - scaled_z) - (M2C_FIELD(arg1, s32 *, 8) + (*(s16 *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + case_base + 4) << 0x11))) >> 7);
            M2C_FIELD(arg0, u16 *, 0x1E) = 0U;
            goto block_base;
        }
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x1E) + 1;
        M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0;
        if (temp_v0 == 0xC) {
            func_80167A98(arg0, arg1, arg2);
            M2C_FIELD(D_800814A8, u16 *, 0x10C) = (u16) (M2C_FIELD(D_800814A8, u16 *, 0x10C) | 1);
            M2C_FIELD(D_800814A8, s16 *, 0x6A) = (s16) (M2C_FIELD(D_800814A8, u16 *, 0x2A) + 0x800);
            func_800419EC(6, 0xC, D_800814A8);
            func_800A56E0(0x601);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x1E) >= 0x10) {
            M2C_FIELD(arg0, s16 *, 0x18) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) + M2C_FIELD(arg0, s32 *, 0x68));
        M2C_FIELD(arg0, s32 *, 0x60) = (s32) (M2C_FIELD(arg0, s32 *, 0x60) + M2C_FIELD(arg0, s32 *, 0x6C));
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) (M2C_FIELD(arg0, s32 *, 0x64) + M2C_FIELD(arg0, s32 *, 0x70));
        goto block_base;
    default:
        var_v0 = (u8 *)D_80175DD8;
        goto block_18;
    }

block_base:
    var_v0 = (u8 *)D_80175DD8;
block_18:
    table_join = var_v0;
    var_a0 = M2C_FIELD(arg0, s32 *, 0x5C);
    temp_a1_2 = (u16 *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_join);
    if (var_a0 < 0) var_a0 += 0xFFFF;
    *temp_a1_2 += var_a0 >> 0x10;
    var_a0_2 = M2C_FIELD(arg0, s32 *, 0x60);
    temp_a1_3 = (void *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_join);
    if (var_a0_2 < 0) var_a0_2 += 0xFFFF;
    M2C_FIELD(temp_a1_3, u16 *, 2) = (u16) (M2C_FIELD(temp_a1_3, u16 *, 2) + (var_a0_2 >> 0x10));
    var_a0_3 = M2C_FIELD(arg0, s32 *, 0x64);
    temp_a1_4 = (void *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_join);
    if (var_a0_3 < 0) var_a0_3 += 0xFFFF;
    M2C_FIELD(temp_a1_4, u16 *, 4) = (u16) (M2C_FIELD(temp_a1_4, u16 *, 4) + (var_a0_3 >> 0x10));
    var_a0_4 = M2C_FIELD(arg0, s32 *, 0x5C);
    temp_a1_5 = (void *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_join);
    if (var_a0_4 < 0) var_a0_4 += 0xFFFF;
    M2C_FIELD(temp_a1_5, u16 *, 6) = (u16) (M2C_FIELD(temp_a1_5, u16 *, 6) + (var_a0_4 >> 0x10));
    var_a0_5 = M2C_FIELD(arg0, s32 *, 0x60);
    temp_a1_6 = (void *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_join);
    if (var_a0_5 < 0) var_a0_5 += 0xFFFF;
    M2C_FIELD(temp_a1_6, u16 *, 8) = (u16) (M2C_FIELD(temp_a1_6, u16 *, 8) + (var_a0_5 >> 0x10));
    var_a0_6 = M2C_FIELD(arg0, s32 *, 0x64);
    temp_a1_7 = (void *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_join);
    if (var_a0_6 < 0) var_a0_6 += 0xFFFF;
    var_t2 = 0;
    clamp_base = table_join;
    var_t1 = 0x190;
    var_a3 = var_t2;
    M2C_FIELD(temp_a1_7, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a1_7, u16 *, 0xA) + (var_a0_6 >> 0x10));
    do {
        var_a1 = 0;
        var_a2_clamp = var_a3;
loop_32:
        clamp_row = M2C_FIELD(arg0, s16 *, 0x1C);
        ASM_KEEP_NV(clamp_row);
        temp_a0_2 = var_a1 * 2;
        ASM_KEEP_NV(temp_a0_2);
        clamp_index = clamp_row * 0x60;
        ASM_KEEP_NV(clamp_index);
        clamp_index = clamp_index + (s32)clamp_base;
        ASM_KEEP_NV(clamp_index);
        clamp_index = var_a2_clamp + clamp_index;
        ASM_KEEP_NV(clamp_index);
        clamp_index = temp_a0_2 + clamp_index;
        ASM_KEEP_NV(clamp_index);
        temp_v1_3 = (s16 *)clamp_index;
        if (*temp_v1_3 >= 0x191) *temp_v1_3 = var_t1;
        clamp_row = M2C_FIELD(arg0, s16 *, 0x1C);
        ASM_KEEP_NV(clamp_row);
        clamp_index = clamp_row * 0x60;
        ASM_KEEP_NV(clamp_index);
        clamp_index = clamp_index + (s32)clamp_base;
        ASM_KEEP_NV(clamp_index);
        clamp_index = var_a2_clamp + clamp_index;
        ASM_KEEP_NV(clamp_index);
        clamp_index = temp_a0_2 + clamp_index;
        ASM_KEEP_NV(clamp_index);
        temp_v1_3 = (s16 *)clamp_index;
        if (*temp_v1_3 < -0x190) {
            clamp_min = -0x190;
            ASM_KEEP(clamp_min);
            *temp_v1_3 = clamp_min;
        }
        var_a1 += 1;
        if (var_a1 < 3) goto loop_32;
        var_t2 += 1;
        var_a3 += 6;
    } while (var_t2 < 2);
    var_s1 = 7;
    table_base = (u8 *)D_80175DD8;
    ASM_KEEP(table_base);
    var_t1 = 0x54;
    ASM_KEEP(var_t1);
    do {
        var_t2_2 = 0;
        var_t0_2 = var_t1;
        var_a3_2 = var_t2_2;
loop_40:
        var_a1_2 = 0;
        var_a2_4 = var_a3_2;
loop_41:
        temp_a0_3 = var_a1_2 * 2;
        var_a1_2 += 1;
        temp_v0_2 = (u8 *)(var_t0_2 + ((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)table_base));
        copy_dst = (u8 *)(var_a2_4 + (s32)temp_v0_2);
        temp_v0_2 -= 0xC;
        copy_src = (u8 *)(var_a2_4 + (s32)temp_v0_2);
        copy_value = *(u16 *)(temp_a0_3 + (s32)copy_src);
        temp_a0_3 += (s32)copy_dst;
        *(u16 *)temp_a0_3 = copy_value;
        if (var_a1_2 < 3) goto loop_41;
        var_t2_2 += 1;
        var_a3_2 += 6;
        if (var_t2_2 < 2) goto loop_40;
        var_s1 -= 1;
        var_t1 -= 0xC;
    } while (var_s1 > 0);
    var_s0 = 0xA;
    ASM_KEEP(var_s0);
    interp_base = (u8 *)D_80175DD8;
    temp_v0_3 = (M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + interp_base;
    temp_fp = (M2C_FIELD(temp_v0_3, s16 *, 0) + M2C_FIELD(temp_v0_3, s16 *, 6)) - (M2C_FIELD(temp_v0_3, s16 *, 0x18) + M2C_FIELD(temp_v0_3, s16 *, 0x1E));
    temp_s7 = (M2C_FIELD(temp_v0_3, s16 *, 2) + M2C_FIELD(temp_v0_3, s16 *, 8)) - (M2C_FIELD(temp_v0_3, s16 *, 0x1A) + M2C_FIELD(temp_v0_3, s16 *, 0x20));
    temp_s6 = (M2C_FIELD(temp_v0_3, s16 *, 4) + M2C_FIELD(temp_v0_3, s16 *, 0xA)) - (M2C_FIELD(temp_v0_3, s16 *, 0x1C) + M2C_FIELD(temp_v0_3, s16 *, 0x22));
    if (M2C_FIELD(arg0, s16 *, 0x12) == 0) var_s0 = 3;
    var_s1_2 = 1;
    if (var_s1_2 < (var_s0 + 1)) {
        var_s4 = temp_s6;
        var_s3 = temp_s7;
        var_s2 = temp_fp;
        do {
            s32 interp_y0;
            s32 interp_y1;
            s32 interp_x1;
            s32 interp_z0;
            s32 interp_x0;
            s32 interp_z1;
            temp_a3 = var_s3 / var_s0;
            temp_t1_2 = var_s4 / var_s0;
            temp_t2 = var_s2 / var_s0;
            interp_call_a0 = arg0 - 0x20;
            ASM_KEEP_NV(interp_call_a0);
            interp_call_a2 = 0xA;
            ASM_KEEP_NV(interp_call_a2);
            var_s4 += temp_s6;
            var_s3 += temp_s7;
            var_s2 += temp_fp;
            var_s1_2 += 1;
            temp_v1_5 = (M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (u8 *)D_80175DD8;
            interp_y0 = M2C_FIELD(temp_v1_5, s16 *, 0x1A);
            interp_y1 = M2C_FIELD(temp_v1_5, s16 *, 0x20);
            interp_x1 = M2C_FIELD(temp_v1_5, s16 *, 0x1E);
            interp_z0 = M2C_FIELD(temp_v1_5, s16 *, 0x1C);
            interp_x0 = M2C_FIELD(temp_v1_5, s16 *, 0x18);
            interp_z1 = M2C_FIELD(temp_v1_5, s16 *, 0x22);
            func_80165018(interp_call_a0, M2C_FIELD(arg2, s32 *, 0xC), interp_call_a2, (s16) (interp_x0 + interp_x1 + temp_t2), (s32) (s16) (interp_y0 + interp_y1 + temp_a3), (s32) (s16) (interp_z0 + interp_z1 + temp_t1_2));
        } while (var_s1_2 < (var_s0 + 1));
    }
    var_v0_2 = (u8 *)0x80170000;
    ASM_KEEP_NV(var_v0_2);
    object_table_base = var_v0_2 + 0x5DD8;
    temp_v1_6 = (u8 *)((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)object_table_base);
    if ((M2C_FIELD(temp_v1_6, s16 *, 0) != 0x190) && (M2C_FIELD(temp_v1_6, s16 *, 2) != 0x190) && (M2C_FIELD(temp_v1_6, s16 *, 4) != 0x190)) {
        var_s3_2 = 0;
        object_limit = 8;
        object_base = object_table_base;
        var_s4_2 = 0;
        do {
            temp_v0_4 = func_8003FC64(0x212);
            if (temp_v0_4 != NULL) {
                temp_s2 = temp_v0_4 + 0x20;
                M2C_FIELD(temp_s2, s16 *, 0x18) = 1;
                M2C_FIELD(temp_s2, s16 *, 0x1A) = 1;
                M2C_FIELD(temp_v0_4, M2C_UNK **, 0x10) = &D_80167C30;
                func_8004491C(temp_v0_4, &D_80166D14);
                temp_a0_4 = M2C_FIELD(temp_v0_4, void **, 0xC);
                M2C_FIELD(temp_a0_4, s16 *, 0x10) = 0x20;
                M2C_FIELD(temp_a0_4, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0_4, u16 *, 0x14) | 0xC);
                temp_v1_7 = M2C_FIELD(temp_v0_4, void **, 8);
                var_s1_3 = 0;
                M2C_FIELD(temp_v1_7, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
                temp_a2_2 = object_limit - var_s3_2;
                M2C_FIELD(temp_v1_7, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
                var_a1_3 = temp_s2;
                M2C_FIELD(temp_v1_7, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
                temp_a0_5 = M2C_FIELD(temp_v0_4, void **, 0xC);
                M2C_FIELD(temp_a0_5, s16 *, 0x1E) = 0x1000;
                M2C_FIELD(temp_a0_5, s16 *, 0x1C) = 0x1000;
                M2C_FIELD(temp_a0_5, u8 *, 0xE) = 0x80;
                M2C_FIELD(temp_a0_5, u8 *, 0xD) = 0x80;
                M2C_FIELD(temp_a0_5, u8 *, 0xC) = 0x80;
                do {
                    var_v0_3 = (u8) M2C_FIELD(arg2, s32 *, 0xC) * temp_a2_2;
                    if (var_v0_3 < 0) var_v0_3 += 7;
                    M2C_FIELD(var_a1_3, s8 *, 0) = (s8) (var_v0_3 >> 3);
                    var_v0_4 = M2C_FIELD(arg2, u8 *, 0xD) * temp_a2_2;
                    if (var_v0_4 < 0) var_v0_4 += 7;
                    M2C_FIELD(var_a1_3, s8 *, 1) = (s8) (var_v0_4 >> 3);
                    var_v0_5 = M2C_FIELD(arg2, u8 *, 0xE) * temp_a2_2;
                    if (var_v0_5 < 0) var_v0_5 += 7;
                    M2C_FIELD(var_a1_3, s8 *, 2) = (s8) (var_v0_5 >> 3);
                    var_s1_3 += 1;
                    var_a1_3 += 4;
                } while (var_s1_3 < 4);
                M2C_FIELD(temp_a0_5, s16 *, 6) = 0;
                func_8003DB94(temp_a0_5, &D_800DEAE0, 0);
                var_t2_3 = 0;
                object_offset = var_s4_2;
                var_t0 = temp_s2;
                var_t3 = var_t2_3;
                do {
                    var_a1_4 = 0;
                    var_t1 = var_t3;
                    var_a3_3 = var_t0 + 0x80;
                    var_a2_2 = var_t0 + 0x74;
loop_64:
                    temp_a0_6 = var_a1_4 * 2;
                    *var_a2_2 = *(u16 *)(temp_a0_6 + (var_t1 + (object_offset + ((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)object_base))));
                    var_a1_4 += 1;
                    var_a2_2 += 1;
                    object_copy_index = object_offset + ((M2C_FIELD(arg0, s16 *, 0x1C) * 0x60) + (s32)object_base);
                    object_copy_index += 0xC;
                    ASM_KEEP_NV(object_copy_index);
                    object_copy_index = var_t1 + object_copy_index;
                    ASM_KEEP_NV(object_copy_index);
                    temp_a0_6 += object_copy_index;
                    ASM_KEEP_NV(temp_a0_6);
                    *var_a3_3 = *(u16 *)temp_a0_6;
                    var_a3_3 += 1;
                    if (var_a1_4 < 3) goto loop_64;
                    var_t0 += 6;
                    var_t2_3 += 1;
                    var_t3 += 6;
                } while (var_t2_3 < 2);
            }
            var_s3_2 += 1;
            var_s4_2 += 0xC;
        } while (var_s3_2 < 7);
    }
    temp_v0_5 = (u16) M2C_FIELD(arg0, s16 *, 0x18) - 1;
    M2C_FIELD(arg0, s16 *, 0x18) = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
#undef arg0
