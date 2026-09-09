#include "common.h"

typedef struct S_80025398_0 {
    union { s16 s; volatile u16 u; u16 p; } unk_00;   /* accessed as both */
    s16 unk_02;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x4];
    s16 unk_0A;
    u8 pad_0C[0x28];
    void * unk_34;
    u8 pad_38[0x60];
    u16 unk_98;
    volatile s16 unk_9A;
} S_80025398_0;   /* arg0 in func_80025398 */

typedef struct S_80025398_1 {
    u8 pad_00[0xC];
    union { s8 s; volatile s8 u; } unk_0C;   /* accessed as both */
    union { s8 s; volatile s8 u; } unk_0D;   /* accessed as both */
    union { s8 s; volatile s8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 s; volatile u16 u; } unk_1C;   /* accessed as both */
    union { u16 s; volatile u16 u; } unk_1E;   /* accessed as both */
} S_80025398_1;   /* out in func_80025398 */

typedef struct S_80025398_2 {
    u8 pad_00[0x38];
    s8 unk_38;
} S_80025398_2;   /* cursor in func_80025398 */



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

void func_80025398(void *arg0, void *arg1, void *arg2)
{
    PackedVector source;
    register PackedVector *source_ptr ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    PackedVector *render_source;
    Pair16 *derived_ptr;
    u32 source_page;
    register void *out ASM_REG("$7") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Pair16 derived;
    s32 current;
    s32 limit;
    s32 end;
    s32 state;
    s32 state_next;
    s16 next;
    s32 quotient;
    s32 quotient2;
    s32 i;
    s32 one;
    u16 angle;
    u16 angle_next;
    s32 color_x;
    s32 color;
    void *cursor;

    source_page = 0x80020000;
    ASM_KEEP(source_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    source_ptr = (PackedVector *)(source_page + 0x4004);
    ASM_KEEP(source_ptr);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    source = *source_ptr;
    ASM_KEEP(source_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    current = ((S_80025398_0 *)arg0)->unk_04.s;
    limit = ((S_80025398_0 *)arg0)->unk_0A;
    D_800266BC[0] = 1;

    if (current < limit) {
        quotient = (current << 7) / limit;
        ((S_80025398_1 *)out)->unk_1C.s += 0x50;
        ((S_80025398_1 *)out)->unk_1E.s += 0x50;
        ((S_80025398_1 *)out)->unk_0E.s = quotient;
        ((S_80025398_1 *)out)->unk_0D.s = quotient;
        ((S_80025398_1 *)out)->unk_0C.s = quotient;
    } else {
        end = ((S_80025398_0 *)arg0)->unk_02;
        quotient2 = ((end - current) << 7) / (end - limit);
        color_x = ((S_80025398_1 *)out)->unk_1C.u;
        color = ((S_80025398_1 *)out)->unk_1E.u;
        color_x += 0x50;
        color += 0x50;
        ((S_80025398_1 *)out)->unk_1C.s = color_x;
        ((S_80025398_1 *)out)->unk_1E.s = color;
        ASM_KEEP(color_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80025398_1 *)out)->unk_0E.u = quotient2;
        ((S_80025398_1 *)out)->unk_0D.u = quotient2;
        ((S_80025398_1 *)out)->unk_0C.u = quotient2;
    }

    angle = ((S_80025398_0 *)arg0)->unk_98;
    angle_next = angle - 0x28;
    ((S_80025398_0 *)arg0)->unk_98 = angle_next;
    if ((s16)angle_next < 0) {
        ((S_80025398_0 *)arg0)->unk_98 = angle + 0xFD8;
    }

    i = 0x5F;
    if (((S_80025398_0 *)arg0)->unk_04.s < 0x32) {
        color = 0x46;
        cursor = (u8 *)arg0 + 0x5F;
        do {
            ((S_80025398_2 *)cursor)->unk_38 = color;
            i--;
            cursor = (u8 *)cursor - 1;
        } while (i >= 0);
    }

    state = ((S_80025398_0 *)arg0)->unk_00.s;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80025398_0 *)arg0)->unk_9A = 0x64;
    state_next = ((S_80025398_0 *)arg0)->unk_00.u + 1;
    if (state != 0) {
        render_source = &source;
        if (state != 1) {
            ASM_SCHED_BARRIER();   /* MATCH: Keep the state guard jumping to the shared epilogue. */
            return;
        }
        goto render;
    }

    ((S_80025398_0 *)arg0)->unk_00.p = state_next;
    ((S_80025398_1 *)out)->unk_14 &= 0xFF7F;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    render_source = &source;

render:
    derived_ptr = &derived;
    derived.x = source.x + ((s16)source.z >> 1);
    one = 1;
    derived.y = source.y + 0x3C;
    ASM_KEEP(render_source);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    func_80024CD4(arg0, ((S_80025398_0 *)arg0)->unk_34, render_source, derived_ptr, one, one);

    next = ((S_80025398_0 *)arg0)->unk_04.u + 1;
    ((S_80025398_0 *)arg0)->unk_04.u = next;
    if (next == ((S_80025398_0 *)arg0)->unk_02) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A packed 8-byte source plus a 4-byte derived pair produces the 0x30 frame.
   Split pinned live ranges encode the retail a0/a1, v0/v1, a2/a3 roles and both tail-call CFG edges.
   Ordered volatile accesses, one zero-word schedule fence, and the mid-store `one` assignment close the residue. */
