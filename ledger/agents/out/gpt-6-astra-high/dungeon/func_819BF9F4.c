#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800251F4_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
    u8 pad_1B[0xD];
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    u8 pad_2E[0xC];
    u8 unk_3A;
    u8 unk_3B;
    u8 pad_3C[0x2];
    u8 unk_3E;
    u8 unk_3F;
    u8 pad_40[0x4];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 pad_48[0x2];
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0x1A];
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    u8 pad_88[0x8];
    s32 unk_90;
} S_800251F4_0;   /* work in func_800251F4 */

typedef struct S_800251F4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800251F4_1;   /* object in func_800251F4 */

typedef struct S_800251F4_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800251F4_2;   /* sub in func_800251F4 */

typedef struct S_800251F4_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800251F4_3;   /* data_first in func_800251F4 */

typedef struct S_800251F4_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800251F4_4;   /* data_second in func_800251F4 */

typedef struct S_800251F4_5 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800251F4_5;   /* ((S_800251F4_1 *)object)->unk_08 in func_800251F4 */

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;
typedef struct {
    s32 value;
} __attribute__((packed)) UNALIGNED32;

#define UNALIGNED(expr, offset) (((UNALIGNED32 *)((u8 *)(expr) + (offset)))->value)

extern void *func_80024064(u32, s32, s32);
extern void func_8003DB94(void *, M2C_UNK *, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, RECT *);
extern s32 func_80069EF8(void);

extern RECT D_80025034[2];
extern M2C_UNK D_80025088[2];
extern M2C_UNK D_800DE870;

/* Spawns four textured particles with randomized positions, motion, and rotation. */
void func_800251F4(s32 unused, s32 center_x, s16 center_y, s16 center_z)
{
    s32 saved_x;
    volatile struct {
        s16 coord2;
        u8 pad0[6];
        s16 coord3;
        u8 pad1[6];
        s16 iteration;
    } stack;
    void *particle;
    u8 *particle_work;
    register void *transform ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    void *quad_template;
    s32 quad_word_0;
    s32 quad_word_1;
    s32 quad_word_2;
    s32 quad_word_3;
    register s32 quad_word_4 ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 quad_word_5 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 tile_u;
    s32 tile_v;
    s32 uv_span;
    s32 tile_size;
    s32 min_u;
    s32 end_u;
    s32 min_v;
    s32 end_v;
    s32 tile_offset;
    register s32 uv_scratch ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 tile_end_offset ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    register s32 tile_max ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 tile_min;
    s32 signed_z;
    u32 template_x;
    register u32 template_y ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 coord_bits ASM_REG("$8");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 particle_y ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    void *y_position;
    void *z_position;
    s32 brightness;
    s32 position_jitter;
    s32 min_x;
    register u32 particle_index ASM_REG("$8");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 next_particle ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    stack.coord2 = center_y;
    stack.coord3 = center_z;
    stack.iteration = 0;
    saved_x = center_x;
    brightness = 0x80;
    do {
        particle = func_8003FC64(0x212);
        particle_work = (u8 *)particle + 0x20;
        if (particle != 0) {
            ((S_800251F4_0 *)particle_work)->unk_28 = 0x78;
            ((S_800251F4_0 *)particle_work)->unk_2C = func_80069EF8() & 1;
            ((S_800251F4_1 *)particle)->unk_10 = D_80025088;
            func_8004491C(particle, D_80025034);

            transform = ((S_800251F4_1 *)particle)->unk_0C;
            ((S_800251F4_2 *)transform)->unk_10 = 0x20;
            ((S_800251F4_2 *)transform)->unk_14 |= 0xC;

            position_jitter = func_80069EF8();
            min_x = saved_x - 0x20;
            ((S_800251F4_5 *)(((S_800251F4_1 *)particle)->unk_08))->unk_02 =
                min_x + (position_jitter & 0x3F);
            position_jitter = func_80069EF8();
            template_x = (u16)saved_x;
            ASM_KEEP(template_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
            position_jitter &= 0x3F;
            template_y = (u16)stack.coord2;
            coord_bits = (u16)stack.coord2;
            y_position = ((S_800251F4_1 *)particle)->unk_08;
            ASM_KEEP(y_position);   /* MATCH pin: load-bearing for the whole function shape */
            particle_y = coord_bits - 0x20;
            particle_y += position_jitter;
            ((S_800251F4_3 *)y_position)->unk_06 = particle_y;
            coord_bits = (u16)stack.coord3;
            z_position = ((S_800251F4_1 *)particle)->unk_08;
            signed_z = (s16)coord_bits;
            ((S_800251F4_4 *)z_position)->unk_0A = coord_bits;

            quad_template = func_80024064(template_x, template_y,
                                           (s16)signed_z);
            quad_word_0 = UNALIGNED(quad_template, 0);
            quad_word_1 = UNALIGNED(quad_template, 4);
            quad_word_2 = UNALIGNED(quad_template, 8);
            quad_word_3 = UNALIGNED(quad_template, 0xC);
            UNALIGNED(particle, 0x52) = quad_word_0;
            UNALIGNED(particle, 0x56) = quad_word_1;
            UNALIGNED(particle, 0x5A) = quad_word_2;
            UNALIGNED(particle, 0x5E) = quad_word_3;
            quad_word_4 = UNALIGNED(quad_template, 0x10);
            quad_word_5 = UNALIGNED(quad_template, 0x14);
            UNALIGNED(particle, 0x62) = quad_word_4;
            UNALIGNED(particle, 0x66) = quad_word_5;

            if (((S_800251F4_0 *)particle_work)->unk_3A > ((S_800251F4_0 *)particle_work)->unk_44) {
                min_u = ((S_800251F4_0 *)particle_work)->unk_44;
                end_u = (*(volatile u8 *)((u8 *)particle_work + 0x3A)) + 1;
            } else {
                min_u = ((S_800251F4_0 *)particle_work)->unk_3A;
                end_u = ((S_800251F4_0 *)particle_work)->unk_44 + 1;
            }

            if (((S_800251F4_0 *)particle_work)->unk_3B > ((S_800251F4_0 *)particle_work)->unk_3F) {
                min_v = ((S_800251F4_0 *)particle_work)->unk_3F;
                end_v = (*(volatile u8 *)((u8 *)particle_work + 0x3B)) + 1;
            } else {
                min_v = ((S_800251F4_0 *)particle_work)->unk_3B;
                end_v = ((S_800251F4_0 *)particle_work)->unk_3F + 1;
            }

            tile_u = func_80069EF8() & 3;
            tile_v = func_80069EF8() & 3;
            uv_span = end_u - min_u;
            if (uv_span < 0) {
                uv_span += 3;
            }
            tile_offset = tile_u;
            uv_scratch = tile_offset + 1;
            tile_size = uv_span >> 2;
            tile_end_offset = uv_scratch * tile_size;
            tile_offset = tile_offset * tile_size;
            uv_span = end_v - min_v;
            uv_scratch = min_u;
            tile_max = uv_scratch + tile_end_offset - 1;
            ((S_800251F4_0 *)particle_work)->unk_3E = tile_max;
            ((S_800251F4_0 *)particle_work)->unk_3A = tile_max;
            tile_min = uv_scratch + tile_offset;
            ((S_800251F4_0 *)particle_work)->unk_46 = tile_min;
            ((S_800251F4_0 *)particle_work)->unk_44 = tile_min;

            if (uv_span < 0) {
                uv_span += 3;
            }
            tile_offset = tile_v;
            uv_scratch = tile_offset + 1;
            tile_size = uv_span >> 2;
            tile_end_offset = uv_scratch * tile_size;
            tile_offset = tile_offset * tile_size;
            uv_scratch = min_v;
            tile_max = uv_scratch + tile_end_offset - 1;
            ((S_800251F4_0 *)particle_work)->unk_47 = tile_max;
            ((S_800251F4_0 *)particle_work)->unk_3F = tile_max;
            tile_min = uv_scratch + tile_offset;
            ((S_800251F4_0 *)particle_work)->unk_45 = tile_min;
            ((S_800251F4_0 *)particle_work)->unk_3B = tile_min;

            transform = ((S_800251F4_1 *)particle)->unk_0C;
            ((S_800251F4_2 *)transform)->unk_1E = 0x1000;
            ((S_800251F4_2 *)transform)->unk_1C = 0x1000;

            ((S_800251F4_0 *)particle_work)->unk_4A = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_4C = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_4E = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_50 = (func_80069EF8() & 3) + 1;
            ((S_800251F4_0 *)particle_work)->unk_52 = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_54 = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_56 = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)particle_work)->unk_58 = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_5A = (func_80069EF8() & 3) + 1;
            ((S_800251F4_0 *)particle_work)->unk_5C = (func_80069EF8() & 3) + 1;
            ((S_800251F4_0 *)particle_work)->unk_5E = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)particle_work)->unk_60 = (func_80069EF8() & 3) + 1;

            ((S_800251F4_0 *)particle_work)->unk_0E = brightness;
            ((S_800251F4_0 *)particle_work)->unk_0D = brightness;
            ((S_800251F4_0 *)particle_work)->unk_0C = brightness;
            ((S_800251F4_0 *)particle_work)->unk_12 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_11 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_10 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_16 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_15 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_14 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_1A = brightness;
            ((S_800251F4_0 *)particle_work)->unk_19 = brightness;
            ((S_800251F4_0 *)particle_work)->unk_18 = brightness;

            ((S_800251F4_2 *)transform)->unk_16 = func_80069EF8() & 0xFFF;
            ((S_800251F4_2 *)transform)->unk_18 = func_80069EF8() & 0xFFF;
            ((S_800251F4_2 *)transform)->unk_1A = func_80069EF8() & 0xFFF;
            ((S_800251F4_0 *)particle_work)->unk_7C = ((func_80069EF8() & 0x7FFF) - 0x4000) << 5;
            ((S_800251F4_0 *)particle_work)->unk_80 = ((func_80069EF8() & 0x7FFF) - 0x4000) << 5;
            ((S_800251F4_0 *)particle_work)->unk_84 =
                (((func_80069EF8() & 0x7FFF) - 0x6000) << 6) + (s32)0xFFFE0000;
            ((S_800251F4_0 *)particle_work)->unk_90 = 0x10000;

            ((S_800251F4_2 *)transform)->unk_0E = brightness;
            ((S_800251F4_2 *)transform)->unk_0D = brightness;
            ((S_800251F4_2 *)transform)->unk_0C = brightness;
            func_8003DB94(transform, &D_800DE870, 0);
        }
        particle_index = (u16)stack.iteration;
        ASM_KEEP(particle_index);   /* MATCH pin: load-bearing for the whole function shape */
        next_particle = particle_index + 1;
        stack.iteration = next_particle;
    } while ((s16)next_particle < 4);
}
