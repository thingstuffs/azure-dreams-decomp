#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[];

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_80024094() __attribute__((noreturn));

s32 func_818CE83C(void *arg0, void *arg1)
{
    register u8 **global ASM_REG("$21");
    register u8 *scratch ASM_REG("$17");
    register u8 *state;
    register u8 *final_state;
    register u8 *cursor;
    register u8 *packet;
    register u8 *node ASM_REG("$19");
    register u8 *input ASM_REG("$8");
    register void *previous ASM_REG("$5");
    u32 index;
    u16 first;
    register u32 rgb_mask ASM_REG("$18");
    register u32 code_mask ASM_REG("$20");

    node = arg0;
    input = arg1;
    global = (u8 **)D_80083160;
    rgb_mask = 0x00FFFFFF;
    state = *(u8 **)D_80083160;
    code_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(node);
    ASM_KEEP(input);
    ASM_KEEP(global);
    ASM_KEEP(rgb_mask);
    ASM_KEEP(code_mask);
    ASM_KEEP(scratch);

    *(u8 * volatile *)(scratch + 0x18) = FIELD(state, u8 *, 0x8D0);
    FIELD(scratch, u8 *, 0x20) = state + 0xB0;

    ASM_SCHED_BARRIER();
loop:
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
        register s32 value ASM_REG("$2");
        register s32 first ASM_REG("$4");
        register s32 second ASM_REG("$5");
        register s32 third ASM_REG("$6");
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
            ASM_KEEP_NV(table);
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
    if (previous != 0) {
        register u8 *loop_ctx ASM_REG("$4");

        loop_ctx = scratch;
        ASM_TAILSLOT_PIN(loop_ctx);
        input = FIELD(previous, u8 *, 8);
        ASM_KEEP(node);
        ASM_KEEP(input);
        func_80024094();
    }

    ASM_SET(previous);
    final_state = *global;
    cursor = FIELD(scratch, u8 *, 0x18);
    FIELD(final_state, u8 *, 0x8D0) = cursor;
    return 0;
}
