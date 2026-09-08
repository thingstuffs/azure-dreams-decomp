#include "common.h"
#include "m2c_compat.h"

typedef struct S_80095C80_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_0;   /* base in func_80095C80 */

typedef struct S_80095C80_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80095C80_1;   /* arg0 in func_80095C80 */

typedef struct S_80095C80_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_2;   /* var_a0 in func_80095C80 */

typedef struct S_80095C80_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_3;   /* var_a0_2 in func_80095C80 */

typedef struct S_80095C80_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_4;   /* (M2C_UNK *)neg_work in func_80095C80 */

typedef struct S_80095C80_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_5;   /* var_a0_3 in func_80095C80 */

typedef struct S_80095C80_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_6;   /* var_a0_4 in func_80095C80 */

typedef struct S_80095C80_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_7;   /* final_base in func_80095C80 */


s32 func_80095BC0();                  /* extern */
s32 func_80095BF0();                  /* extern */
s32 func_80095C20();             /* extern */
s32 func_80095C50();             /* extern */
void func_800961A8(void *);                 /* extern */
void func_800961D8(void *);                 /* extern */
extern s32 D_800FE5C0[];
#ifdef NON_MATCHING
#define D_80100000 ((s32 *)((s8 *)D_800FE5C0 + 0x1A40))
#else
#define D_80100000 ((s32 *)0x80100000)
#endif

void func_80095C80(S_80095C80_1 *arg0) {
    struct {
        s32 x;
        s32 y;
        s32 z;
        s32 pad3;
        s32 pad4;
    } sp10;
    M2C_UNK *base;
    M2C_UNK *var_a0;
    M2C_UNK *var_a0_2;
    M2C_UNK *var_a0_3;
    M2C_UNK *var_a0_4;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s16 var_v1;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    register s32 temp_v1_3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK *neg_page;

    neg_page = (M2C_UNK *)D_80100000;
    ASM_KEEP_NV(neg_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    base = (M2C_UNK *)((s8 *)neg_page - 0x1A40);
    {
        if (((S_80095C80_0 *)base)->unk_0C <= 0) {
            goto block_24_low;
        }
        if (((S_80095C80_0 *)base)->unk_10 > 0) {
            register s32 collision_x ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 return_x;
            register s32 coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            void *next_a0;
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_0 *)base)->unk_0C;
            sp10.y = arg0->unk_04.at00.v;
            sp10.z = arg0->unk_08;
            return_x = func_80095BC0(&sp10, 0);
            next_a0 = &sp10;
            ASM_KEEP_NV(next_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            collision_x = arg0->unk_00.at00.v;
            sp10.x = collision_x;
            collision_x = collision_x < (return_x << 0x10);
            coord = arg0->unk_04.at00.v;
            ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            temp_a1 = ((S_80095C80_0 *)base)->unk_10;
            collision_x ^= 1;
            sp10.y = coord - temp_a1;
            coord = arg0->unk_08;
            sp10.z = coord;
            return_x = func_80095C20(next_a0, 0);
            coord = arg0->unk_04.at00.v;
            return_x <<= 0x10;
            coord = coord < return_x;
            return_x = coord ^ 1;
            if (collision_x == 0) {
                var_a0 = (M2C_UNK *)D_80100000;
                if (return_x == 0) {
                    s32 angle_x;
                    s32 angle_y;
                    angle_x = arg0->unk_00.at02.v;
                    angle_y = arg0->unk_04.at02.v;
                    angle_x &= 0x3F;
                    angle_y &= 0x3F;
                    angle_x = angle_x < angle_y;
                    if (angle_x == 0) {
                        goto block_57;
                    }
                    goto call_a8;
                }
                goto block_8;
            }
            var_a0 = (M2C_UNK *)D_80100000;
block_8:
            var_a0 = (M2C_UNK *)((s8 *)var_a0 - 0x1A40);
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_2 *)var_a0)->unk_0C;
            temp_v0 = arg0->unk_04.at00.v;
            ASM_KEEP_NV(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            temp_v1 = ((S_80095C80_2 *)var_a0)->unk_10;
            ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            temp_a1 = 0;
            ASM_KEEP_NV(temp_a1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sp10.y = temp_v0 - temp_v1;
            sp10.z = arg0->unk_08 - temp_v1;
            temp_v1 = arg0->unk_00.at00.v < (func_80095BC0(&sp10, temp_a1) << 0x10);
            temp_v1 ^= 1;
            if (temp_v1 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        if (((S_80095C80_0 *)base)->unk_10 < 0) {
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_0 *)base)->unk_0C;
            sp10.y = arg0->unk_04.at00.v;
            sp10.z = arg0->unk_08;
            temp_s0_2 = arg0->unk_00.at00.v < (func_80095BC0(&sp10, 1) << 0x10);
            temp_s0_2 ^= 1;
            sp10.x = arg0->unk_00.at00.v;
            sp10.y = arg0->unk_04.at00.v - ((S_80095C80_0 *)base)->unk_10;
            sp10.z = arg0->unk_08;
            temp_v0_4 = (func_80095C50(&sp10, 0) << 0x10) >= arg0->unk_04.at00.v;
            if (temp_s0_2 == 0) {
                var_a0_2 = (M2C_UNK *)D_80100000;
                if (temp_v0_4 == 0) {
                    s32 angle_x2;
                    angle_x2 = arg0->unk_00.at02.v;
                    temp_v1_3 = (s16) arg0->unk_04.at02.v;
                    angle_x2 &= 0x3F;
                    ASM_KEEP_NV(angle_x2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    if (temp_v1_3 < 0) {
                        temp_v1_3 = 0 - temp_v1_3;
                    }
                    temp_v1_3 &= 0x3F;
                    angle_x2 = angle_x2 < temp_v1_3;
                    if (angle_x2 != 0) {
                        goto call_a8;
                    }
                    goto block_57;
                }
                goto block_20;
            }
            var_a0_2 = (M2C_UNK *)D_80100000;
block_20:
            var_a0_2 = (M2C_UNK *)((s8 *)var_a0_2 - 0x1A40);
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_3 *)var_a0_2)->unk_0C;
            temp_v0_2 = arg0->unk_04.at00.v;
            ASM_KEEP_NV(temp_v0_2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            temp_v1_2 = ((S_80095C80_3 *)var_a0_2)->unk_10;
            ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            temp_a1 = 1;
            ASM_KEEP_NV(temp_a1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sp10.y = temp_v0_2 - temp_v1_2;
            sp10.z = arg0->unk_08 - temp_v1_2;
            temp_v1_2 = arg0->unk_00.at00.v >= (func_80095BC0(&sp10, temp_a1) << 0x10);
            ASM_KEEP_NV(temp_v1_2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (temp_v1_2 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        goto block_24;
    }
block_24:
    {
    unsigned long neg_work;
    neg_page = (M2C_UNK *)D_80100000;
block_24_low:
    neg_work = (unsigned long)((s8 *)neg_page - 0x1A40);
    {
        if (((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_0C >= 0) {
            goto block_52_low;
        }
        if (((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_10 > 0) {
            register s32 neg_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            register s32 neg_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 neg_return;
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_0C;
            sp10.y = arg0->unk_04.at00.v;
            sp10.z = arg0->unk_08;
            temp_v0_5 = func_80095BF0(&sp10, 0);
            temp_a2 = arg0->unk_00.at00.v;
            sp10.x = temp_a2;
            neg_coord = arg0->unk_04.at00.v;
            neg_a1 = ((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_10;
            neg_work = temp_v0_5 << 0x10;
            neg_work = (s32)neg_work < temp_a2;
            neg_work ^= 1;
            sp10.y = neg_coord - neg_a1;
            neg_coord = arg0->unk_08;
            sp10.z = neg_coord;
            neg_return = func_80095C20(&sp10, 1, temp_a2);
            neg_coord = arg0->unk_04.at00.v;
            neg_return <<= 0x10;
            neg_coord = neg_coord < neg_return;
            neg_return = neg_coord ^ 1;
            if (neg_work == 0) {
                var_a0_3 = (M2C_UNK *)D_80100000;
                if (neg_return == 0) {
                    s32 angle_y3;
                    temp_v1_3 = (s16) arg0->unk_00.at02.v;
                    angle_y3 = arg0->unk_04.at02.v;
                    if (temp_v1_3 < 0) {
                        temp_v1_3 = 0 - temp_v1_3;
                    }
                    temp_v1_3 &= 0x3F;
                    angle_y3 &= 0x3F;
                    if (temp_v1_3 < angle_y3) {
                        goto call_a8;
                    }
                    goto block_57;
                }
                goto block_34;
            }
            var_a0_3 = (M2C_UNK *)D_80100000;
block_34:
            var_a0_3 = (M2C_UNK *)((s8 *)var_a0_3 - 0x1A40);
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_5 *)var_a0_3)->unk_0C;
            temp_v0_3 = arg0->unk_04.at00.v;
            ASM_KEEP_NV(temp_v0_3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            neg_coord = ((S_80095C80_5 *)var_a0_3)->unk_10;
            ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            neg_a1 = 0;
            ASM_KEEP_NV(neg_a1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sp10.y = temp_v0_3 - neg_coord;
            sp10.z = arg0->unk_08 - neg_coord;
            temp_v1_3 = (func_80095BF0(&sp10, neg_a1) << 0x10) < arg0->unk_00.at00.v;
            temp_v1_3 ^= 1;
            if (temp_v1_3 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        if (((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_10 < 0) {
            register s32 neg2_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            register s32 neg2_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_0C;
            sp10.y = arg0->unk_04.at00.v;
            sp10.z = arg0->unk_08;
            temp_v0_7 = func_80095BF0(&sp10, 1);
            temp_a2_2 = arg0->unk_00.at00.v;
            sp10.x = temp_a2_2;
            neg2_coord = arg0->unk_04.at00.v;
            neg2_a1 = ((S_80095C80_4 *)((M2C_UNK *)neg_work))->unk_10;
            neg_work = temp_v0_7 << 0x10;
            neg_work = (s32)neg_work < temp_a2_2;
            neg_work ^= 1;
            sp10.y = neg2_coord - neg2_a1;
            neg2_coord = arg0->unk_08;
            sp10.z = neg2_coord;
            temp_v1_3 = func_80095C50(&sp10, 1, temp_a2_2);
            neg2_coord = arg0->unk_04.at00.v;
            temp_v1_3 <<= 0x10;
            temp_v1_3 = temp_v1_3 < neg2_coord;
            temp_v1_3 ^= 1;
            if (neg_work == 0) {
                var_a0_4 = (M2C_UNK *)D_80100000;
                if (temp_v1_3 == 0) {
                    s32 angle_y4;
                    temp_v1_3 = (s16) arg0->unk_00.at02.v;
                    angle_y4 = (s16) arg0->unk_04.at02.v;
                    if (temp_v1_3 < 0) {
                        temp_v1_3 = 0 - temp_v1_3;
                    }
                    temp_v1_3 &= 0x3F;
                    ASM_KEEP_NV(temp_v1_3);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    if (angle_y4 < 0) {
                        angle_y4 = -angle_y4;
                    }
                    angle_y4 &= 0x3F;
                    if (temp_v1_3 < angle_y4) {
                        goto call_d8;
                    }
                    goto call_a8;
                }
                goto block_48;
            }
            var_a0_4 = (M2C_UNK *)D_80100000;
block_48:
            var_a0_4 = (M2C_UNK *)((s8 *)var_a0_4 - 0x1A40);
            sp10.x = arg0->unk_00.at00.v - ((S_80095C80_6 *)var_a0_4)->unk_0C;
            temp_v0_6 = arg0->unk_04.at00.v;
            ASM_KEEP_NV(temp_v0_6);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            neg2_coord = ((S_80095C80_6 *)var_a0_4)->unk_10;
            ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            neg2_a1 = 1;
            ASM_KEEP_NV(neg2_a1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sp10.y = temp_v0_6 - neg2_coord;
            sp10.z = arg0->unk_08 - neg2_coord;
            temp_v1_3 = (func_80095BF0(&sp10, neg2_a1) << 0x10) >= arg0->unk_00.at00.v;
            ASM_KEEP_NV(temp_v1_3);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (temp_v1_3 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        goto block_52;
    }
    }
block_52:
    {
    M2C_UNK *final_base;
    neg_page = (M2C_UNK *)D_80100000;
block_52_low:
    final_base = (M2C_UNK *)((s8 *)neg_page - 0x1A40);
    if (((S_80095C80_7 *)final_base)->unk_0C == 0) {
        goto check_final_y;
    }
    if (((S_80095C80_7 *)final_base)->unk_10 != 0) {
        goto done;
    }

call_a8:
    func_800961A8(arg0);
    goto done;

check_final_y:
    if (((S_80095C80_7 *)final_base)->unk_10 == 0) {
        goto done;
    }

block_57:
call_d8:
    func_800961D8(arg0);
    }

done:
    return;
}
