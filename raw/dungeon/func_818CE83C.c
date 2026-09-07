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

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[];

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

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
    register u32 rgb_mask ASM_REG("$18");
    register u32 code_mask;

    node = arg0;
    input = arg1;
    global = (u8 **)D_80083160;
    rgb_mask = 0x00FFFFFF;
    state = *(u8 **)D_80083160;
    code_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(global);
    ASM_KEEP(code_mask);

    *(u8 * volatile *)(scratch + 0x18) = FIELD(state, u8 *, 0x8D0);
    FIELD(scratch, u8 *, 0x20) = state + 0xB0;

    for (;;) {
    first = FIELD(input, volatile u16, 2);
    packet = *(u8 * volatile *)(scratch + 0x18);
    FIELD(scratch, volatile u16, 0) = first;
    FIELD(scratch, u16, 2) = FIELD(input, u16, 6);
    FIELD(scratch, u16, 4) = FIELD(input, u16, 0xA);
    *(u8 * volatile *)(scratch + 0x18) = packet + 0xC;

    index = func_80065420(scratch, packet + 8, scratch + 0x90,
                         scratch + 0x94);
    FIELD(scratch, u32, 0xC0) = index;

    if (index < 0x1E0) {
        register s32 value;
        register s32 first ASM_REG("$4");
        register s32 second ASM_REG("$5");
        register s32 third;
        s32 command;

        FIELD(packet, u32, 4) = FIELD(node, volatile u32, 8);
        value = FIELD(packet, u8, 4) * FIELD(node, s16, 0x32);
        if (value < 0) {
            value += 0xFF;
        }
        FIELD(packet, u8, 4) = value >> 8;

        value = FIELD(packet, u8, 5) * FIELD(node, s16, 0x32);
        if (value < 0) {
            value += 0xFF;
        }
        FIELD(packet, u8, 5) = value >> 8;

        value = FIELD(packet, u8, 6) * FIELD(node, s16, 0x32);
        if (value < 0) {
            value += 0xFF;
        }
        first = 0;
        second = 1;
        FIELD(packet, u8, 6) = value >> 8;
        FIELD(packet, u8, 3) = 2;
        command = 0x6A;
        ASM_SET(third);
        third = first;
        ASM_KEEP_DEP_NV(third, command);
        FIELD(packet, u8, 7) = command;

        FIELD(packet, u32, 0) =
            (FIELD(packet, u32, 0) & code_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x20), u32,
                   FIELD(scratch, u32, 0xC0) * 4) & rgb_mask);
        {
            register u32 *table ASM_REG("$7");
            register u32 table_word ASM_REG("$3");
            u32 packet_bits;

            table = (u32 *)(FIELD(scratch, u32, 0xC0) << 2);
            table = (u32 *)((u32)table +
                            (u32)FIELD(scratch, u32 *, 0x20));
            table_word = *table;
            packet_bits = (u32)packet & rgb_mask;
            table_word = (table_word & code_mask) | packet_bits;
            *table = table_word;
        }

        packet = *(u8 * volatile *)(scratch + 0x18);
        FIELD(scratch, u8 *, 0x18) = packet + 0xC;
        value = func_80066460(first, second, third, first);
        func_80067F20(packet, 0, 0, (u16)value, 0);

        FIELD(packet, u32, 0) =
            (FIELD(packet, u32, 0) & code_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x20), u32,
                   FIELD(scratch, u32, 0xC0) * 4) & rgb_mask);
        packet = (u8 *)((u32)packet & rgb_mask);
        FIELD(FIELD(scratch, u32 *, 0x20), u32,
              FIELD(scratch, u32, 0xC0) * 4) =
            (FIELD(FIELD(scratch, u32 *, 0x20), u32,
                   FIELD(scratch, u32, 0xC0) * 4) & code_mask) |
            (u32)packet;
    }

    previous = FIELD(node, void *, -8);
    node = (u8 *)previous + 0x20;
    if (previous == 0) {
        break;
    }
    input = FIELD(previous, u8 *, 8);
    }

    final_state = *global;
    cursor = FIELD(scratch, u8 *, 0x18);
    FIELD(final_state, u8 *, 0x8D0) = cursor;
    return 0;
}
