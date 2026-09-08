/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

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


typedef struct S_800277F4_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
    u8 pad_0F[0x4];
    u8 unk_13;
    union { s32 n; volatile s32 v; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x4];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 pad_26[0x1D];
    u8 unk_43;
    s8 unk_44;
    u8 pad_45[0x3];
    union { struct { s32 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x3]; u8 v; } at03; } unk_48;   /* overlapping accesses */
    u8 pad_4C[0x8];
    s32 unk_54;
    u8 pad_58[0xE];
    u8 unk_66;
} S_800277F4_0;   /* var_s2 in func_800277F4 */

typedef struct S_800277F4_1 {
    s8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800277F4_1;   /* temp_v0_2 in func_800277F4 */

typedef struct S_800277F4_2 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_2;   /* temp_s0 in func_800277F4 */

typedef struct S_800277F4_3 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_3;   /* temp_a0_3 in func_800277F4 */

typedef struct S_800277F4_4 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
} S_800277F4_4;   /* temp_a0_5 in func_800277F4 */

typedef struct S_800277F4_5 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_5;   /* copy_src in func_800277F4 */

typedef struct S_800277F4_6 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_6;   /* temp_s1 in func_800277F4 */

typedef struct S_800277F4_7 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_7;   /* temp_a1_2 in func_800277F4 */

typedef struct S_800277F4_8_pre {
    void * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800277F4_8_pre;   /* the 0x14 bytes before var_s4 in func_800277F4, addressed as var_s4[-1] */

typedef struct S_800277F4_8 {
    u8 pad_00[0xE];
    u8 unk_0E;
    u8 pad_0F[0x4];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x4];
    u16 unk_24;
    u8 pad_26[0x1D];
    u8 unk_43;
    u8 pad_44[0x10];
    s32 unk_54;
} S_800277F4_8;   /* var_s4 in func_800277F4 */

typedef struct S_800277F4_9 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800277F4_9;   /* (var_a0 + temp_s1_2) in func_800277F4 */

typedef struct S_800277F4_10 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800277F4_10;   /* (var_v0_3 + temp_s1_2) in func_800277F4 */

typedef struct S_800277F4_11 {
    u8 pad_00[0xA];
    u8 unk_0A;
} S_800277F4_11;   /* temp_a1 in func_800277F4 */

typedef struct S_800277F4_12 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_12;   /* (var_v1 + temp_a0) in func_800277F4 */

typedef struct S_800277F4_13 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
} S_800277F4_13;   /* temp_a3 in func_800277F4 */

typedef struct S_800277F4_14 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_14;   /* fallback_source in func_800277F4 */

typedef struct S_800277F4_15 {
    u8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800277F4_15;   /* temp_a0_8 in func_800277F4 */

typedef struct S_800277F4_16 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_16;   /* (var_s2 + (var_s3 * 3)) in func_800277F4 */

typedef struct S_800277F4_17 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_800277F4_17;   /* slot_addr in func_800277F4 */

typedef struct S_800277F4_18 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800277F4_18;   /* temp_a0_9 in func_800277F4 */

typedef struct S_800277F4_19 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_800277F4_19;   /* runtime_addr in func_800277F4 */

typedef struct S_800277F4_20 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800277F4_20;   /* temp_s1_3 in func_800277F4 */

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
    register s32 temp_v0_4 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    register s16 var_s6_2 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 var_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_a0;
    s32 temp_a0_10;
    s32 temp_a0_4;
    s32 temp_a0_7;
    register s32 temp_a1_3 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_a2;
    s32 temp_s1_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 slot_index;
    s32 slot_flags;
    register s32 global_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_s0;
    s32 var_s3;
    register s32 var_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_v0_2;
    u8 *temp_a1;
    u8 *temp_s0_2;
    u8 *slot_addr;
    register u8 *slot_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 temp_a0_2;
    u8 temp_v0;
    u8 temp_v0_8;
    u8 temp_v1_10;
    u8 temp_v1_8;
    u8 temp_v1_9;
    u8 room_x;
    u8 room_y;
    u8 merge_key;
    register void *table_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    register void *var_a2_2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *var_s2;
    register void *var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *held0 = arg0;
    s32 one_s1;
    void *var_v0_3;
    void *var_v0_4;
    void *var_v1_4;

    {
    register void *var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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
        temp_v1 = ((S_800277F4_0 *)var_s2)->unk_14.n & ~7;
        ((S_800277F4_0 *)var_s2)->unk_14.v = temp_v1;
        temp_v1 |= temp_mask;
        ((S_800277F4_0 *)var_s2)->unk_14.n = temp_v1;
        do {
            temp_v1_2 = var_s6 << 0x10;
            ASM_KEEP_NV(temp_v1_2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            temp_a0_4 = var_s6 - 1;
            var_s6 = temp_a0_4;
            temp_v1_3 = temp_v1_2 >> 0x10;
            temp_v0_2 = clear_a3 + (temp_v1_3 * 3);
            ((S_800277F4_1 *)temp_v0_2)->unk_00 = 0;
            ((S_800277F4_1 *)temp_v0_2)->unk_02 = 0;
            clear_a1[temp_v1_3] = 0;
            clear_a2[temp_v1_3] = 0;
            ASM_KEEP_NV(temp_a0_4);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
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
            temp_v0_4 = (s16) func_800A57B4(var_s4, ((S_800277F4_2 *)temp_s0)->unk_08);
            ASM_KEEP_NV(temp_v0_4);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (temp_v0_4 >= 0) {
                sp13[temp_v0_4] = (u8) one_s1;
                temp_a0_3 = var_s4 + (temp_v0_4 * 3);
                if ((u8) ((S_800277F4_2 *)temp_s0)->unk_0A < (u8) ((S_800277F4_3 *)temp_a0_3)->unk_0A) {
                    temp_a0_5 = sp18 + (var_s6_2 * 3);
                    ((S_800277F4_4 *)temp_a0_5)->unk_00 = ((S_800277F4_3 *)temp_a0_3)->unk_08;
                    ((S_800277F4_4 *)temp_a0_5)->unk_02 = ((S_800277F4_3 *)temp_a0_3)->unk_0A;
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
                ASM_KEEP_NV(copy_dst_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                copy_dst = sp18;
                ASM_KEEP_NV(copy_dst);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                copy_src_index = (s16) temp_v0_3;

                copy_src = var_s2 + (copy_src_index * 3);

                (*(u8 *)((u8 *)copy_dst + copy_dst_offset)) = (u8) ((S_800277F4_5 *)copy_src)->unk_08;
                (*(u8 *)((u8 *)copy_dst + copy_dst_offset + 2)) = (u8) ((S_800277F4_5 *)copy_src)->unk_0A;
            }
block_16:
            var_s6_2 += 1;
        }
block_17:
        temp_v0_5 = func_8002773C(var_s4);
        if (temp_v0_5 >= 0) {
            register u8 *visited_slot ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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
            ASM_KEEP_NV(visited_slot);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            if (*visited_slot == 0) {
                temp_s1 = var_s4 + (temp_v0_5 * 3);
                temp_v0_6 = func_800A57B4(var_s2, ((S_800277F4_6 *)temp_s1)->unk_08);
                if (temp_v0_6 >= 0) {
                    sp10[temp_v0_6] = 1;
                }
                *visited_slot = 1;
                if (temp_v0_6 >= 0) {
                    temp_a1_2 = var_s2 + (temp_v0_6 * 3);
                    if ((u8) ((S_800277F4_6 *)temp_s1)->unk_0A < (u8) ((S_800277F4_7 *)temp_a1_2)->unk_0A) {
                        s32 copy_dst_index = (s16) var_s6_2;
                        s32 copy_dst_offset;
                        u8 *copy_dst;

                        copy_dst_offset = copy_dst_index * 3;
                        ASM_KEEP_NV(copy_dst_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        copy_dst = sp18;

                        copy_dst += copy_dst_offset;
                        temp_a0_2 = ((S_800277F4_7 *)temp_a1_2)->unk_08;
                        (*(u8 *)((u8 *)copy_dst + 0)) = temp_a0_2;
                        (*(u8 *)((u8 *)copy_dst + 2)) = ((S_800277F4_7 *)temp_a1_2)->unk_0A;
                        goto block_25;
                    }
                }
                {
                    s32 copy_dst_index = (s16) var_s6_2;
                    s32 copy_dst_offset;
                    u8 *copy_dst;
                    s32 copy_src_index;
                    register u8 *copy_src ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    copy_dst_offset = copy_dst_index * 3;
                    ASM_KEEP_NV(copy_dst_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    copy_dst = sp18;
                    ASM_KEEP_NV(copy_dst);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    copy_src_index = (s16) temp_v0_5;

                    copy_src = var_s4 + (copy_src_index * 3);

                    copy_dst += copy_dst_offset;
                    (*(u8 *)((u8 *)copy_dst + 0)) = (u8) ((S_800277F4_5 *)copy_src)->unk_08;
                    (*(u8 *)((u8 *)copy_dst + 2)) = (u8) ((S_800277F4_5 *)copy_src)->unk_0A;
                }
block_25:
                var_s6_2 += 1;
            }
        }
        {
            u16 merge_limit = 3;
            if ((((S_800277F4_0 *)var_s2)->unk_0E != 0) || (((S_800277F4_8 *)var_s4)->unk_0E != 0)) {
                sp30 = merge_limit;
            }
            var_s7 = 0;
        }
        var_s3 = 0;
        var_t0 = sp10;
        ASM_KEEP_NV(var_t0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        merge_out = sp18;
        ASM_KEEP_NV(merge_out);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
loop_30:
        if (var_s6_2 < (s32) sp30) {
            var_a0 = var_s4;
            if (var_s7 == 0) {
                var_a0 = var_s2;
            }
            temp_v1_6 = var_s3 >> 1;
            temp_s1_2 = temp_v1_6 * 3;
            if ((((S_800277F4_9 *)((var_a0 + temp_s1_2)))->unk_08 != 0) && (*((var_s7 * 3) + var_t0 + temp_v1_6) == 0)) {
                var_a0_2 = var_s4;
                if (var_s7 != 0) {
                    var_a0_2 = var_s2;
                }
                var_v0_3 = var_s4;
                if (var_s7 == 0) {
                    var_v0_3 = var_s2;
                }
                merge_key = ((S_800277F4_10 *)((var_v0_3 + temp_s1_2)))->unk_08;
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
                    if ((u8) ((S_800277F4_11 *)temp_a1)->unk_0A < (u8) ((S_800277F4_12 *)((var_v1 + temp_a0)))->unk_0A) {
                        var_v1 = var_s4;
                        temp_a1 = merge_out + (var_s6_2 * 3);
                        if (var_s7 != 0) {
                            var_v1 = var_s2;
                        }
                        *temp_a1 = ((S_800277F4_12 *)((var_v1 + temp_a0)))->unk_08;
                        var_v1 = var_s4;
                        if (var_s7 != 0) {
                            var_v1 = var_s2;
                        }
                        temp_a1[2] = ((S_800277F4_12 *)((var_v1 + temp_a0)))->unk_0A;
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
                    register s32 fallback_twice ASM_REG("$2") = fallback_half * 2;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    s32 fallback_offset = fallback_twice + fallback_half;
                    register u8 *fallback_source ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    u8 *second_source;

                    fallback_source = var_a2_2 + fallback_offset;

                    ((S_800277F4_13 *)temp_a3)->unk_00 = ((S_800277F4_14 *)fallback_source)->unk_08;
                    second_source = var_s4;
                    if (var_s7 == 0) {
                        second_source = var_s2;
                    }

                    fallback_source = second_source + fallback_offset;

                    ((S_800277F4_13 *)temp_a3)->unk_02 = ((S_800277F4_14 *)fallback_source)->unk_0A;
                }
block_58:
                temp_a0_8 = merge_out + (var_s6_2 * 3);
                if (((S_800277F4_15 *)temp_a0_8)->unk_00 == 0x2E) {
                    ((S_800277F4_15 *)temp_a0_8)->unk_00 = 0U;
                    ((S_800277F4_15 *)temp_a0_8)->unk_02 = 0;
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
            ASM_KEEP_NV(default_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            default_index = ((S_800277F4_0 *)var_s2)->unk_13;
            ASM_KEEP(default_index);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            default_table -= 0x784C;
            ASM_KEEP_NV(default_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            default_index += (s32) default_table;
            sp18[0] = *(u8 *) default_index;
            sp18[2] = 1;
        }
        ASM_USE_NV(var_s6_2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        terrain_table = D_8006DE24;
        tile_p = &sp10[8];
        do {
        {
        register s32 tile_test ASM_REG("$2") = tile_p[var_s3 * 3];   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(tile_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (tile_test != 0) {
            s32 tile = tile_test;
            temp_v1_7 = ((S_800277F4_0 *)var_s2)->unk_14.n;
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
        ((S_800277F4_16 *)((var_s2 + (var_s3 * 3))))->unk_08 = (u8) tile_p[var_s3 * 3];
        temp_v0_8 = tile_p[(var_s3 * 3) + 2];
        ((S_800277F4_16 *)((var_s2 + (var_s3 * 3))))->unk_0A = temp_v0_8;
        var_s3 -= 1;
        } while (var_s3 >= 0);
            {
                s32 idx_b = ((S_800277F4_8 *)var_s4)->unk_13;
                s32 idx_a = ((S_800277F4_0 *)var_s2)->unk_13;
                s32 *pb, *pa;
                s32 val_a, own;
                table_a0 = var_s2;

                temp_a1_3 = (s32) D_8006D6D8;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                temp_a2 = ((S_800277F4_8 *)var_s4)->unk_54;
                pb = (s32 *) temp_a1_3 + idx_b;
                pa = (s32 *) temp_a1_3 + idx_a;
                temp_a1_3 = *pb;
                own = ((S_800277F4_0 *)var_s2)->unk_54;
                val_a = *pa;
                temp_a1_3 &= temp_a2;
                ((S_800277F4_0 *)var_s2)->unk_54 = (s32) ((own & val_a) | temp_a1_3);
            }
            func_80041E70(table_a0, temp_a1_3, temp_a2);
            ((S_800277F4_0 *)var_s2)->unk_24.at00.v = (u16) ((u32) ((((S_800277F4_0 *)var_s2)->unk_24.at00.v + ((S_800277F4_8 *)var_s4)->unk_24) & 0xFFFF) >> 1);
            temp_v1_8 = ((S_800277F4_0 *)var_s2)->unk_66;
            if (temp_v1_8 < (u8) ((S_800277F4_0 *)var_s2)->unk_24.at01.v) {
                ((S_800277F4_0 *)var_s2)->unk_24.at01.v = temp_v1_8;
            }
            ((S_800277F4_0 *)var_s2)->unk_24.at00u.v = 0xFF;
            if (((S_800277F4_0 *)var_s2)->unk_24.at01.v != 0) {
                ((S_800277F4_0 *)var_s2)->unk_1C = (s32) (((S_800277F4_0 *)var_s2)->unk_1C & ~8);
            }
            if (arg2 == NULL) {
                func_80042984(var_s2);
            }
            if ((((S_800277F4_0 *)var_s2)->unk_48.at01.v != 0) && !(((S_800277F4_0 *)var_s2)->unk_48.at03.v & 0x20)) {
                ((S_800277F4_0 *)var_s2)->unk_48.at00.v = 0;
            }
            var_s0 = 0;
            if ((u8) ((S_800277F4_0 *)var_s2)->unk_43 < 0x40U) {
                var_s0 = ((u8) ((S_800277F4_8 *)var_s4)->unk_43 < 0x40U) * 2;
            } else {
                temp_v1_9 = ((S_800277F4_8 *)var_s4)->unk_43;
                if (temp_v1_9 < 0x40U) {
                    var_s0 = 1;

                    ((S_800277F4_0 *)var_s2)->unk_43 = temp_v1_9;
                    var_v0_2 = var_s0;
                    ASM_KEEP_NV(var_v0_2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    ((S_800277F4_0 *)var_s2)->unk_44 = (s8) var_v0_2;
                }
            }
            if (arg2 == NULL) {
                func_800A31D0(var_s4);
                func_800A18E8(((S_800277F4_8 *)var_s4)->unk_13, 3);
                slot_index = func_800A1BD0(var_s4);
                {
#ifdef NON_MATCHING
                    u8 *slot_page = D_80080000;
#else
                    u8 *slot_page = (u8 *) 0x80080000;
#endif
                    ASM_KEEP_NV(slot_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    slot_base = *(u8 **) (slot_page + 0x14A8);
                }
                slot_addr = (u8 *) (((s32) (slot_index << 0x10) >> 0xE) + (s32) slot_base);
                ASM_KEEP_NV(slot_addr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                slot_flags = ((S_800277F4_8 *)var_s4)->unk_1C & 0x2000;
                temp_a0_9 = ((S_800277F4_8_pre *)var_s4)[-1].unk_00;
                temp_s1_3 = ((S_800277F4_17 *)slot_addr)->unk_D0;
                room_x = ((S_800277F4_18 *)temp_a0_9)->unk_24;
                room_y = ((S_800277F4_18 *)temp_a0_9)->unk_25;
                ASM_KEEP(slot_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                var_a2_3 = 0x3000;
                if (slot_flags != 0) {
                    var_a2_3 = 0x300;
                }
                func_8009A3D0(room_x, room_y, var_a2_3);
                func_8009A028(var_s4);
                if (var_s0 == 1) {
#ifdef NON_MATCHING
                    D_80010980[((S_800277F4_8 *)var_s4)->unk_43 * 4] = ((S_800277F4_0 *)var_s2)->unk_13;
#else
                    u8 *room_page = (u8 *) 0x80010000;

                    room_page[0x980 + (((S_800277F4_8 *)var_s4)->unk_43 * 4)] = ((S_800277F4_0 *)var_s2)->unk_13;
#endif
                    ((S_800277F4_8 *)var_s4)->unk_43 = 0xFF;
                } else if (var_s0 == 2) {
#ifdef NON_MATCHING
                    *(s32 *) &D_80010980[((S_800277F4_8 *)var_s4)->unk_43 * 4] = 0;
#else
                    u32 room_base = 0x80010000;
                    s32 room_index;
                    room_index = ((S_800277F4_8 *)var_s4)->unk_43;

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
                    ASM_KEEP_NV(slot_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    runtime_base = *(u8 **) (slot_page + 0x14A8);
                    runtime_addr = (u8 *) (((s32) (slot_index << 0x10) >> 0xE) + (s32) runtime_base);

                    ((S_800277F4_19 *)runtime_addr)->unk_D0 = 0;
                }
                func_8003DB4C(&D_800E3E48[(((S_800277F4_20 *)temp_s1_3)->unk_03 & 0x1F) * 0x8C], 0x23);
                {
                    register void *destroy_arg ASM_REG("$4") = temp_s1_3;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP_NV(destroy_arg);
#ifdef NON_MATCHING
                    D_800E3DF0[((S_800277F4_20 *)temp_s1_3)->unk_03 & 0x1F] = 0;
#else
                    {
                        u32 dead_base = 0x800E0000;
                        s32 dead_index;
                        ASM_KEEP_NV(dead_base);
                        dead_index = ((S_800277F4_20 *)temp_s1_3)->unk_03;
                        ASM_KEEP(dead_index);
                        dead_base += 0x3DF0;
                        ASM_KEEP_NV(dead_base);
                        *(u32 *) (dead_base + ((dead_index & 0x1F) * 4)) = 0;
                    }
#endif
                    func_80098B38(destroy_arg);
                }
                temp_a0_10 = ((S_800277F4_0 *)var_s2)->unk_54;
                if ((temp_a0_10 & 0x800000) &&
                    ((temp_v1_10 = ((S_800277F4_0 *)var_s2)->unk_13) != 2) &&
                    (temp_v1_10 != 0x39)) {
                    ((S_800277F4_0 *)var_s2)->unk_54 = (s32) (temp_a0_10 & 0xFF7FFFFF);
                }
                (*(u16 *)((u8 *)var_s4 + -2)) = (u16) (((S_800277F4_8_pre *)var_s4)[-1].unk_12 | 0x8000);
                global_flags = *(s32 *) (D_80080000 + 0x14A0);
                global_flags |= 0x8000;
                *(s32 *) (D_80080000 + 0x14A0) = global_flags;
                return var_s2;
            }
            return var_s2;
    }
    return var_s2;
}
