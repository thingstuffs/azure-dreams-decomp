/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                        /* extern */
s32 func_8009074C();               /* extern */
M2C_UNK func_8009F644();      /* extern */
u32 func_800A0818(); /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern void *D_80025000[];
__asm__(".set D_80025000, 0x80025000");
extern u16 D_80012094[5];
extern u16 D_80012096[5];
extern u8 D_80026864[16];
extern s16 D_80027156[5];
extern u16 D_80027158[5];
extern s16 D_8002715C[5];
extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern u8 D_80080A87[16];
extern s32 D_800814A0;
extern u8 D_80083160[32];
extern u8 D_800E3D7C[16384];

void func_8002520C(void *arg0_in, void *arg1_in, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_default };
    u16 sp18;
    u16 entry_counter;
    s16 temp_a0;
    s16 temp_a0_10;
    s16 temp_a0_4;
    s16 temp_a0_8;
    s16 temp_a0_9;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_6;
    s32 temp_v1;
    s16 temp_v1_8;
    s32 temp_a0_2;
    s32 temp_a0_6;
    s32 temp_flags_raw;
    s32 temp_flags;
    s32 temp_a3_2;
    s32 temp_t1;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a1_2;
    s32 var_v0_5;
    u16 *temp_a0_3;
    u16 *temp_t3;
    u16 *var_a0;
    u16 *var_v0_6;
    u16 *var_v0_7;
    u16 *var_v1_2;
    u16 *var_v1_3;
    u16 temp_a0_11;
    u16 temp_a1;
    u16 temp_v0_5;
    u16 temp_v1_2;
    u16 temp_v1_9;
    u32 temp_v0_2;
    u32 temp_v1_5;
    u32 var_v0_3;
    u8 temp_t2;
    u8 temp_v1_10;
    u8 temp_v1_11;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 var_a2;
    void **var_v0_2;
    void **var_v0_4;
    void **var_v1;
    void *temp_a0_12;
    void *temp_a0_5;
    void *temp_a0_7;
    void *temp_a1_2;
    void *temp_a3;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_t0;
    void *temp_t0_2;
    void *temp_v0_4;
    void *temp_v1_12;
    register void *var_a1 ASM_REG("$5");
    s32 *var_a2_2;
    void *var_v1_4;
    u8 *state_base;
    void *arg2_local;
    u8 *counter_page;
    s32 *world_page;
    void *arg0 = arg0_in;
    void *arg1 = arg1_in;
    entry_counter = D_8002715C[0];
    D_8002715C[0] = entry_counter + 1;
    temp_s1 = arg1;
    arg2_local = arg2;
    state_base = D_80083160;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1C);
    (void)jt_keep;
    if ((u32)temp_v1 >= 5U) {
        goto jt_default;
    }
    goto *D_80025000[(u32)temp_v1];
jt_c0:
        func_8004491C(arg0 - 0x20, &D_80026864);
        M2C_FIELD(temp_s1, s16 *, 2) = -0x180;
        M2C_FIELD(temp_s1, s16 *, 6) = -0x20;
        M2C_FIELD(arg2_local, u16 *, 0x16) = 0x1000U;
        M2C_FIELD(arg2_local, u16 *, 0x1E) = 0x1000U;
        M2C_FIELD(arg2_local, u16 *, 0x1C) = 0x1000U;
        M2C_FIELD(arg0, s16 *, 0x22) = 8;
        M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
        /* fallthrough */
jt_c1:
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x22);
        if (temp_a0 != 0) {
            M2C_FIELD(temp_s1, s16 *, 2) = (s16) ((u16) M2C_FIELD(temp_s1, s16 *, 2) + ((s32) (-0x80 - M2C_FIELD(temp_s1, s16 *, 2)) / temp_a0));
            M2C_FIELD(temp_s1, s16 *, 0xA) = (s16) (func_800644B8(M2C_FIELD(arg0, s16 *, 0x22) << 5) + 0x400);
            temp_v1_2 = M2C_FIELD(arg2_local, u16 *, 0x16);
            M2C_FIELD(arg2_local, u16 *, 0x16) = (u16) (temp_v1_2 + ((s32) (0xD00 - temp_v1_2) / (s16) M2C_FIELD(arg0, s16 *, 0x22)));
            temp_v1_3 = M2C_FIELD(arg2_local, u8 *, 0xE);
            temp_v1_4 = temp_v1_3 + ((s32) (0x80 - temp_v1_3) / (s16) M2C_FIELD(arg0, s16 *, 0x22));
            M2C_FIELD(arg2_local, u8 *, 0xE) = temp_v1_4;
            M2C_FIELD(arg2_local, u8 *, 0xD) = temp_v1_4;
            M2C_FIELD(arg2_local, u8 *, 0xC) = temp_v1_4;
        }
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x22) - 1;
        M2C_FIELD(arg0, s16 *, 0x22) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(temp_s1, s16 *, 2) = -0x80;
            M2C_FIELD(temp_s1, s16 *, 6) = -0x20;
            M2C_FIELD(temp_s1, s16 *, 0xA) = 0x400;
            M2C_FIELD(arg2_local, u16 *, 0x16) = 0xD00U;
            M2C_FIELD(arg2_local, u8 *, 0xE) = 0x80U;
            M2C_FIELD(arg2_local, u8 *, 0xD) = 0x80U;
            M2C_FIELD(arg2_local, u8 *, 0xC) = 0x80U;
            M2C_FIELD(arg0, s16 *, 0x22) = 0;
            M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
        jt_c2:
        }
        if (D_80027156[0] == 0) {
            temp_v1_5 = func_8009074C(((u16) M2C_FIELD(arg2_local, u16 *, 0x1A) >> 9) & 7, M2C_FIELD(&D_800E3D7C, s32 *, 0) + 0xA2, 0) & 0xFFFF;
            if ((temp_v1_5 != 0xFFF) && (M2C_FIELD(state_base, s32 *, 0x10) & 0xF000)) {
                register s32 table_idx ASM_REG("$9");
                register s32 slot_a0 ASM_REG("$4");
                s32 side_index;
                register void *dest ASM_REG("$7");
                register u16 *x_table ASM_REG("$11");
                register void *cell ASM_REG("$8");
                register u32 base_x ASM_REG("$10");
                register u32 x_value ASM_REG("$6");
                register u32 y_value ASM_REG("$5");
                register s32 compare_x ASM_REG("$3");

                {
                    register u32 shifted ASM_REG("$3");

                    shifted = temp_v1_5 >> 9;
                    side_index = M2C_FIELD(arg0, s16 *, 0x26);
                    ASM_SCHED_BARRIER();
                    table_idx = shifted & 7;
                    ASM_KEEP_DEP_NV(table_idx, shifted);
                }
                slot_a0 = table_idx * 2;
                temp_v0_4 = M2C_FIELD(((side_index * 4) + arg0), void **, 0xC);
                dest = temp_v0_4 + 0x20;
                ASM_KEEP_DEP_NV(dest, temp_v0_4);
                ASM_KEEP(dest);
                cell = M2C_FIELD(dest, void **, -0x14);
                {
                    register s32 load_v0 ASM_REG("$2");
                    register s32 load_v1 ASM_REG("$3");

                    load_v0 = (s32) D_8006CCD8;
                    x_table = (u16 *) (slot_a0 + load_v0);
                    ASM_KEEP_NV(x_table);
                    load_v0 = *x_table;
                    load_v1 = M2C_FIELD(cell, u8 *, 0x24);
                    ASM_USE2_NV(load_v0, load_v1);
                    base_x = load_v1 + load_v0;
                    ASM_KEEP(base_x);
                    load_v0 = (s32) D_8006CCE8;
                    slot_a0 += load_v0;
                    ASM_KEEP_NV(slot_a0);
                    load_v1 = M2C_FIELD(cell, u8 *, 0x25);
                    ASM_KEEP(load_v1);
                    load_v0 = *(u16 *) slot_a0;
                    ASM_KEEP_DEP_NV(base_x, load_v0);
                    x_value = base_x;
                    y_value = load_v1 + load_v0;
                }
                sp18 = (u16) y_value;
                ASM_USE2_NV(table_idx, dest);
                ASM_USE2_NV(cell, x_value);
                ASM_USE_NV(y_value);
                compare_x = x_value & 0xFFFF;
                ASM_USE2_NV(compare_x, x_value);
                ASM_KEEP_NV(x_value);
                if (compare_x == 1) {
                    if ((y_value & 0xFFFF) == compare_x) {
                        register s32 add_v0 ASM_REG("$2");
                        register s32 add_v1 ASM_REG("$3");

                        add_v1 = *x_table;
                        add_v0 = *(u16 *) slot_a0;
                        ASM_USE2_NV(add_v0, add_v1);
                        x_value = add_v1 + base_x;
                        add_v0 = y_value + add_v0;
                        sp18 = (u16) add_v0;
                        goto block_14;
                    }
                    var_v1 = arg0 + 0xC;
                } else {
block_14:
                    var_v1 = arg0 + 0xC;
                }
                slot_a0 = M2C_FIELD(arg0, s16 *, 0x26);
                var_v0_2 = var_v1;
                if (slot_a0 == 0) {
                    var_v0_2 = arg0 + 0x10;
                }
                if (*var_v0_2 != NULL) {
                    var_v0_4 = var_v1;
                    if (slot_a0 == 0) {
                        var_v0_4 = arg0 + 0x10;
                    }
                    slot_a0 = (s32) M2C_FIELD(*var_v0_4, void **, 0xC);
                    temp_v1_6 = M2C_FIELD((void *) slot_a0, u8 *, 0x24);
                    ASM_CLOBBER("$2");
                    temp_v0_2 = x_value & 0xFFFF;
                    if (temp_v0_2 != temp_v1_6) {
                        var_v0_5 = temp_v0_2 < 3U;
                    } else {
                        y_value = sp18;
                        if (y_value == M2C_FIELD((void *) slot_a0, u8 *, 0x25)) {
                            register s32 repeat_v0 ASM_REG("$2");
                            register s32 repeat_v1 ASM_REG("$3");

                            slot_a0 = table_idx & 0xFFFF;
                            ASM_KEEP_NV(slot_a0);
                            repeat_v1 = (s32) D_8006CCD8;
                            ASM_KEEP_NV(repeat_v1);
                            slot_a0 *= 2;
                            repeat_v1 = slot_a0 + repeat_v1;
                            ASM_KEEP_NV(repeat_v1);
                            repeat_v0 = (s32) D_8006CCE8;
                            ASM_KEEP_NV(repeat_v0);
                            slot_a0 += repeat_v0;
                            ASM_KEEP_NV(slot_a0);
                            repeat_v1 = *(u16 *) repeat_v1;
                            repeat_v0 = *(u16 *) slot_a0;
                            x_value += repeat_v1;
                            repeat_v0 = y_value + repeat_v0;
                            sp18 = (u16) repeat_v0;
                            ASM_KEEP(repeat_v0);
                        }
                        var_v0_5 = (x_value & 0xFFFF) < 3U;
                    }
                } else {
                    var_v0_5 = (x_value & 0xFFFF) < 3U;
                }
                if ((var_v0_5 != 0) && (sp18 < 3U)) {
                    M2C_FIELD(dest, s16 *, 0x96) = 8;
                    M2C_FIELD(cell, u8 *, 0x24) = (u8) x_value;
                    M2C_FIELD(cell, u8 *, 0x25) = (u8) sp18;
                }
            }
            if (M2C_FIELD(state_base, s32 *, 0x10) & 0x40) {
                register s32 direction ASM_REG("$7");

                func_800A56E0(0x503);
                {
                    register s32 call_a0 ASM_REG("$4");
                    register s32 call_a1 ASM_REG("$5");
                    register s32 world_off ASM_REG("$3");
                    register s32 world_base ASM_REG("$6");
                    register void *world_node ASM_REG("$2");
                    register void *world_cell ASM_REG("$8");

                    call_a0 = 1;
                    call_a1 = call_a0;
                    ASM_KEEP_NV(call_a0);
                    ASM_KEEP_NV(call_a1);
                    world_page = (s32 *)0x800E0000;
                    ASM_SCHED_BARRIER();
                    world_off = M2C_FIELD(arg0, s16 *, 0x26);
                    ASM_KEEP_NV(world_off);
                    world_base = M2C_FIELD(world_page, s32 *, 0x3D7C);
                    ASM_KEEP_NV(world_base);
                    world_off *= 4;
                    world_node = (void *) (world_off + (s32) arg0);
                    ASM_KEEP_NV(world_node);
                    world_node = M2C_FIELD(world_node, void **, 0xC);
                    world_off += world_base;
                    world_cell = M2C_FIELD(world_node, void **, 0xC);
                    ASM_KEEP_NV(world_cell);
                    ASM_KEEP_DEP_NV(world_off, world_cell);
                    temp_s1_2 = M2C_FIELD((void *) world_off, void **, 0xAC);
                    ASM_USE2_NV(world_off, world_node);
                    direction = (func_800A0818(call_a0, call_a1, M2C_FIELD(world_cell, u8 *, 0x24), M2C_FIELD(world_cell, u8 *, 0x25), &sp18) >> 9) & 7;
                }
                ASM_KEEP_NV(direction);
                {
                    register s32 compare_dir ASM_REG("$3");
                    register s32 side_v0 ASM_REG("$2");
                    register u8 *counter_ptr ASM_REG("$4");

                    compare_dir = direction - 2;
                    ASM_USE2_NV(compare_dir, direction);
                    ASM_KEEP_NV(direction);
                    side_v0 = M2C_FIELD(arg0, s16 *, 0x26);
                    ASM_KEEP(side_v0);
                    counter_page = (u8 *)0x80010000;
                    counter_ptr = (side_v0 * 2) + counter_page;
                    ASM_KEEP_NV(counter_ptr);
                    if ((compare_dir & 7) != M2C_FIELD(counter_ptr, u16 *, 0x2094)) {
                        direction = (direction - 2) & 7;
                        M2C_FIELD(counter_ptr, u16 *, 0x2094) = direction;
                        M2C_FIELD(temp_s1_2, s8 *, 0x45) = (s8) direction;
                        func_8009F644(M2C_FIELD(world_page, s32 *, 0x3D7C), 0x90, M2C_FIELD(arg0, s16 *, 0x26), direction);
                    temp_a0_8 = M2C_FIELD(arg0, s16 *, 0x26);
                    var_v1_2 = (u16 *)0x80012094;
                    if (temp_a0_8 == 0) {
                        var_v1_2 = (u16 *)0x80012096;
                    }
                    if (*var_v1_2 == M2C_FIELD(((temp_a0_8 * 2) + counter_page), u16 *, 0x2094)) {
                        var_v1_3 = (u16 *)0x80012094;
                        if (temp_a0_8 == 0) {
                            var_v1_3 = (u16 *)0x80012096;
                        }
                        var_v0_6 = (u16 *)0x80012094;
                        if (temp_a0_8 == 0) {
                            var_v0_6 = (u16 *)0x80012096;
                        }
                        *var_v1_3 = *var_v0_6 + 1;
                        temp_v1_8 = M2C_FIELD(arg0, s16 *, 0x26);
                        var_a0 = (u16 *)0x80012094;
                        if (temp_v1_8 == 0) {
                            var_a0 = (u16 *)0x80012096;
                        }
                        var_v0_7 = (u16 *)0x80012094;
                        if (temp_v1_8 == 0) {
                            var_v0_7 = (u16 *)0x80012096;
                        }
                        *var_a0 = *var_v0_7 & 7;
                    }
                }
                }
                if (D_80080A87[0] != 0) {
                    D_80027158[0] = (u16) M2C_FIELD(arg0, s16 *, 0x26);
                    D_80027156[0] = (s16) (0x20 / (s32) D_80080A87[0]);
                }
                M2C_FIELD(M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x26) * 4) + arg0), void **, 0xC), s16 *, 0xB6) = 1;
            }
            if (M2C_FIELD(state_base, s32 *, 0x10) & 8) {
                M2C_FIELD(arg0, u16 *, 0x20) = (u16) (M2C_FIELD(arg0, u16 *, 0x20) - 0x200);
            }
            if (M2C_FIELD(state_base, s32 *, 0x10) & 4) {
                M2C_FIELD(arg0, u16 *, 0x20) = (u16) (M2C_FIELD(arg0, u16 *, 0x20) + 0x200);
            }
        }
        if (M2C_FIELD(arg0, s16 *, 0x1E) != (s16) M2C_FIELD(arg0, u16 *, 0x20)) {
            M2C_FIELD(arg0, s16 *, 0x1E) = (s16) M2C_FIELD(arg0, u16 *, 0x20);
            M2C_FIELD(arg0, s16 *, 0x24) = 8;
        }
        temp_a0_9 = M2C_FIELD(arg0, s16 *, 0x24);
        if (temp_a0_9 != 0) {
            M2C_FIELD(arg2_local, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2_local, u16 *, 0x1A) + ((s32) (M2C_FIELD(arg0, s16 *, 0x1E) - (s16) M2C_FIELD(arg2_local, u16 *, 0x1A)) / temp_a0_9));
            temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x24) - 1;
            M2C_FIELD(arg0, s16 *, 0x24) = temp_v0_3;
            if ((temp_v0_3 << 0x10) <= 0) {
                M2C_FIELD(arg2_local, u16 *, 0x1A) = (u16) M2C_FIELD(arg0, s16 *, 0x1E);
                M2C_FIELD(arg0, s16 *, 0x24) = 0;
                M2C_FIELD(arg2_local, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2_local, u16 *, 0x1A) & 0xFFF);
                M2C_FIELD(arg0, s16 *, 0x1E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1E) & 0xFFF);
                M2C_FIELD(arg0, u16 *, 0x20) = (u16) (M2C_FIELD(arg0, u16 *, 0x20) & 0xFFF);
                return;
            }
        }
    goto jt_default;
jt_c3:
        var_a1 = NULL;
        var_v1_4 = arg0;
loop_55:
        temp_v0_4 = M2C_FIELD(var_v1_4, void **, 0xC);
        if ((temp_v0_4 == NULL) || (M2C_FIELD(temp_v0_4, s16 *, 0xB6) == 0)) {
            var_a1 += 1;
            var_v1_4 += 4;
            if ((s32) var_a1 >= 2) {
                M2C_FIELD(arg0, s16 *, 0x22) = 8;
                M2C_FIELD(temp_s1, u16 *, 0x16) = 8U;
                M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
            jt_c4:
                temp_a0_10 = M2C_FIELD(arg0, s16 *, 0x22);
                if (temp_a0_10 != 0) {
                    M2C_FIELD(temp_s1, s16 *, 2) = (s16) ((u16) M2C_FIELD(temp_s1, s16 *, 2) + ((s32) (-0x480 - M2C_FIELD(temp_s1, s16 *, 2)) / temp_a0_10));
                    M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xA) + func_800644B8(M2C_FIELD(arg0, s16 *, 0x22) << 5, (s32) var_a1));
                    temp_v1_9 = M2C_FIELD(arg2_local, u16 *, 0x16);
                    M2C_FIELD(arg2_local, u16 *, 0x16) = (u16) (temp_v1_9 + ((s32) (0x1000 - temp_v1_9) / (s16) M2C_FIELD(arg0, s16 *, 0x22)));
                    temp_v1_10 = M2C_FIELD(arg2_local, u8 *, 0xE);
                    temp_a0_11 = M2C_FIELD(arg2_local, u16 *, 0x1C);
                    temp_v1_11 = temp_v1_10 + ((s32) (0 - temp_v1_10) / (s16) M2C_FIELD(arg0, s16 *, 0x22));
                    M2C_FIELD(arg2_local, u8 *, 0xE) = temp_v1_11;
                    M2C_FIELD(arg2_local, u8 *, 0xD) = temp_v1_11;
                    M2C_FIELD(arg2_local, u8 *, 0xC) = temp_v1_11;
                    temp_v0_5 = M2C_FIELD(arg2_local, u16 *, 0x1E);
                    M2C_FIELD(arg2_local, u16 *, 0x1C) = (u16) (temp_a0_11 + ((s32) (0x200 - temp_a0_11) / (s16) M2C_FIELD(arg0, s16 *, 0x22)));
                    M2C_FIELD(arg2_local, u16 *, 0x1E) = (u16) (temp_v0_5 + ((s32) (0x200 - temp_v0_5) / (s16) M2C_FIELD(arg0, s16 *, 0x22)));
                    M2C_FIELD(temp_s1, u16 *, 0x16) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x16) * 2);
                }
                temp_v0_6 = (u16) M2C_FIELD(arg0, s16 *, 0x22) - 1;
                M2C_FIELD(arg0, s16 *, 0x22) = temp_v0_6;
                if ((temp_v0_6 << 0x10) <= 0) {
                    register s32 slot_a0 ASM_REG("$4");
                    register s32 slot_a1 ASM_REG("$5");
                    register s32 slot_v0 ASM_REG("$2");
                    register s32 slot_v1 ASM_REG("$3");
                    register s32 *slot_a2 ASM_REG("$6");
                    register s32 *slot_a3 ASM_REG("$7");

                    slot_a2 = (s32 *) 0x80080000;
                    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
                    slot_v0 = M2C_FIELD(slot_a2, s32 *, 0x14A0);
                    slot_v1 = (s32) M2C_FIELD(arg0, void **, 8);
                    slot_a0 = slot_v0 | 0x8000;
                    ASM_KEEP_NV(slot_a0);
                    M2C_FIELD(slot_a2, s32 *, 0x14A0) = slot_a0;
                    if (slot_v1 != 0) {
                        M2C_FIELD((void *) slot_v1, u16 *, 0x1E) = (u16) (M2C_FIELD((void *) slot_v1, u16 *, 0x1E) | 0x8000);
                    }
                    slot_a1 = 0;
                    ASM_KEEP_NV(slot_a2);
                    slot_a3 = slot_a2;
                    slot_a2 = (s32 *) arg0;
                    do {
                        slot_a0 = (s32) M2C_FIELD(slot_a2, void **, 0xC);
                        ASM_KEEP_NV(slot_a0);
                        if (slot_a0 != 0) {
                            slot_v0 = M2C_FIELD((void *) slot_a0, u16 *, 0x1E);
                            slot_v1 = M2C_FIELD(slot_a3, s32 *, 0x14A0);
                            slot_v0 |= 0x8000;
                            slot_v1 |= 0x8000;
                            M2C_FIELD((void *) slot_a0, u16 *, 0x1E) = (u16) slot_v0;
                            M2C_FIELD(slot_a3, s32 *, 0x14A0) = slot_v1;
                        }
                        slot_a1 += 1;
                        slot_a2 += 1;
                    } while (slot_a1 < 2);
                    slot_a1 = (s32) M2C_FIELD(arg0, void **, 0x14);
                    if (slot_a1 != 0) {
                        slot_v0 = (s32) 0x80080000;
                        slot_v1 = M2C_FIELD((void *) slot_a1, u16 *, 0x1E);
                        slot_a0 = M2C_FIELD((s32 *) slot_v0, s32 *, 0x14A0);
                        slot_v1 |= 0x8000;
                        slot_a0 |= 0x8000;
                        M2C_FIELD((void *) slot_a1, u16 *, 0x1E) = (u16) slot_v1;
                        M2C_FIELD((s32 *) slot_v0, s32 *, 0x14A0) = slot_a0;
                    }
                }
            } else {
                goto loop_55;
            }
        }
    jt_default:
        return;
}
