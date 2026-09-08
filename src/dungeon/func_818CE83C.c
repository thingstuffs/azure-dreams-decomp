/* func_8002403C (dungeon, foff 0x18EE83C, 592 B) -- true base 0x8002403C by bank law
 * (bank 0x18EA800 -> 0x80020000, delta 0x7E735800, same delta as the proven region
 * leaf_18efb74_truebase_80025374 in this bank).  The retail `j 0x80024094` at word 132
 * is this function's OWN loop head (word 22): reorg steals `move a0,s1` from the target
 * thread into the j delay slot and retargets the jump one word past the label.  Written
 * as an ordinary loop it needs no fake extern callee, no census entry and no maspsx
 * name table: gcc emits `j $Lloop` itself and the word links to 0x08009025 at the true base.
 * Stock 2.7.2-cdk -O2 -G0, as_flags container default --fill-shadowed-return-delay.
 * Landing route (codegen_nudges §7.45): rowbase record for [0x18EE83C,0x18EEA8C) delta
 * 0x7E735800 -> rowbase.py promote -> rowbase_rename_reverify.py --execute (TU then
 * defines func_8002403C) -> overlay_land_function.
 */
#include "common.h"


extern u8 D_80083160[];

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);


typedef struct S_8002403C_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8002403C_0;   /* state in func_8002403C */

typedef struct S_8002403C_1 {
    volatile u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_8002403C_1;   /* scratch in func_8002403C */

typedef struct S_8002403C_2 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8002403C_2;   /* input in func_8002403C */

typedef struct S_8002403C_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_8002403C_3;   /* packet in func_8002403C */

typedef struct S_8002403C_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_8002403C_4_pre;   /* the 0x8 bytes before node in func_8002403C, addressed as node[-1] */

typedef struct S_8002403C_4 {
    u8 pad_00[0x8];
    volatile u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_8002403C_4;   /* node in func_8002403C */

typedef struct S_8002403C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_8002403C_5;   /* previous in func_8002403C */

typedef struct S_8002403C_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8002403C_6;   /* final_state in func_8002403C */

s32 func_8002403C(void *arg0, void *arg1)
{
    register u8 **global;
    register u8 *scratch;
    register u8 *state;
    register u8 *final_state;
    register u8 *cursor;
    register u8 *packet;
    register u8 *node;
    register u8 *input;
    register void *previous;
    u32 index;
    u16 first;
    register u32 rgb_mask ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 code_mask;

    node = arg0;
    input = arg1;
    global = (u8 **)D_80083160;
    rgb_mask = 0x00FFFFFF;
    state = *(u8 **)D_80083160;
    code_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;

    *(u8 * volatile *)(scratch + 0x18) = ((S_8002403C_0 *)state)->unk_8D0;
    ((S_8002403C_1 *)scratch)->unk_20.p = state + 0xB0;

    for (;;) {
    first = ((S_8002403C_2 *)input)->unk_02;
    packet = *(u8 * volatile *)(scratch + 0x18);
    ((S_8002403C_1 *)scratch)->unk_00 = first;
    ((S_8002403C_1 *)scratch)->unk_02 = ((S_8002403C_2 *)input)->unk_06;
    ((S_8002403C_1 *)scratch)->unk_04 = ((S_8002403C_2 *)input)->unk_0A;
    *(u8 * volatile *)(scratch + 0x18) = packet + 0xC;

    index = func_80065420(scratch, packet + 8, scratch + 0x90,
                         scratch + 0x94);
    ((S_8002403C_1 *)scratch)->unk_C0 = index;

    if (index < 0x1E0) {
        register s32 value;
        register s32 first ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        register s32 second ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 third;
        s32 command;

        ((S_8002403C_3 *)packet)->unk_04.at00.v = ((S_8002403C_4 *)node)->unk_08;
        value = ((S_8002403C_3 *)packet)->unk_04.at00u.v * ((S_8002403C_4 *)node)->unk_32;
        if (value < 0) {
            value += 0xFF;
        }
        ((S_8002403C_3 *)packet)->unk_04.at00u.v = value >> 8;

        value = ((S_8002403C_3 *)packet)->unk_04.at01.v * ((S_8002403C_4 *)node)->unk_32;
        if (value < 0) {
            value += 0xFF;
        }
        ((S_8002403C_3 *)packet)->unk_04.at01.v = value >> 8;

        value = ((S_8002403C_3 *)packet)->unk_04.at02.v * ((S_8002403C_4 *)node)->unk_32;
        if (value < 0) {
            value += 0xFF;
        }
        first = 0;
        second = 1;
        ((S_8002403C_3 *)packet)->unk_04.at02.v = value >> 8;
        ((S_8002403C_3 *)packet)->unk_00.at03.v = 2;
        command = 0x6A;
        ASM_SET(third);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        third = first;
        ASM_KEEP_DEP_NV(third, command);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_8002403C_3 *)packet)->unk_04.at03.v = command;

        ((S_8002403C_3 *)packet)->unk_00.at00.v =
            (((S_8002403C_3 *)packet)->unk_00.at00.v & code_mask) |
            ((*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) & rgb_mask);
        {
            register u32 *table ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u32 table_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u32 packet_bits;

            table = (u32 *)(((S_8002403C_1 *)scratch)->unk_C0 << 2);
            table = (u32 *)((u32)table +
                            (u32)((S_8002403C_1 *)scratch)->unk_20.p2);
            table_word = *table;
            packet_bits = (u32)packet & rgb_mask;
            table_word = (table_word & code_mask) | packet_bits;
            *table = table_word;
        }

        packet = *(u8 * volatile *)(scratch + 0x18);
        ((S_8002403C_1 *)scratch)->unk_18 = packet + 0xC;
        value = func_80066460(first, second, third, first);
        func_80067F20(packet, 0, 0, (u16)value, 0);

        ((S_8002403C_3 *)packet)->unk_00.at00.v =
            (((S_8002403C_3 *)packet)->unk_00.at00.v & code_mask) |
            ((*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) & rgb_mask);
        packet = (u8 *)((u32)packet & rgb_mask);
        (*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) =
            ((*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) & code_mask) |
            (u32)packet;
    }

    previous = ((S_8002403C_4_pre *)node)[-1].unk_00;
    node = (u8 *)previous + 0x20;
    if (previous == 0) {
        break;
    }
    input = ((S_8002403C_5 *)previous)->unk_08;
    }

    final_state = *global;
    cursor = ((S_8002403C_1 *)scratch)->unk_18;
    ((S_8002403C_6 *)final_state)->unk_8D0 = cursor;
    return 0;
}
