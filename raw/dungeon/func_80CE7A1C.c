#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Vec3u16 {
    u16 raw_y;
    u16 y;
    u16 z;
} Vec3u16;

extern void *func_8003FC64(s32);
extern s32 func_8003DE58(void *, void *, Vec3u16 *, s32);
extern void func_8004491C(void *, void *);

extern u8 D_800DDC40[];
extern u8 D_80170CEC[];
extern u8 D_80170D40[];
extern s16 D_80175EBC[];

void func_8017121C(void *arg0, void *arg1, s32 arg2, void *arg3)
{
    Vec3u16 offset;
    void *effect;
    void *call_effect;
    void *call_data;
    void *coords;
    register u8 *base ASM_REG("$18");
    void *source;
    void *part;
    void *tracked;
    register s16 *table_base ASM_REG("$5");
    register s32 value ASM_REG("$2");
    u32 mask;
    register u32 flags ASM_REG("$2");
    u32 index1;
    register void *owner ASM_REG("$2");
    s32 coord1;
    s16 *entry1;
    s32 table1;
    s32 tracked1;
    u32 index2;
    s32 tracked2;
    s32 coord2;
    s16 *entry2;
    s32 table2;
    s32 value2;
    s32 coord3;
    s32 raw_x;
    register s32 raw_y ASM_REG("$3");
    s32 y;
    s32 scaled_x;
    s32 scaled_y;
    s32 tail_coord;

    effect = func_8003FC64(0x212);
    if (effect == NULL) {
        return;
    }

    call_effect = effect;
    ASM_KEEP_NV(call_effect);
    call_data = D_80170CEC;
    ASM_KEEP(call_data);
    base = (u8 *)effect + 0x20;
    ASM_KEEP_NV(base);
    FIELD(base, s16, 0x18) = 2;
    FIELD(base, s16, 0x1A) = 2;
    FIELD(effect, void *, 0x10) = D_80170D40;
    func_8004491C(call_effect, call_data);

    part = FIELD(effect, void *, 0xC);
    ASM_KEEP_NV(part);
    FIELD(part, u16, 0x14) &= 0xFFF3;

    coords = FIELD(effect, void *, 8);
    FIELD(coords, u16, 2) = FIELD(arg1, u16, 2);
    FIELD(coords, u16, 6) = FIELD(arg1, u16, 6);
    FIELD(coords, u16, 0xA) = FIELD(arg1, u16, 0xA);

    source = FIELD(arg0, void *, -0x14);
    if (func_8003DE58(FIELD(source, void *, 8), source, &offset, 0) != 0) {
        FIELD(coords, u16, 2) += offset.raw_y;
        FIELD(coords, u16, 6) += offset.y;
        FIELD(coords, u16, 0xA) += offset.z;
    } else {
        FIELD(coords, u16, 0xA) -= 0x14;
    }

    part = FIELD(effect, void *, 0xC);
    ASM_KEEP_NV(part);
    FIELD(part, s16, 0x1E) = 0x1000;
    FIELD(part, s16, 0x1C) = 0x1000;
    FIELD(part, u8, 0xE) = 0xA0;
    FIELD(part, u8, 0xD) = 0xA0;
    FIELD(part, u8, 0xC) = 0xA0;
    FIELD(base, u8, 0) = 0xA0;
    FIELD(base, u8, 1) = FIELD(part, u8, 0xD);
    FIELD(base, u8, 2) = FIELD(part, u8, 0xE);

    if (FIELD(arg3, void *, 0x60) == NULL) {
        goto no_tracked;
    }
    flags = FIELD(arg3, u32, 0x14);
    ASM_KEEP_NV(flags);
    mask = 0x04000000;
    ASM_KEEP_NV(mask);
    if ((flags & mask) == 0) {
        table_base = D_80175EBC;
        ASM_KEEP_NV(table_base);
        FIELD(base, s16, 0x60) = 0;
        FIELD(base, s16, 0x5C) = 0;
        FIELD(base, s16, 0x58) = 0;

        index1 = FIELD(arg3, u16, 0x2A);
        ASM_KEEP_NV(index1);
        owner = FIELD(arg3, void *, 0x60);
        ASM_KEEP_NV(owner);
        coord1 = FIELD(coords, s16, 2);
        ASM_KEEP_NV(coord1);
        index1 = (index1 >> 7) & 0x1C;
        index1 += (u32)table_base;
        entry1 = (s16 *)index1;
        ASM_KEEP_NV(entry1);
        tracked = FIELD(owner, void *, -0x18);
        ASM_KEEP_NV(tracked);
        table1 = *entry1;
        ASM_KEEP(table1);
        tracked1 = FIELD(tracked, s16, 2);
        ASM_KEEP_NV(tracked1);
        table1 <<= 4;
        value = tracked1 - coord1;
        value -= table1;
        ASM_KEEP_NV(value);
        FIELD(base, s16, 0x5A) = value / 2;

        index2 = FIELD(arg3, u16, 0x2A);
        ASM_KEEP_NV(index2);
        tracked2 = FIELD(tracked, s16, 6);
        ASM_KEEP_NV(tracked2);
        coord2 = FIELD(coords, s16, 6);
        ASM_KEEP_NV(coord2);
        index2 = (index2 >> 7) & 0x1C;
        index2 += (u32)table_base;
        entry2 = (s16 *)index2;
        ASM_KEEP_NV(entry2);
        table2 = entry2[1];
        ASM_KEEP_NV(table2);
        value2 = tracked2 - coord2;
        table2 <<= 4;
        value2 -= table2;
        ASM_KEEP_NV(value2);
        FIELD(base, s16, 0x5E) = value2 / 2;

        coord3 = FIELD(coords, s16, 0xA);
        value = FIELD(tracked, s16, 0xA) - coord3;
        value -= D_800DDC40[FIELD(FIELD(arg3, void *, 0x60), u8, 0x13)] >> 1;
        ASM_KEEP_NV(value);
        FIELD(base, s16, 0x62) = value / 2;
        return;
    }

no_tracked:
    FIELD(base, s16, 0x60) = 0;
    FIELD(base, s16, 0x5C) = 0;
    FIELD(base, s16, 0x58) = 0;

    raw_y = FIELD(arg3, u8, 0x73);
    raw_x = FIELD(arg3, u8, 0x72);
    ASM_KEEP(raw_y);
    raw_y <<= 24;
    y = raw_y >> 24;
    raw_x <<= 24;
    raw_y = raw_x >> 24;
    if (raw_x < 0) {
        raw_y = -raw_y;
    }
    if ((s16)y < 0) {
        y = -y;
    }
    scaled_x = raw_y << 16;
    tail_coord = FIELD(coords, s16, 2);
    scaled_x >>= 10;
    tail_coord -= 0x20;

    value = scaled_x - tail_coord;
    FIELD(base, s16, 0x5A) = value / 2;
    ASM_KEEP(base);
    scaled_y = y << 16;
    tail_coord = FIELD(coords, s16, 6);
    scaled_y >>= 10;
    FIELD(base, s16, 0x62) = 0;
    tail_coord -= 0x20;
    value = scaled_y - tail_coord;
    FIELD(base, s16, 0x5E) = value / 2;
}

/* MECHANISM: The 0x38 frame and guarded register live ranges preserve the retail prologue, held bases, and table pipelines.
   Raw u8 shift/sign-extension idioms reproduce the fallback branches without widening artifacts.
   Mutating scaled_x/scaled_y with >>= 10 lets each sra fill an lh delay and preserves the second zero-store seam. */
