#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct PackedVector {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct Pair16 {
    s16 x;
    s16 y;
} Pair16;

extern PackedVector D_80024004;
extern s16 D_800266BC[5];
extern s32 D_800814A0;

extern void func_80024CD4();
extern void func_80025468() __attribute__((noreturn));
extern void func_80025578() __attribute__((noreturn));

void func_80025398(void *arg0, void *arg1, void *arg2)
{
    PackedVector source;
    register PackedVector *source_ptr ASM_REG("$6");
    register PackedVector *render_source ASM_REG("$6");
    register Pair16 *derived_ptr ASM_REG("$7");
    register u32 source_page ASM_REG("$2");
    register void *out ASM_REG("$7") = arg2;
    Pair16 derived;
    register s32 current ASM_REG("$4");
    register s32 limit ASM_REG("$5");
    register s32 end ASM_REG("$2");
    register s32 state ASM_REG("$3");
    register s32 state_next ASM_REG("$2");
    s16 next;
    s32 quotient;
    register s32 quotient2 ASM_REG("$3");
    s32 i;
    s32 one;
    u16 angle;
    u16 angle_next;
    register s32 color_x ASM_REG("$2");
    register s32 color ASM_REG("$4");
    void *cursor;

    source_page = 0x80020000;
    ASM_KEEP(source_page);
    source_ptr = (PackedVector *)(source_page + 0x4004);
    ASM_KEEP(source_ptr);
    source = *source_ptr;
    ASM_KEEP(source_page);
    ASM_KEEP(out);
    current = FIELD(arg0, s16, 4);
    limit = FIELD(arg0, s16, 0xA);
    D_800266BC[0] = 1;
    ASM_KEEP(current);
    ASM_KEEP(limit);

    if (current < limit) {
        quotient = (current << 7) / limit;
        FIELD(out, u16, 0x1C) += 0x50;
        FIELD(out, u16, 0x1E) += 0x50;
        FIELD(out, s8, 0xE) = quotient;
        FIELD(out, s8, 0xD) = quotient;
        FIELD(out, s8, 0xC) = quotient;
        func_80025468(quotient, limit, source_ptr, out);
        return;
    }

    end = FIELD(arg0, s16, 2);
    ASM_KEEP(end);
    quotient2 = ((end - current) << 7) / (end - limit);
    color_x = FIELD(out, volatile u16, 0x1C);
    color = FIELD(out, volatile u16, 0x1E);
    color_x += 0x50;
    color += 0x50;
    FIELD(out, u16, 0x1C) = color_x;
    FIELD(out, u16, 0x1E) = color;
    ASM_KEEP(color_x);
    FIELD(out, volatile s8, 0xE) = quotient2;
    FIELD(out, volatile s8, 0xD) = quotient2;
    FIELD(out, volatile s8, 0xC) = quotient2;
    ASM_KEEP(quotient2);
    ASM_KEEP(color);

    angle = FIELD(arg0, u16, 0x98);
    angle_next = angle - 0x28;
    FIELD(arg0, u16, 0x98) = angle_next;
    if ((s16)angle_next < 0) {
        FIELD(arg0, u16, 0x98) = angle + 0xFD8;
    }

    i = 0x5F;
    if (FIELD(arg0, s16, 4) < 0x32) {
        color = 0x46;
        cursor = (u8 *)arg0 + 0x5F;
        do {
            FIELD(cursor, s8, 0x38) = color;
            i--;
            cursor = (u8 *)cursor - 1;
        } while (i >= 0);
    }

    state = FIELD(arg0, s16, 0);
    ASM_KEEP(state);
    FIELD(arg0, volatile s16, 0x9A) = 0x64;
    state_next = FIELD(arg0, volatile u16, 0) + 1;
    if (state != 0) {
        render_source = &source;
        if (state != 1) {
            func_80025578(color, limit, render_source, out);
            return;
        }
        goto render;
    }

    FIELD(arg0, u16, 0) = state_next;
    ASM_KEEP(state_next);
    FIELD(out, u16, 0x14) &= 0xFF7F;
    ASM_SCHED_BARRIER();
    render_source = &source;

render:
    derived_ptr = &derived;
    ASM_KEEP(derived_ptr);
    derived.x = source.x + ((s16)source.z >> 1);
    one = 1;
    derived.y = source.y + 0x3C;
    ASM_KEEP(render_source);
    func_80024CD4(arg0, FIELD(arg0, void *, 0x34), render_source, derived_ptr, one, one);

    next = FIELD(arg0, u16, 4) + 1;
    FIELD(arg0, u16, 4) = next;
    if (next == FIELD(arg0, s16, 2)) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A packed 8-byte source plus a 4-byte derived pair produces the 0x30 frame.
   Split pinned live ranges encode the retail a0/a1, v0/v1, a2/a3 roles and both tail-call CFG edges.
   Ordered volatile accesses, one zero-word schedule fence, and the mid-store `one` assignment close the residue. */
