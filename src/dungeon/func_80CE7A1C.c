#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8017121C_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x3C];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
} S_8017121C_0;   /* base in func_8017121C */

typedef struct S_8017121C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017121C_1;   /* effect in func_8017121C */

typedef struct S_8017121C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8017121C_2;   /* part in func_8017121C */

typedef struct S_8017121C_3 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_8017121C_3;   /* coords in func_8017121C */

typedef struct S_8017121C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017121C_4;   /* arg1 in func_8017121C */

typedef struct S_8017121C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017121C_5_pre;   /* the 0x14 bytes before arg0 in func_8017121C, addressed as arg0[-1] */

typedef struct S_8017121C_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8017121C_6;   /* source in func_8017121C */

typedef struct S_8017121C_7 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
} S_8017121C_7;   /* arg3 in func_8017121C */

typedef struct S_8017121C_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8017121C_8_pre;   /* the 0x18 bytes before owner in func_8017121C, addressed as owner[-1] */

typedef struct S_8017121C_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8017121C_9;   /* tracked in func_8017121C */

typedef struct S_8017121C_10 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_8017121C_10;   /* ((S_8017121C_7 *)arg3)->unk_60 in func_8017121C */



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

void func_8017121C(void *arg0, S_8017121C_4 *arg1, s32 arg2, S_8017121C_7 *arg3)
{
    Vec3u16 offset;
    void *effect;
    void *call_effect;
    void *call_data;
    S_8017121C_3 *coords;
    register u8 *base ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    S_8017121C_6 *source;
    S_8017121C_2 *part;
    S_8017121C_9 *tracked;
    register s16 *table_base ASM_REG("$5");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u32 mask;
    u32 flags;
    u32 index1;
    register void *owner ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
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
    s32 raw_y;
    s32 y;
    s32 scaled_x;
    s32 scaled_y;
    s32 tail_coord;

    effect = func_8003FC64(0x212);
    if (effect == NULL) {
        return;
    }

    call_effect = effect;
    ASM_KEEP_NV(call_effect);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_data = D_80170CEC;
    ASM_KEEP(call_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
    base = (u8 *)effect + 0x20;
    ((S_8017121C_0 *)base)->unk_18 = 2;
    ((S_8017121C_0 *)base)->unk_1A = 2;
    ((S_8017121C_1 *)effect)->unk_10 = D_80170D40;
    func_8004491C(call_effect, call_data);

    part = ((S_8017121C_1 *)effect)->unk_0C;
    part->unk_14 &= 0xFFF3;

    coords = ((S_8017121C_1 *)effect)->unk_08;
    coords->unk_02.s = arg1->unk_02;
    coords->unk_06.s = arg1->unk_06;
    coords->unk_0A.s = arg1->unk_0A;

    source = ((S_8017121C_5_pre *)arg0)[-1].unk_00;
    if (func_8003DE58(source->unk_08, source, &offset, 0) != 0) {
        coords->unk_02.s += offset.raw_y;
        coords->unk_06.s += offset.y;
        coords->unk_0A.s += offset.z;
    } else {
        coords->unk_0A.s -= 0x14;
    }

    part = ((S_8017121C_1 *)effect)->unk_0C;
    part->unk_1E = 0x1000;
    part->unk_1C = 0x1000;
    part->unk_0E = 0xA0;
    part->unk_0D = 0xA0;
    part->unk_0C = 0xA0;
    ((S_8017121C_0 *)base)->unk_00 = 0xA0;
    ((S_8017121C_0 *)base)->unk_01 = part->unk_0D;
    ((S_8017121C_0 *)base)->unk_02 = part->unk_0E;

    if (arg3->unk_60 == NULL) {
        goto no_tracked;
    }
    flags = arg3->unk_14;
    mask = 0x04000000;
    if ((flags & mask) == 0) {
        table_base = D_80175EBC;
        ((S_8017121C_0 *)base)->unk_60 = 0;
        ((S_8017121C_0 *)base)->unk_5C = 0;
        ((S_8017121C_0 *)base)->unk_58 = 0;

        index1 = arg3->unk_2A;
        ASM_KEEP_NV(index1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        owner = arg3->unk_60;
        ASM_KEEP_NV(owner);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        coord1 = coords->unk_02.u;
        ASM_KEEP_NV(coord1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        index1 = (index1 >> 7) & 0x1C;
        index1 += (u32)table_base;
        entry1 = (s16 *)index1;
        tracked = ((S_8017121C_8_pre *)owner)[-1].unk_00;
           /* MATCH pin: retail basic-block layout depends on it */
        table1 = *entry1;
        tracked1 = tracked->unk_02;
        table1 <<= 4;
        value = tracked1 - coord1;
        value -= table1;
        ((S_8017121C_0 *)base)->unk_5A = value / 2;

        index2 = arg3->unk_2A;
        ASM_KEEP_NV(index2);   /* MATCH pin: load-bearing for the whole function shape */
        tracked2 = tracked->unk_06;
        ASM_KEEP_NV(tracked2);   /* MATCH pin: retail basic-block layout depends on it */
        coord2 = coords->unk_06.u;
        ASM_KEEP_NV(coord2);   /* MATCH pin: load-bearing for the whole function shape */
        index2 = (index2 >> 7) & 0x1C;
        index2 += (u32)table_base;
        entry2 = (s16 *)index2;
        table2 = entry2[1];
        ASM_KEEP_NV(table2);   /* MATCH pin: load-bearing for the whole function shape */
        value2 = tracked2 - coord2;
        table2 <<= 4;
        value2 -= table2;
        ((S_8017121C_0 *)base)->unk_5E = value2 / 2;

        coord3 = coords->unk_0A.u;
        value = tracked->unk_0A - coord3;
        value -= D_800DDC40[((S_8017121C_10 *)(arg3->unk_60))->unk_13] >> 1;
        ((S_8017121C_0 *)base)->unk_62 = value / 2;
        return;
    }

no_tracked:
    ((S_8017121C_0 *)base)->unk_60 = 0;
    ((S_8017121C_0 *)base)->unk_5C = 0;
    ((S_8017121C_0 *)base)->unk_58 = 0;

    raw_y = arg3->unk_73;
    raw_x = arg3->unk_72;
    ASM_KEEP(raw_y);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
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
    tail_coord = coords->unk_02.u;
    scaled_x >>= 10;
    tail_coord -= 0x20;

    value = scaled_x - tail_coord;
    ((S_8017121C_0 *)base)->unk_5A = value / 2;
    ASM_KEEP(base);   /* MATCH pin: keeps a statement from moving across a call/branch */
    scaled_y = y << 16;
    tail_coord = coords->unk_06.u;
    scaled_y >>= 10;
    ((S_8017121C_0 *)base)->unk_62 = 0;
    tail_coord -= 0x20;
    value = scaled_y - tail_coord;
    ((S_8017121C_0 *)base)->unk_5E = value / 2;
}

/* MECHANISM: The 0x38 frame and guarded register live ranges preserve the retail prologue, held bases, and table pipelines.
   Raw u8 shift/sign-extension idioms reproduce the fallback branches without widening artifacts.
   Mutating scaled_x/scaled_y with >>= 10 lets each sra fill an lh delay and preserves the second zero-store seam. */
