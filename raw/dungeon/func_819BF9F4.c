#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;
typedef struct {
    s32 value;
} __attribute__((packed)) UNALIGNED32;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))
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
    register void *object ASM_REG("$18");
    u8 *work;
    register void *sub ASM_REG("$17");
    void *preset;
    s32 copy0;
    s32 copy4;
    s32 copy1;
    s32 copy2;
    register s32 copy3 ASM_REG("$3");
    register s32 copy5 ASM_REG("$4");
    s32 random_x;
    register s32 random_y ASM_REG("$6");
    register s32 span ASM_REG("$5");
    register s32 step ASM_REG("$2");
    s32 low;
    s32 high;
    register s32 low_y ASM_REG("$21");
    s32 high_y;
    register s32 factor ASM_REG("$4");
    register s32 scratch ASM_REG("$3");
    register s32 edge_product ASM_REG("$9");
    register s32 edge ASM_REG("$2");
    s32 inner;
    s32 coord3_value;
    register u32 call_center ASM_REG("$4");
    register u32 call_coord2 ASM_REG("$5");
    register u32 coord_raw ASM_REG("$8");
    register s32 coord_scratch ASM_REG("$3");
    register void *data_first ASM_REG("$6");
    register void *data_second ASM_REG("$2");
    s32 color;
    s32 random_pos;
    s32 center_base;
    register u32 iteration_raw ASM_REG("$8");
    register s32 iteration_next ASM_REG("$2");

    stack.coord2 = coord2;
    stack.coord3 = coord3;
    stack.iteration = 0;
    held_center = center;
    color = 0x80;
    do {
        object = func_8003FC64(0x212);
        work = (u8 *)object + 0x20;
        if (object != 0) {
            FIELD(work, s16, 0x28) = 0x78;
            FIELD(work, s16, 0x2C) = func_80069EF8() & 1;
            FIELD(object, void *, 0x10) = D_80025088;
            func_8004491C(object, D_80025034);

            sub = FIELD(object, void *, 0xC);
            FIELD(sub, s16, 0x10) = 0x20;
            FIELD(sub, u16, 0x14) |= 0xC;

            random_pos = func_80069EF8();
            center_base = held_center - 0x20;
            FIELD(FIELD(object, void *, 8), s16, 2) =
                center_base + (random_pos & 0x3F);
            random_pos = func_80069EF8();
            call_center = (u16)held_center;
            ASM_KEEP(call_center);
            random_pos &= 0x3F;
            call_coord2 = (u16)stack.coord2;
            ASM_KEEP(call_coord2);
            coord_raw = (u16)stack.coord2;
            ASM_KEEP(coord_raw);
            data_first = FIELD(object, void *, 8);
            ASM_KEEP(data_first);
            coord_scratch = coord_raw - 0x20;
            ASM_KEEP(coord_scratch);
            coord_scratch += random_pos;
            FIELD(data_first, s16, 6) = coord_scratch;
            coord_raw = (u16)stack.coord3;
            ASM_KEEP(coord_raw);
            data_second = FIELD(object, void *, 8);
            ASM_KEEP(data_second);
            coord3_value = (s16)coord_raw;
            FIELD(data_second, s16, 0xA) = coord_raw;

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

            if (FIELD(work, u8, 0x3A) > FIELD(work, u8, 0x44)) {
                low = FIELD(work, u8, 0x44);
                high = (*(volatile u8 *)((u8 *)work + 0x3A)) + 1;
            } else {
                low = FIELD(work, u8, 0x3A);
                high = FIELD(work, u8, 0x44) + 1;
            }

            if (FIELD(work, u8, 0x3B) > FIELD(work, u8, 0x3F)) {
                low_y = FIELD(work, u8, 0x3F);
                high_y = (*(volatile u8 *)((u8 *)work + 0x3B)) + 1;
            } else {
                low_y = FIELD(work, u8, 0x3B);
                high_y = FIELD(work, u8, 0x3F) + 1;
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
            FIELD(work, u8, 0x3E) = edge;
            FIELD(work, u8, 0x3A) = edge;
            inner = scratch + factor;
            FIELD(work, u8, 0x46) = inner;
            FIELD(work, u8, 0x44) = inner;

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
            FIELD(work, u8, 0x47) = edge;
            FIELD(work, u8, 0x3F) = edge;
            inner = scratch + factor;
            FIELD(work, u8, 0x45) = inner;
            FIELD(work, u8, 0x3B) = inner;

            sub = FIELD(object, void *, 0xC);
            FIELD(sub, s16, 0x1E) = 0x1000;
            FIELD(sub, s16, 0x1C) = 0x1000;

            FIELD(work, s16, 0x4A) = (func_80069EF8() & 3) - 5;
            FIELD(work, s16, 0x4C) = (func_80069EF8() & 3) - 2;
            FIELD(work, s16, 0x4E) = (func_80069EF8() & 3) - 5;
            FIELD(work, s16, 0x50) = (func_80069EF8() & 3) + 1;
            FIELD(work, s16, 0x52) = (func_80069EF8() & 3) - 2;
            FIELD(work, s16, 0x54) = (func_80069EF8() & 3) - 5;
            FIELD(work, s16, 0x56) = (func_80069EF8() & 3) - 5;
            FIELD(work, s16, 0x58) = (func_80069EF8() & 3) - 2;
            FIELD(work, s16, 0x5A) = (func_80069EF8() & 3) + 1;
            FIELD(work, s16, 0x5C) = (func_80069EF8() & 3) + 1;
            FIELD(work, s16, 0x5E) = (func_80069EF8() & 3) - 2;
            FIELD(work, s16, 0x60) = (func_80069EF8() & 3) + 1;

            FIELD(work, u8, 0xE) = color;
            FIELD(work, u8, 0xD) = color;
            FIELD(work, u8, 0xC) = color;
            FIELD(work, u8, 0x12) = color;
            FIELD(work, u8, 0x11) = color;
            FIELD(work, u8, 0x10) = color;
            FIELD(work, u8, 0x16) = color;
            FIELD(work, u8, 0x15) = color;
            FIELD(work, u8, 0x14) = color;
            FIELD(work, u8, 0x1A) = color;
            FIELD(work, u8, 0x19) = color;
            FIELD(work, u8, 0x18) = color;

            FIELD(sub, s16, 0x16) = func_80069EF8() & 0xFFF;
            FIELD(sub, s16, 0x18) = func_80069EF8() & 0xFFF;
            FIELD(sub, s16, 0x1A) = func_80069EF8() & 0xFFF;
            FIELD(work, s32, 0x7C) = ((func_80069EF8() & 0x7FFF) - 0x4000) << 5;
            FIELD(work, s32, 0x80) = ((func_80069EF8() & 0x7FFF) - 0x4000) << 5;
            FIELD(work, s32, 0x84) =
                (((func_80069EF8() & 0x7FFF) - 0x6000) << 6) + (s32)0xFFFE0000;
            FIELD(work, s32, 0x90) = 0x10000;

            FIELD(sub, u8, 0xE) = color;
            FIELD(sub, u8, 0xD) = color;
            FIELD(sub, u8, 0xC) = color;
            func_8003DB94(sub, &D_800DE870, 0);
        }
        iteration_raw = (u16)stack.iteration;
        ASM_KEEP(iteration_raw);
        iteration_next = iteration_raw + 1;
        stack.iteration = iteration_next;
    } while ((s16)iteration_next < 4);
}
