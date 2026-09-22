#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B1B10_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x34];
    s32 unk_58;
    u8 pad_5C[0x14];
    s32 unk_70;
    s32 unk_74;
} S_800B1B10_0;   /* obj in func_800B1B10 */

typedef struct S_800B1B10_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800B1B10_1;   /* header in func_800B1B10 */

typedef struct S_800B1B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
    union { s32 n; volatile s32 v; } unk_18;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_1C;   /* accessed as both */
    u8 pad_20[0x2];
    s16 unk_22;
    s16 unk_24;
    u16 unk_26;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
} S_800B1B10_2;   /* sub in func_800B1B10 */

typedef struct S_800B1B10_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
} S_800B1B10_3;   /* meta in func_800B1B10 */

typedef struct S_800B1B10_4 {
    u8 unk_00;
    u8 unk_01;
} S_800B1B10_4;   /* owner_held in func_800B1B10 */

typedef struct S_800B1B10_5 {
    u8 unk_00;
    union { u8 n; volatile u8 v; } unk_01;   /* accessed as both */
    s8 unk_02;
    union { u8 u; s8 s; } unk_03;   /* accessed as both */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    s8 unk_0B;
    s32 unk_0C;
    volatile s32 unk_10;
    volatile s32 unk_14;
} S_800B1B10_5;   /* (void *) b_held in func_800B1B10 */

typedef struct S_800B1B10_6 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800B1B10_6;   /* ((style_held++ * 4) + sub) in func_800B1B10 */

typedef struct S_800B1B10_7 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800B1B10_7;   /* ((style_held * 4) + sub) in func_800B1B10 */


extern u8 D_80083498[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_8004DA74();
s32 func_80069E98();
s32 func_800990FC();
s8 *func_80099368();
void *func_800B12F4();
M2C_UNK func_800B1320();
M2C_UNK func_800B135C();
M2C_UNK func_800B1400();
void *func_800B1434();
extern M2C_UNK D_800B14FC;
extern M2C_UNK D_800B06F0;

/* Build the floating number/icon widget for the owner: allocate it and lay out its digit sprites. */
void func_800B1B10(void *owner, s32 value_a, s32 value_b, s32 style, s16 compact, u16 flags) {
    u16 subroutine_arg4;
    S_800B1B10_4 *owner_held = owner;
    register s32 a_held ASM_REG("$16") = value_a;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 b_held = value_b;
    s32 style_held = style;
    s16 compact_held = compact;
    u16 flags_held = flags;
    register s16 compact_s16;
    M2C_UNK offset;
    M2C_UNK obj;
    M2C_UNK obj_2;
    s32 style_byte;
    s32 geom;
    s32 call_kind;
    register s32 call_target ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *alloc_data;
    s32 copy_a;
    s32 copy_b;
    u32 byte_val;
    s32 value_4;
    s32 value_5;
    s32 tail;
    void *sub;
    s32 *slots;
    S_800B1B10_1 *header;
    void *part;
    S_800B1B10_3 *meta;

    call_kind = 0x12;
#ifdef NON_MATCHING
    alloc_data = D_80083498;
#else
#endif
    subroutine_arg4 = flags_held;
#ifndef NON_MATCHING
    alloc_data = (u8 *)&D_80083498;
#endif
    obj = (M2C_UNK) func_8003FD64(call_kind, alloc_data);
    compact_s16 = compact_held;
    if (obj != NULL) {
        meta = ((S_800B1B10_0 *)obj)->unk_0C;
        header = ((S_800B1B10_0 *)obj)->unk_08;
        sub = obj + 0x20;
        header->unk_02 = a_held;
        header->unk_06 = b_held;
        ((S_800B1B10_2 *)sub)->unk_08 = 1;
        meta->unk_1C = 0x1000;
        meta->unk_0C = 0;
        ((S_800B1B10_0 *)obj)->unk_10 = &D_800B14FC;
        func_8004491C(obj, &D_800B06F0);
        call_kind = 3;
        style_byte = (s32) (style_held << 0x10) >> 0x18;
        ((S_800B1B10_2 *)sub)->unk_24 = (s16) style_byte;
        ((S_800B1B10_2 *)sub)->unk_0A = a_held;
        ((S_800B1B10_2 *)sub)->unk_0C = b_held;
        ((S_800B1B10_0 *)obj)->unk_20 = (void *) (obj + 0x70);
        ((S_800B1B10_2 *)sub)->unk_04 = (void *) (obj + 0x58);
        if (func_8003FA44(call_kind) != 0) {
            slots = (s32 *) (obj + 0x5C);
            a_held = (s32) func_800B12F4();
            b_held = a_held;
            ASM_KEEP_NV(b_held);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ((S_800B1B10_2 *)sub)->unk_28 = a_held;
            ((S_800B1B10_0 *)obj)->unk_70 = b_held;
            part = func_8004A658(owner_held->unk_01, owner_held->unk_00);
            style_held = 2;
            b_held = (s32) func_800B1434((void *) b_held, part);
            ASM_KEEP_NV(style_held);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            func_800B13CC((void *) a_held, 0x20);
            func_800B1400((void *) a_held, style_held);
            {
                s32 color_v0;
                color_v0 = 0x808080;
                ((S_800B1B10_0 *)obj)->unk_58 = color_v0;
            }
            value_4 = func_800990FC();
            *func_80099368(owner_held, value_4) = 0;
            value_5 = func_8004DA74((void *) b_held, value_4, 0);
            {
                s32 mask_v1;
                mask_v1 = 0x7FFFFFFF;
                call_target = value_4;
                owner_held = (void *) value_5;
                ((S_800B1B10_0 *)obj)->unk_74 = (s32) owner_held & mask_v1;
            }
            obj_2 = func_80069E98(call_target) * 4;
            if ((compact_held << 0x10) != 0) {
                tail = 0x89 - obj_2;
                offset = (s16) tail;
                goto block_shared;
            }
            offset = 0x8A;
block_shared:
            func_800B1320((void *) b_held, offset, (s16) ((0 - (s8) ((S_800B1B10_5 *)((void *) b_held))->unk_03.u) - 0xE));
            offset = 8;
            if ((compact_s16 << 0x10) != 0) {
                offset = 4;
            }
            func_800B135C((void *) b_held, offset);
            func_800B13CC((void *) b_held, 0x20);
            func_800B1400((void *) b_held, 2);
            {
                s32 color_v0;
                color_v0 = 0x808080;
                *slots = color_v0;
            }
            slots++;
            func_80069E98(value_4);
            b_held = (s32) func_800B12F4();
            ((S_800B1B10_2 *)sub)->unk_2C = b_held;
            {
                s32 mask_v0;
                mask_v0 = 0x7FFFFFFF;
                ((S_800B1B10_6 *)(((style_held++ * 4) + sub)))->unk_50 = b_held & mask_v0;
            }
            func_800B1434((void *) b_held, owner_held);
            func_800B1320(owner_held, 1, 1);
            b_held = (s32) func_800B12F4();
            ((S_800B1B10_2 *)sub)->unk_30 = b_held;
            *slots = 0x80808;
            geom = 0x80000;
            ((S_800B1B10_7 *)(((style_held * 4) + sub)))->unk_50 = b_held;
            ((S_800B1B10_5 *)((void *) b_held))->unk_01.n = 0x38U;
            ((S_800B1B10_5 *)((void *) b_held))->unk_02 = -0xA;
            ((S_800B1B10_5 *)((void *) b_held))->unk_03.s = -0x10;
            ((S_800B1B10_5 *)((void *) b_held))->unk_0A = (s8) (obj_2 + 0x18);
            ((S_800B1B10_5 *)((void *) b_held))->unk_09 = 0;
            ((S_800B1B10_5 *)((void *) b_held))->unk_08 = 0;
            ((S_800B1B10_5 *)((void *) b_held))->unk_0B = 0x14;
            ((S_800B1B10_5 *)((void *) b_held))->unk_00 = 0xC0;
            ((S_800B1B10_2 *)sub)->unk_10 = 0;
            ((S_800B1B10_2 *)sub)->unk_14 = 0;
            geom |= 0x4008;
            ((S_800B1B10_2 *)sub)->unk_18.n = geom;
            ((S_800B1B10_2 *)sub)->unk_1C.n = geom;
            ((S_800B1B10_5 *)((void *) b_held))->unk_04.at00.v = (s32) ((S_800B1B10_2 *)sub)->unk_10;
            ((S_800B1B10_5 *)((void *) b_held))->unk_0C = (s32) ((S_800B1B10_2 *)sub)->unk_14;
            copy_a = ((S_800B1B10_2 *)sub)->unk_18.v;
            style_held++;
            ((S_800B1B10_5 *)((void *) b_held))->unk_10 = copy_a;
            byte_val = ((S_800B1B10_5 *)((void *) b_held))->unk_01.v;
            copy_b = ((S_800B1B10_2 *)sub)->unk_1C.v;
            byte_val |= 2;
            ((S_800B1B10_5 *)((void *) b_held))->unk_01.v = byte_val;
            ((S_800B1B10_5 *)((void *) b_held))->unk_14 = copy_b;
            b_held += 0x18;
            ((S_800B1B10_7 *)(((style_held * 4) + sub)))->unk_50 = b_held;
            ((S_800B1B10_5 *)((void *) b_held))->unk_01.n = 0x81;
            ((S_800B1B10_5 *)((void *) b_held))->unk_04.at00u.v = 0x20;
            ((S_800B1B10_5 *)((void *) b_held))->unk_04.at02.v = 0;
            ((S_800B1B10_5 *)((void *) b_held))->unk_00 = 0xC0;
            goto block_8;
        }
block_8:
        ((S_800B1B10_2 *)sub)->unk_22 = 4;
        flags_held = subroutine_arg4;
        ((S_800B1B10_2 *)sub)->unk_26 = flags_held;
    }
}
