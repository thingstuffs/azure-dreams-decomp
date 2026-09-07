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

s16 func_8002773C();
void *func_800280F4(void *, void *, u16 *);
void func_8003DB4C();
M2C_UNK func_80041E70();
void func_80042710();
void func_80042984();
M2C_UNK func_80098B38();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
s32 func_800A1BD0();
M2C_UNK func_800A31D0();
s16 func_800A57B4();
typedef struct {
    u8 pad_00[0x10];
    u8 flags;
    u8 pad_11[3];
} D_8006DE24_Record;
extern u8 D_80010980[];
extern u8 D_800287B4[];
extern s32 D_8006D6D8[4];
extern D_8006DE24_Record D_8006DE24[];
extern s32 D_800814A0;
extern void *D_800814A8;
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];
extern u8 D_80080000[];
extern u8 D_80030000[];
__asm__(".set D_80080000, 0x80080000");
__asm__(".set D_80030000, 0x80030000");

void *func_800277F4(void *arg0, void *arg1, void *arg2) {
    u8 sp10[17];
#define sp13 (sp10 + 3)
#define sp18 (sp10 + 8)
    u16 sp28;
    u16 sp30;
    s32 temp_mask;
    u8 *clear_a1;
    u8 *clear_a2;
    u8 *clear_a3;
    u8 *var_a1;
    u8 *tile_p;
    D_8006DE24_Record *terrain_table;
    u8 *var_t0;
    u8 *merge_out;
    u8 *var_v1;
    M2C_UNK var_a2_3;
    s16 temp_v0_3;
    register s32 temp_v0_4 ASM_REG("$4");
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    register s16 var_s6_2 ASM_REG("$22");
    register s16 var_s7 ASM_REG("$23");
    s32 temp_a0;
    s32 temp_a0_10;
    s32 temp_a0_4;
    s32 temp_a0_7;
    register s32 temp_a1_3 ASM_REG("$5");
    s32 temp_a2;
    s32 temp_s1_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 slot_index;
    s32 slot_flags;
    register s32 global_flags ASM_REG("$2");
    s32 var_s0;
    s32 var_s3;
    register s32 var_s6 ASM_REG("$22");
    s32 var_v0_2;
    u8 *temp_a1;
    u8 *temp_s0_2;
    u8 *slot_addr;
    register u8 *slot_base ASM_REG("$4");
    u8 temp_a0_2;
    u8 temp_v0;
    u8 temp_v0_8;
    u8 temp_v1_10;
    u8 temp_v1_8;
    u8 temp_v1_9;
    u8 room_x;
    u8 room_y;
    u8 merge_key;
    register void *table_a0 ASM_REG("$4");
    void *temp_a0_3;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a0_8;
    void *temp_a0_9;
    void *temp_a1_2;
    void *temp_a3;
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_3;
    void *temp_v0_2;
    void *temp_v1_4;
    void *temp_v1_5;
    void *var_a0;
    void *var_a0_2;
    volatile u8 *var_a2;
    register void *var_a2_2 ASM_REG("$6");
    void *var_s2;
    register void *var_s4 ASM_REG("$20");
    void *held0 = arg0;
    s32 one_s1;
    void *var_v0_3;
    void *var_v0_4;
    void *var_v1_4;

    {
    register void *var_s1 ASM_REG("$17");
    var_s1 = arg1;
    sp30 = 2;
    var_s2 = func_800280F4(held0, var_s1, &sp28);
    if (var_s2 == NULL) {
        return NULL;
    }
    {
        void *arg2_for_call = arg2;
        if (arg2_for_call != NULL) {
            func_80042710(arg2_for_call, var_s2);
            if (held0 == var_s2) {
                held0 = arg2;
                var_s2 = held0;
                goto block_6;
            }
            var_s1 = arg2;
            var_s2 = var_s1;
        }
block_6:
        var_s4 = var_s1;
        if (held0 != var_s2) {
            var_s4 = held0;
        }
    }
        var_s6 = 2;
        clear_a3 = sp18;
        clear_a2 = sp10;
        clear_a1 = sp13;
        temp_mask = sp28;
        temp_v1 = M2C_FIELD(var_s2, s32 *, 0x14) & ~7;
        M2C_FIELD(var_s2, volatile s32 *, 0x14) = temp_v1;
        temp_v1 |= temp_mask;
        M2C_FIELD(var_s2, s32 *, 0x14) = temp_v1;
        do {
            temp_v1_2 = var_s6 << 0x10;
            ASM_KEEP_NV(temp_v1_2);
            temp_a0_4 = var_s6 - 1;
            var_s6 = temp_a0_4;
            temp_v1_3 = temp_v1_2 >> 0x10;
            temp_v0_2 = clear_a3 + (temp_v1_3 * 3);
            M2C_FIELD(temp_v0_2, s8 *, 0) = 0;
            M2C_FIELD(temp_v0_2, s8 *, 2) = 0;
            clear_a1[temp_v1_3] = 0;
            clear_a2[temp_v1_3] = 0;
            ASM_KEEP_NV(temp_a0_4);
        } while ((s16) temp_a0_4 >= 0);
        var_s6_2 = 0;
        temp_v0_3 = func_8002773C(var_s2, clear_a1, clear_a2, clear_a3);
        if (temp_v0_3 >= 0) {
#ifdef NON_MATCHING
            one_s1 = 1;
            sp10[temp_v0_3] = (u8) one_s1;
#else
            {
                u8 *indexed_sp =
                    (u8 *) &sp28 + temp_v0_3 - 0x28;

                one_s1 = 1;
                indexed_sp[0x10] = (u8) one_s1;
            }
#endif
            temp_s0 = var_s2 + (temp_v0_3 * 3);
            temp_v0_4 = (s16) func_800A57B4(var_s4, M2C_FIELD(temp_s0, u8 *, 8));
            ASM_KEEP_NV(temp_v0_4);
            if (temp_v0_4 >= 0) {
                sp13[temp_v0_4] = (u8) one_s1;
                temp_a0_3 = var_s4 + (temp_v0_4 * 3);
                if ((u8) M2C_FIELD(temp_s0, u8 *, 0xA) < (u8) M2C_FIELD(temp_a0_3, u8 *, 0xA)) {
                    temp_a0_5 = sp18 + (var_s6_2 * 3);
                    M2C_FIELD(temp_a0_5, u8 *, 0) = M2C_FIELD(temp_a0_3, u8 *, 8);
                    M2C_FIELD(temp_a0_5, u8 *, 2) = M2C_FIELD(temp_a0_3, u8 *, 0xA);
                    goto block_16;
                }
            }
            {
                s32 copy_dst_index = (s16) var_s6_2;
                s32 copy_dst_offset;
                u8 *copy_dst;
                s32 copy_src_index;
                u8 *copy_src;

                copy_dst_offset = copy_dst_index * 3;
                ASM_KEEP_NV(copy_dst_offset);
                copy_dst = sp18;
                ASM_KEEP_NV(copy_dst);
                copy_src_index = (s16) temp_v0_3;

                copy_src = var_s2 + (copy_src_index * 3);

                M2C_FIELD(copy_dst, u8 *, copy_dst_offset) = (u8) M2C_FIELD(copy_src, u8 *, 8);
                M2C_FIELD(copy_dst, u8 *, copy_dst_offset + 2) = (u8) M2C_FIELD(copy_src, u8 *, 0xA);
            }
block_16:
            var_s6_2 += 1;
        }
block_17:
        temp_v0_5 = func_8002773C(var_s4);
        if (temp_v0_5 >= 0) {
            register u8 *visited_slot ASM_REG("$16");
#ifdef NON_MATCHING
            visited_slot = sp13 + temp_v0_5;
#else
            {
                u8 *frame_base =
                    (u8 *) &sp28 - 0x28;
                register u8 *visited_base ASM_REG("$2") =
                    frame_base + 0x13;
                visited_slot = visited_base + temp_v0_5;
            }
#endif
            ASM_KEEP_NV(visited_slot);
            if (*visited_slot == 0) {
                temp_s1 = var_s4 + (temp_v0_5 * 3);
                temp_v0_6 = func_800A57B4(var_s2, M2C_FIELD(temp_s1, u8 *, 8));
                if (temp_v0_6 >= 0) {
                    sp10[temp_v0_6] = 1;
                }
                *visited_slot = 1;
                if (temp_v0_6 >= 0) {
                    temp_a1_2 = var_s2 + (temp_v0_6 * 3);
                    if ((u8) M2C_FIELD(temp_s1, u8 *, 0xA) < (u8) M2C_FIELD(temp_a1_2, u8 *, 0xA)) {
                        s32 copy_dst_index = (s16) var_s6_2;
                        s32 copy_dst_offset;
                        u8 *copy_dst;

                        copy_dst_offset = copy_dst_index * 3;
                        ASM_KEEP_NV(copy_dst_offset);
                        copy_dst = sp18;

                        copy_dst += copy_dst_offset;
                        temp_a0_2 = M2C_FIELD(temp_a1_2, u8 *, 8);
                        M2C_FIELD(copy_dst, u8 *, 0) = temp_a0_2;
                        M2C_FIELD(copy_dst, u8 *, 2) = M2C_FIELD(temp_a1_2, u8 *, 0xA);
                        goto block_25;
                    }
                }
                {
                    s32 copy_dst_index = (s16) var_s6_2;
                    s32 copy_dst_offset;
                    u8 *copy_dst;
                    s32 copy_src_index;
                    register u8 *copy_src ASM_REG("$3");

                    copy_dst_offset = copy_dst_index * 3;
                    ASM_KEEP_NV(copy_dst_offset);
                    copy_dst = sp18;
                    ASM_KEEP_NV(copy_dst);
                    copy_src_index = (s16) temp_v0_5;

                    copy_src = var_s4 + (copy_src_index * 3);

                    copy_dst += copy_dst_offset;
                    M2C_FIELD(copy_dst, u8 *, 0) = (u8) M2C_FIELD(copy_src, u8 *, 8);
                    M2C_FIELD(copy_dst, u8 *, 2) = (u8) M2C_FIELD(copy_src, u8 *, 0xA);
                }
block_25:
                var_s6_2 += 1;
            }
        }
        {
            u16 merge_limit = 3;
            if ((M2C_FIELD(var_s2, u8 *, 0xE) != 0) || (M2C_FIELD(var_s4, u8 *, 0xE) != 0)) {
                sp30 = merge_limit;
            }
            var_s7 = 0;
        }
        var_s3 = 0;
        var_t0 = sp10;
        ASM_KEEP_NV(var_t0);
        merge_out = sp18;
        ASM_KEEP_NV(merge_out);
loop_30:
        if (var_s6_2 < (s32) sp30) {
            var_a0 = var_s4;
            if (var_s7 == 0) {
                var_a0 = var_s2;
            }
            temp_v1_6 = var_s3 >> 1;
            temp_s1_2 = temp_v1_6 * 3;
            if ((M2C_FIELD((var_a0 + temp_s1_2), u8 *, 8) != 0) && (*((var_s7 * 3) + var_t0 + temp_v1_6) == 0)) {
                var_a0_2 = var_s4;
                if (var_s7 != 0) {
                    var_a0_2 = var_s2;
                }
                var_v0_3 = var_s4;
                if (var_s7 == 0) {
                    var_v0_3 = var_s2;
                }
                merge_key = M2C_FIELD((var_v0_3 + temp_s1_2), u8 *, 8);
                temp_v0_7 = func_800A57B4(var_a0_2, merge_key);
                if (temp_v0_7 < 0) {
                    var_a2_2 = var_s4;
                    goto block_54;
                }
                if (temp_v0_7 >= 0) {
                    var_v1 = var_t0;
                    if (var_s7 == 0) {
                        var_v1 = sp13;
                    }
                    *(var_v1 + temp_v0_7) = 1;
                    var_v0_4 = var_s4;
                    if (var_s7 == 0) {
                        var_v0_4 = var_s2;
                    }
                    var_v1 = var_s4;

                    temp_a1 = var_v0_4 + temp_s1_2;
                    if (var_s7 != 0) {
                        var_v1 = var_s2;
                    }
                    temp_a0 = temp_v0_7 * 3;
                    if ((u8) M2C_FIELD(temp_a1, u8 *, 0xA) < (u8) M2C_FIELD((var_v1 + temp_a0), u8 *, 0xA)) {
                        var_v1 = var_s4;
                        temp_a1 = merge_out + (var_s6_2 * 3);
                        if (var_s7 != 0) {
                            var_v1 = var_s2;
                        }
                        *temp_a1 = M2C_FIELD((var_v1 + temp_a0), u8 *, 8);
                        var_v1 = var_s4;
                        if (var_s7 != 0) {
                            var_v1 = var_s2;
                        }
                        temp_a1[2] = M2C_FIELD((var_v1 + temp_a0), u8 *, 0xA);
                        goto block_58;
                    }
                    var_a2_2 = var_s4;
                    goto block_54;
                }
block_54:
                temp_a3 = merge_out + (var_s6_2 * 3);
                if (var_s7 == 0) {
                    var_a2_2 = var_s2;
                }
                {
                    s32 fallback_half = var_s3 >> 1;
                    register s32 fallback_twice ASM_REG("$2") = fallback_half * 2;
                    s32 fallback_offset = fallback_twice + fallback_half;
                    register u8 *fallback_source ASM_REG("$2");
                    u8 *second_source;



                    fallback_source = var_a2_2 + fallback_offset;


                    M2C_FIELD(temp_a3, u8 *, 0) = M2C_FIELD(fallback_source, u8 *, 8);
                    second_source = var_s4;
                    if (var_s7 == 0) {
                        second_source = var_s2;
                    }

                    fallback_source = second_source + fallback_offset;

                    M2C_FIELD(temp_a3, u8 *, 2) = M2C_FIELD(fallback_source, u8 *, 0xA);
                }
block_58:
                temp_a0_8 = merge_out + (var_s6_2 * 3);
                if (M2C_FIELD(temp_a0_8, u8 *, 0) == 0x2E) {
                    M2C_FIELD(temp_a0_8, u8 *, 0) = 0U;
                    M2C_FIELD(temp_a0_8, s8 *, 2) = 0;
                }
                var_s6_2 += 1;
                {
                    u8 *visited_row = (u8 *) ((var_s7 * 3) + (s32) var_t0);
                    s32 visited_index = var_s3 >> 1;
                    visited_row[visited_index] = 1;
                }
                goto block_61;
            }
block_61:
            var_s3 += 1;
            var_s7 ^= 1;
            if (var_s3 >= 6) {
                goto block_62;
            }
            goto loop_30;
        }
block_62:
        var_s3 = 2;
        if ((var_s6_2 << 0x10) == 0) {
            u8 *default_table = (u8 *) 0x80030000;
            s32 default_index;
            ASM_KEEP_NV(default_table);
            default_index = M2C_FIELD(var_s2, u8 *, 0x13);
            ASM_KEEP(default_index);
            default_table -= 0x784C;
            ASM_KEEP_NV(default_table);
            default_index += (s32) default_table;
            sp18[0] = *(u8 *) default_index;
            sp18[2] = 1;
        }
        ASM_USE_NV(var_s6_2);
        terrain_table = D_8006DE24;
        tile_p = &sp10[8];
        do {
        {
        register s32 tile_test ASM_REG("$2") = tile_p[var_s3 * 3];
        ASM_KEEP_NV(tile_test);
        if (tile_test != 0) {
            s32 tile = tile_test;
            temp_v1_7 = M2C_FIELD(var_s2, s32 *, 0x14);
            if (!(terrain_table[tile].flags & 7 & temp_v1_7)) {
                if (temp_v1_7 & 1) {
                    tile_p[var_s3 * 3] = (u8) ((((tile - 1) / 3) * 3) + 1);
                    goto block_75;
                }
                if (temp_v1_7 & 2) {
                    tile_p[var_s3 * 3] = (u8) ((((tile - 1) / 3) * 3) + 2);
                    goto block_75;
                }
                if (temp_v1_7 & 4) {
                    tile_p[var_s3 * 3] = (u8) ((((tile - 1) / 3) * 3) + 3);
                }
                goto block_75;
            }
        }
        }
block_75:
        M2C_FIELD((var_s2 + (var_s3 * 3)), u8 *, 8) = (u8) tile_p[var_s3 * 3];
        temp_v0_8 = tile_p[(var_s3 * 3) + 2];
        M2C_FIELD((var_s2 + (var_s3 * 3)), u8 *, 0xA) = temp_v0_8;
        var_s3 -= 1;
        } while (var_s3 >= 0);
            {
                s32 idx_b = M2C_FIELD(var_s4, u8 *, 0x13);
                s32 idx_a = M2C_FIELD(var_s2, u8 *, 0x13);
                s32 *pb, *pa;
                s32 val_a, own;
                table_a0 = var_s2;

                temp_a1_3 = (s32) D_8006D6D8;
                ASM_SCHED_BARRIER();
                temp_a2 = M2C_FIELD(var_s4, s32 *, 0x54);
                pb = (s32 *) temp_a1_3 + idx_b;
                pa = (s32 *) temp_a1_3 + idx_a;
                temp_a1_3 = *pb;
                own = M2C_FIELD(var_s2, s32 *, 0x54);
                val_a = *pa;
                temp_a1_3 &= temp_a2;
                M2C_FIELD(var_s2, s32 *, 0x54) = (s32) ((own & val_a) | temp_a1_3);
            }
            func_80041E70(table_a0, temp_a1_3, temp_a2);
            M2C_FIELD(var_s2, u16 *, 0x24) = (u16) ((u32) ((M2C_FIELD(var_s2, u16 *, 0x24) + M2C_FIELD(var_s4, u16 *, 0x24)) & 0xFFFF) >> 1);
            temp_v1_8 = M2C_FIELD(var_s2, u8 *, 0x66);
            if (temp_v1_8 < (u8) M2C_FIELD(var_s2, u8 *, 0x25)) {
                M2C_FIELD(var_s2, u8 *, 0x25) = temp_v1_8;
            }
            M2C_FIELD(var_s2, u8 *, 0x24) = 0xFF;
            if (M2C_FIELD(var_s2, u8 *, 0x25) != 0) {
                M2C_FIELD(var_s2, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s2, s32 *, 0x1C) & ~8);
            }
            if (arg2 == NULL) {
                func_80042984(var_s2);
            }
            if ((M2C_FIELD(var_s2, u8 *, 0x49) != 0) && !(M2C_FIELD(var_s2, u8 *, 0x4B) & 0x20)) {
                M2C_FIELD(var_s2, s32 *, 0x48) = 0;
            }
            var_s0 = 0;
            if ((u8) M2C_FIELD(var_s2, u8 *, 0x43) < 0x40U) {
                var_s0 = ((u8) M2C_FIELD(var_s4, u8 *, 0x43) < 0x40U) * 2;
            } else {
                temp_v1_9 = M2C_FIELD(var_s4, u8 *, 0x43);
                if (temp_v1_9 < 0x40U) {
                    var_s0 = 1;

                    M2C_FIELD(var_s2, u8 *, 0x43) = temp_v1_9;
                    var_v0_2 = var_s0;
                    ASM_KEEP_NV(var_v0_2);
                    M2C_FIELD(var_s2, s8 *, 0x44) = (s8) var_v0_2;
                }
            }
            if (arg2 == NULL) {
                func_800A31D0(var_s4);
                func_800A18E8(M2C_FIELD(var_s4, u8 *, 0x13), 3);
                slot_index = func_800A1BD0(var_s4);
                {
#ifdef NON_MATCHING
                    u8 *slot_page = D_80080000;
#else
                    u8 *slot_page = (u8 *) 0x80080000;
#endif
                    ASM_KEEP_NV(slot_page);
                    slot_base = *(u8 **) (slot_page + 0x14A8);
                }
                slot_addr = (u8 *) (((s32) (slot_index << 0x10) >> 0xE) + (s32) slot_base);
                ASM_KEEP_NV(slot_addr);

                slot_flags = M2C_FIELD(var_s4, s32 *, 0x1C) & 0x2000;
                temp_a0_9 = M2C_FIELD(var_s4, void **, -0x14);
                temp_s1_3 = M2C_FIELD(slot_addr, void **, 0xD0);
                room_x = M2C_FIELD(temp_a0_9, u8 *, 0x24);
                room_y = M2C_FIELD(temp_a0_9, u8 *, 0x25);
                ASM_KEEP(slot_flags);
                var_a2_3 = 0x3000;
                if (slot_flags != 0) {
                    var_a2_3 = 0x300;
                }
                func_8009A3D0(room_x, room_y, var_a2_3);
                func_8009A028(var_s4);
                if (var_s0 == 1) {
#ifdef NON_MATCHING
                    D_80010980[M2C_FIELD(var_s4, u8 *, 0x43) * 4] = M2C_FIELD(var_s2, u8 *, 0x13);
#else
                    u8 *room_page = (u8 *) 0x80010000;

                    room_page[0x980 + (M2C_FIELD(var_s4, u8 *, 0x43) * 4)] = M2C_FIELD(var_s2, u8 *, 0x13);
#endif
                    M2C_FIELD(var_s4, u8 *, 0x43) = 0xFF;
                } else if (var_s0 == 2) {
#ifdef NON_MATCHING
                    *(s32 *) &D_80010980[M2C_FIELD(var_s4, u8 *, 0x43) * 4] = 0;
#else
                    u32 room_base = 0x80010000;
                    s32 room_index;
                    ASM_KEEP_NV(room_base);
                    room_index = M2C_FIELD(var_s4, u8 *, 0x43);

                    room_base |= 0x980;

                    *(s32 *) (room_base + (room_index * 4)) = 0;
#endif
                }
                slot_index = func_800A1BD0(var_s4);
                {
#ifdef NON_MATCHING
                    u8 *slot_page = D_80080000;
#else
                    u8 *slot_page = (u8 *) 0x80080000;
#endif
                    u8 *runtime_base;
                    u8 *runtime_addr;
                    ASM_KEEP_NV(slot_page);
                    runtime_base = *(u8 **) (slot_page + 0x14A8);
                    runtime_addr = (u8 *) (((s32) (slot_index << 0x10) >> 0xE) + (s32) runtime_base);

                    M2C_FIELD(runtime_addr, s32 *, 0xD0) = 0;
                }
                func_8003DB4C(&D_800E3E48[(M2C_FIELD(temp_s1_3, u8 *, 3) & 0x1F) * 0x8C], 0x23);
                {
                    register void *destroy_arg ASM_REG("$4") = temp_s1_3;
                    ASM_KEEP_NV(destroy_arg);
#ifdef NON_MATCHING
                    D_800E3DF0[M2C_FIELD(temp_s1_3, u8 *, 3) & 0x1F] = 0;
#else
                    {
                        u32 dead_base = 0x800E0000;
                        s32 dead_index;
                        ASM_KEEP_NV(dead_base);
                        dead_index = M2C_FIELD(temp_s1_3, u8 *, 3);
                        ASM_KEEP(dead_index);
                        dead_base += 0x3DF0;
                        ASM_KEEP_NV(dead_base);
                        *(u32 *) (dead_base + ((dead_index & 0x1F) * 4)) = 0;
                    }
#endif
                    func_80098B38(destroy_arg);
                }
                temp_a0_10 = M2C_FIELD(var_s2, s32 *, 0x54);
                if ((temp_a0_10 & 0x800000) &&
                    ((temp_v1_10 = M2C_FIELD(var_s2, u8 *, 0x13)) != 2) &&
                    (temp_v1_10 != 0x39)) {
                    M2C_FIELD(var_s2, s32 *, 0x54) = (s32) (temp_a0_10 & 0xFF7FFFFF);
                }
                M2C_FIELD(var_s4, u16 *, -2) = (u16) (M2C_FIELD(var_s4, u16 *, -2) | 0x8000);
                global_flags = *(s32 *) (D_80080000 + 0x14A0);
                global_flags |= 0x8000;
                *(s32 *) (D_80080000 + 0x14A0) = global_flags;
                return var_s2;
            }
            return var_s2;
    }
    return var_s2;
}
