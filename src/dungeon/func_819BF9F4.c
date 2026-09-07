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

void func_800251F4(s32 unused, s32 center, s16 coord2, s16 coord3)
{
    s32 held_center;
    volatile struct {
        s16 coord2;
        u8 pad0[6];
        s16 coord3;
        u8 pad1[6];
        s16 iteration;
    } stack;
    void *object;
    u8 *work;
    register void *sub ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    void *preset;
    s32 copy0;
    s32 copy4;
    s32 copy1;
    s32 copy2;
    register s32 copy3 ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 copy5 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 random_x;
    s32 random_y;
    s32 span;
    s32 step;
    s32 low;
    s32 high;
    s32 low_y;
    s32 high_y;
    s32 factor;
    register s32 scratch ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 edge_product ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    register s32 edge ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 inner;
    s32 coord3_value;
    u32 call_center;
    register u32 call_coord2 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 coord_raw ASM_REG("$8");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 coord_scratch ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    void *data_first;
    void *data_second;
    s32 color;
    s32 random_pos;
    s32 center_base;
    register u32 iteration_raw ASM_REG("$8");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 iteration_next ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    stack.coord2 = coord2;
    stack.coord3 = coord3;
    stack.iteration = 0;
    held_center = center;
    color = 0x80;
    do {
        object = func_8003FC64(0x212);
        work = (u8 *)object + 0x20;
        if (object != 0) {
            ((S_800251F4_0 *)work)->unk_28 = 0x78;
            ((S_800251F4_0 *)work)->unk_2C = func_80069EF8() & 1;
            ((S_800251F4_1 *)object)->unk_10 = D_80025088;
            func_8004491C(object, D_80025034);

            sub = ((S_800251F4_1 *)object)->unk_0C;
            ((S_800251F4_2 *)sub)->unk_10 = 0x20;
            ((S_800251F4_2 *)sub)->unk_14 |= 0xC;

            random_pos = func_80069EF8();
            center_base = held_center - 0x20;
            ((S_800251F4_5 *)(((S_800251F4_1 *)object)->unk_08))->unk_02 =
                center_base + (random_pos & 0x3F);
            random_pos = func_80069EF8();
            call_center = (u16)held_center;
            ASM_KEEP(call_center);   /* MATCH pin: keeps a statement from moving across a call/branch */
            random_pos &= 0x3F;
            call_coord2 = (u16)stack.coord2;
            coord_raw = (u16)stack.coord2;
            data_first = ((S_800251F4_1 *)object)->unk_08;
            ASM_KEEP(data_first);   /* MATCH pin: load-bearing for the whole function shape */
            coord_scratch = coord_raw - 0x20;
            coord_scratch += random_pos;
            ((S_800251F4_3 *)data_first)->unk_06 = coord_scratch;
            coord_raw = (u16)stack.coord3;
            data_second = ((S_800251F4_1 *)object)->unk_08;
            coord3_value = (s16)coord_raw;
            ((S_800251F4_4 *)data_second)->unk_0A = coord_raw;

            preset = func_80024064(call_center, call_coord2,
                                   (s16)coord3_value);
            copy0 = UNALIGNED(preset, 0);
            copy4 = UNALIGNED(preset, 4);
            copy1 = UNALIGNED(preset, 8);
            copy2 = UNALIGNED(preset, 0xC);
            UNALIGNED(object, 0x52) = copy0;
            UNALIGNED(object, 0x56) = copy4;
            UNALIGNED(object, 0x5A) = copy1;
            UNALIGNED(object, 0x5E) = copy2;
            copy3 = UNALIGNED(preset, 0x10);
            copy5 = UNALIGNED(preset, 0x14);
            UNALIGNED(object, 0x62) = copy3;
            UNALIGNED(object, 0x66) = copy5;

            if (((S_800251F4_0 *)work)->unk_3A > ((S_800251F4_0 *)work)->unk_44) {
                low = ((S_800251F4_0 *)work)->unk_44;
                high = (*(volatile u8 *)((u8 *)work + 0x3A)) + 1;
            } else {
                low = ((S_800251F4_0 *)work)->unk_3A;
                high = ((S_800251F4_0 *)work)->unk_44 + 1;
            }

            if (((S_800251F4_0 *)work)->unk_3B > ((S_800251F4_0 *)work)->unk_3F) {
                low_y = ((S_800251F4_0 *)work)->unk_3F;
                high_y = (*(volatile u8 *)((u8 *)work + 0x3B)) + 1;
            } else {
                low_y = ((S_800251F4_0 *)work)->unk_3B;
                high_y = ((S_800251F4_0 *)work)->unk_3F + 1;
            }

            random_x = func_80069EF8() & 3;
            random_y = func_80069EF8() & 3;
            span = high - low;
            if (span < 0) {
                span += 3;
            }
            factor = random_x;
            scratch = factor + 1;
            step = span >> 2;
            edge_product = scratch * step;
            factor = factor * step;
            span = high_y - low_y;
            scratch = low;
            edge = scratch + edge_product - 1;
            ((S_800251F4_0 *)work)->unk_3E = edge;
            ((S_800251F4_0 *)work)->unk_3A = edge;
            inner = scratch + factor;
            ((S_800251F4_0 *)work)->unk_46 = inner;
            ((S_800251F4_0 *)work)->unk_44 = inner;

            if (span < 0) {
                span += 3;
            }
            factor = random_y;
            scratch = factor + 1;
            step = span >> 2;
            edge_product = scratch * step;
            factor = factor * step;
            scratch = low_y;
            edge = scratch + edge_product - 1;
            ((S_800251F4_0 *)work)->unk_47 = edge;
            ((S_800251F4_0 *)work)->unk_3F = edge;
            inner = scratch + factor;
            ((S_800251F4_0 *)work)->unk_45 = inner;
            ((S_800251F4_0 *)work)->unk_3B = inner;

            sub = ((S_800251F4_1 *)object)->unk_0C;
            ((S_800251F4_2 *)sub)->unk_1E = 0x1000;
            ((S_800251F4_2 *)sub)->unk_1C = 0x1000;

            ((S_800251F4_0 *)work)->unk_4A = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)work)->unk_4C = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)work)->unk_4E = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)work)->unk_50 = (func_80069EF8() & 3) + 1;
            ((S_800251F4_0 *)work)->unk_52 = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)work)->unk_54 = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)work)->unk_56 = (func_80069EF8() & 3) - 5;
            ((S_800251F4_0 *)work)->unk_58 = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)work)->unk_5A = (func_80069EF8() & 3) + 1;
            ((S_800251F4_0 *)work)->unk_5C = (func_80069EF8() & 3) + 1;
            ((S_800251F4_0 *)work)->unk_5E = (func_80069EF8() & 3) - 2;
            ((S_800251F4_0 *)work)->unk_60 = (func_80069EF8() & 3) + 1;

            ((S_800251F4_0 *)work)->unk_0E = color;
            ((S_800251F4_0 *)work)->unk_0D = color;
            ((S_800251F4_0 *)work)->unk_0C = color;
            ((S_800251F4_0 *)work)->unk_12 = color;
            ((S_800251F4_0 *)work)->unk_11 = color;
            ((S_800251F4_0 *)work)->unk_10 = color;
            ((S_800251F4_0 *)work)->unk_16 = color;
            ((S_800251F4_0 *)work)->unk_15 = color;
            ((S_800251F4_0 *)work)->unk_14 = color;
            ((S_800251F4_0 *)work)->unk_1A = color;
            ((S_800251F4_0 *)work)->unk_19 = color;
            ((S_800251F4_0 *)work)->unk_18 = color;

            ((S_800251F4_2 *)sub)->unk_16 = func_80069EF8() & 0xFFF;
            ((S_800251F4_2 *)sub)->unk_18 = func_80069EF8() & 0xFFF;
            ((S_800251F4_2 *)sub)->unk_1A = func_80069EF8() & 0xFFF;
            ((S_800251F4_0 *)work)->unk_7C = ((func_80069EF8() & 0x7FFF) - 0x4000) << 5;
            ((S_800251F4_0 *)work)->unk_80 = ((func_80069EF8() & 0x7FFF) - 0x4000) << 5;
            ((S_800251F4_0 *)work)->unk_84 =
                (((func_80069EF8() & 0x7FFF) - 0x6000) << 6) + (s32)0xFFFE0000;
            ((S_800251F4_0 *)work)->unk_90 = 0x10000;

            ((S_800251F4_2 *)sub)->unk_0E = color;
            ((S_800251F4_2 *)sub)->unk_0D = color;
            ((S_800251F4_2 *)sub)->unk_0C = color;
            func_8003DB94(sub, &D_800DE870, 0);
        }
        iteration_raw = (u16)stack.iteration;
        ASM_KEEP(iteration_raw);   /* MATCH pin: load-bearing for the whole function shape */
        iteration_next = iteration_raw + 1;
        stack.iteration = iteration_next;
    } while ((s16)iteration_next < 4);
}
