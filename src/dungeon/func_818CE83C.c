#include "common.h"

typedef struct S_818CE83C_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_818CE83C_0;   /* state in func_818CE83C */

typedef struct S_818CE83C_1 {
    volatile u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_818CE83C_1;   /* scratch in func_818CE83C */

typedef struct S_818CE83C_2 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818CE83C_2;   /* input in func_818CE83C */

typedef struct S_818CE83C_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_818CE83C_3;   /* packet in func_818CE83C */

typedef struct S_818CE83C_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_818CE83C_4_pre;   /* the 0x8 bytes before node in func_818CE83C, addressed as node[-1] */

typedef struct S_818CE83C_4 {
    u8 pad_00[0x8];
    volatile u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_818CE83C_4;   /* node in func_818CE83C */

typedef struct S_818CE83C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_818CE83C_5;   /* previous in func_818CE83C */

typedef struct S_818CE83C_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_818CE83C_6;   /* final_state in func_818CE83C */



extern u8 D_80083160[];

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_80024094() __attribute__((noreturn));

s32 func_818CE83C(void *arg0, void *arg1)
{
    u8 **global;
    u8 *scratch;
    register u8 *state;
    register u8 *final_state;
    register u8 *cursor;
    register u8 *packet;
    u8 *node;
    u8 *input;
    void *previous;
    u32 index;
    u16 first;
    register u32 rgb_mask ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 code_mask;

    node = arg0;
    input = arg1;
    global = (u8 **)D_80083160;
    rgb_mask = 0x00FFFFFF;
    state = *(u8 **)D_80083160;
    code_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(global);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(code_mask);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(scratch);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    *(u8 * volatile *)(scratch + 0x18) = ((S_818CE83C_0 *)state)->unk_8D0;
    ((S_818CE83C_1 *)scratch)->unk_20.p = state + 0xB0;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
loop:
    first = ((S_818CE83C_2 *)input)->unk_02;
    packet = *(u8 * volatile *)(scratch + 0x18);
    ((S_818CE83C_1 *)scratch)->unk_00 = first;
    ((S_818CE83C_1 *)scratch)->unk_02 = ((S_818CE83C_2 *)input)->unk_06;
    ((S_818CE83C_1 *)scratch)->unk_04 = ((S_818CE83C_2 *)input)->unk_0A;
    *(u8 * volatile *)(scratch + 0x18) = packet + 0xC;

    index = func_80065420(scratch, packet + 8, scratch + 0x90,
                         scratch + 0x94);
    ((S_818CE83C_1 *)scratch)->unk_C0 = index;

    if (index < 0x1E0) {
        s32 value;
        register s32 first ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
        register s32 second ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 third;
        s32 command;

        ((S_818CE83C_3 *)packet)->unk_04.at00.v = ((S_818CE83C_4 *)node)->unk_08;
        value = ((S_818CE83C_3 *)packet)->unk_04.at00u.v * ((S_818CE83C_4 *)node)->unk_32;
        if (value < 0) {
            value += 0xFF;
        }
        ((S_818CE83C_3 *)packet)->unk_04.at00u.v = value >> 8;

        value = ((S_818CE83C_3 *)packet)->unk_04.at01.v * ((S_818CE83C_4 *)node)->unk_32;
        if (value < 0) {
            value += 0xFF;
        }
        ((S_818CE83C_3 *)packet)->unk_04.at01.v = value >> 8;

        value = ((S_818CE83C_3 *)packet)->unk_04.at02.v * ((S_818CE83C_4 *)node)->unk_32;
        if (value < 0) {
            value += 0xFF;
        }
        first = 0;
        second = 1;
        ((S_818CE83C_3 *)packet)->unk_04.at02.v = value >> 8;
        ((S_818CE83C_3 *)packet)->unk_00.at03.v = 2;
        command = 0x6A;
        ASM_SET(third);   /* MATCH pin: retail schedule: same instructions, different order without it */
        third = first;
        ((S_818CE83C_3 *)packet)->unk_04.at03.v = command;

        ((S_818CE83C_3 *)packet)->unk_00.at00.v =
            (((S_818CE83C_3 *)packet)->unk_00.at00.v & code_mask) |
            ((*(u32 *)((u8 *)(((S_818CE83C_1 *)scratch)->unk_20.p2) + ((S_818CE83C_1 *)scratch)->unk_C0 * 4)) & rgb_mask);
        {
            register u32 *table ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
            register u32 table_word ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            u32 packet_bits;

            table = (u32 *)(((S_818CE83C_1 *)scratch)->unk_C0 << 2);
            table = (u32 *)((u32)table +
                            (u32)((S_818CE83C_1 *)scratch)->unk_20.p2);
            table_word = *table;
            packet_bits = (u32)packet & rgb_mask;
            table_word = (table_word & code_mask) | packet_bits;
            *table = table_word;
        }

        packet = *(u8 * volatile *)(scratch + 0x18);
        ((S_818CE83C_1 *)scratch)->unk_18 = packet + 0xC;
        value = func_80066460(first, second, third, first);
        func_80067F20(packet, 0, 0, (u16)value, 0);

        ((S_818CE83C_3 *)packet)->unk_00.at00.v =
            (((S_818CE83C_3 *)packet)->unk_00.at00.v & code_mask) |
            ((*(u32 *)((u8 *)(((S_818CE83C_1 *)scratch)->unk_20.p2) + ((S_818CE83C_1 *)scratch)->unk_C0 * 4)) & rgb_mask);
        packet = (u8 *)((u32)packet & rgb_mask);
        (*(u32 *)((u8 *)(((S_818CE83C_1 *)scratch)->unk_20.p2) + ((S_818CE83C_1 *)scratch)->unk_C0 * 4)) =
            ((*(u32 *)((u8 *)(((S_818CE83C_1 *)scratch)->unk_20.p2) + ((S_818CE83C_1 *)scratch)->unk_C0 * 4)) & code_mask) |
            (u32)packet;
    }

    previous = ((S_818CE83C_4_pre *)node)[-1].unk_00;
    node = (u8 *)previous + 0x20;
    if (previous != 0) {
        register u8 *loop_ctx ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

        loop_ctx = scratch;
        ASM_TAILSLOT_PIN(loop_ctx);   /* MATCH pin: retail delay-slot contents depend on it */
        input = ((S_818CE83C_5 *)previous)->unk_08;
        ASM_KEEP(node);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(input);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80024094();
    }

    final_state = *global;
    cursor = ((S_818CE83C_1 *)scratch)->unk_18;
    ((S_818CE83C_6 *)final_state)->unk_8D0 = cursor;
    return 0;
}
