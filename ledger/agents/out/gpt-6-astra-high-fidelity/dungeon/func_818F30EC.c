#include "common.h"

typedef struct S_800248EC_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800248EC_0;   /* ctx in func_800248EC */

typedef struct S_800248EC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800248EC_1;   /* input in func_800248EC */

typedef struct S_800248EC_2 {
    u8 pad_00[0x3];
    u8 unk_03;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800248EC_2;   /* packet in func_800248EC */

typedef struct S_800248EC_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800248EC_3_pre;   /* the 0x8 bytes before cur in func_800248EC, addressed as cur[-1] */

typedef struct S_800248EC_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_800248EC_3;   /* cur in func_800248EC */

typedef struct S_800248EC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800248EC_4;   /* next in func_800248EC */

typedef struct S_800248EC_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800248EC_5;   /* final_ctx in func_800248EC */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch800248EC;

typedef struct {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet800248EC;

extern u8 D_80083160[];
extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

s32 func_800248EC(void *arg0, void *arg1)
{
    void *cur = arg0;
    void *input = arg1;
    u8 *global = D_80083160;
    register u32 low_mask ASM_REG("$18") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *ctx = *(u8 **)D_80083160;
    register u8 *initial_next ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 high_mask = 0xFF000000;
    Scratch800248EC *scratch =
        (Scratch800248EC *)0x1F800000;
    Packet800248EC *packet;
    Packet800248EC *packet2;
    u8 *final_ctx;
    s32 value;
    void *next;
    register s32 call_arg0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 call_arg1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 call_arg2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    u32 packet_code;

    ASM_KEEP(global);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(high_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    initial_next = ((S_800248EC_0 *)ctx)->unk_8D0;
    scratch->ot = (u32 *)(ctx + 0xB0);
    scratch->cursor = initial_next;
    ASM_KEEP(initial_next);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    for (;;) {
        packet = *(Packet800248EC *volatile *)&scratch->cursor;
        scratch->x = ((S_800248EC_1 *)input)->unk_02;
        scratch->y = ((S_800248EC_1 *)input)->unk_06;
        scratch->z = ((S_800248EC_1 *)input)->unk_0A;
        scratch->cursor = (u8 *)packet + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)packet + 8,
                                      &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            ((S_800248EC_2 *)packet)->unk_04.at00.v = ((S_800248EC_3 *)cur)->unk_08;

            value = (s32)packet->r * ((S_800248EC_3 *)cur)->unk_32;
            if (value < 0) {
                value += 0x7F;
            }
            packet->r = value >> 7;

            value = (s32)packet->g * ((S_800248EC_3 *)cur)->unk_32;
            if (value < 0) {
                value += 0x7F;
            }
            packet->g = value >> 7;

            value = (s32)packet->b * ((S_800248EC_3 *)cur)->unk_32;
            if (value < 0) {
                value += 0x7F;
            }
            packet->b = value >> 7;

            call_arg0 = 0;
            call_arg1 = 1;
            ((S_800248EC_2 *)packet)->unk_03 = 2;
            ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            packet_code = 0x6A;
            ASM_KEEP(packet_code);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            call_arg2 = call_arg0;
            ((S_800248EC_2 *)packet)->unk_04.at03.v = packet_code;
            packet->tag = (packet->tag & high_mask) |
                          (scratch->ot[scratch->index] & low_mask);
            {
                u32 old_tag = scratch->ot[scratch->index];
                register u32 packet_mask ASM_REG("$2") =
                    (u32)packet & low_mask;

                scratch->ot[scratch->index] =
                    (old_tag & high_mask) | packet_mask;
                ASM_KEEP(packet_mask);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            }

            packet2 = (Packet800248EC *)scratch->cursor;
            scratch->cursor = (u8 *)packet2 + 0xC;
            value = func_80066460(call_arg0, call_arg1, call_arg2, call_arg0);
            func_80067F20(packet2, 0, 0, (u16)value, 0);

            packet2->tag = (packet2->tag & high_mask) |
                           (scratch->ot[scratch->index] & low_mask);
            scratch->ot[scratch->index] =
                (scratch->ot[scratch->index] & high_mask) |
                ((u32)packet2 & low_mask);
        }

        next = ((S_800248EC_3_pre *)cur)[-1].unk_00;
        if (next != 0) {
            cur = (u8 *)next + 0x20;
            input = ((S_800248EC_4 *)next)->unk_08;
            ASM_KEEP(cur);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            continue;
        }

        break;
    }

    ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    final_ctx = *(u8 **)global;
    ((S_800248EC_5 *)final_ctx)->unk_8D0 = scratch->cursor;
    return 0;
}
