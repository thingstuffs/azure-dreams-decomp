#include "common.h"

extern void *D_80083160[3];
extern u8 D_801C9E40[16];

extern void func_8002616C();
extern s32 func_8006658C(void *, s32);
extern void func_80067E2C();

/* Renders data with the active buffer offset between ordering-table commands. */
void func_81960864(void *draw_data, s32 draw_mode)
{
    s32 start_packet;
    s32 end_packet;
    s32 buffer_shift_copy;
    s32 buffer_shift;
    register void *ordering_table ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    s32 mode_offset;
    s32 base_offset;
    void **draw_contexts;
    void *draw_context;
    void *end_context;

    draw_context = D_80083160[0];
    draw_contexts = D_80083160;
    start_packet = *(s32 *)((u8 *)draw_context + 0x8D0);
    ordering_table = (u8 *)draw_context + 0x8B0;
    *(s32 *)((u8 *)draw_context + 0x8D0) = start_packet + 0xC;
    buffer_shift = draw_context != (void *)D_801C9E40;
    func_80067E2C(start_packet, D_80083160[0], draw_context);
    {
        register void *packet_table ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 packet_addr;

        packet_table = ordering_table;
        packet_addr = start_packet;
        ASM_KEEP(packet_addr);   /* MATCH pin: retail immediate-load split depends on it */
        func_8006658C(packet_table, packet_addr);
    }
    buffer_shift_copy = buffer_shift;
    ASM_KEEP(buffer_shift_copy);   /* MATCH pin: load-bearing for the whole function shape */

    if (draw_mode != 0) {
        s32 needs_shift;

        needs_shift = buffer_shift;
        ASM_KEEP(needs_shift);   /* MATCH pin: load-bearing for the whole function shape */
        mode_offset = 0;
        if (needs_shift != 0) {
            mode_offset = -0xE0;
        }
        func_8002616C(mode_offset, draw_data, draw_mode, ordering_table);
    }

    {
        s32 needs_shift;

        needs_shift = buffer_shift_copy;
        ASM_KEEP(needs_shift);   /* MATCH pin: load-bearing for the whole function shape */
        base_offset = 0;
        if (needs_shift != 0) {
            base_offset = -0xE0;
        }
    }
    func_8002616C(base_offset, draw_data, 0, ordering_table);

    end_context = *draw_contexts;
    end_packet = *(s32 *)((u8 *)end_context + 0x8D0);
    *(s32 *)((u8 *)end_context + 0x8D0) = end_packet + 0xC;
    func_80067E2C(end_packet, draw_data);
    func_8006658C(ordering_table, end_packet);
}

/* MECHANISM: The 0x30 frame holds s0-s5; D_80083160 stays in s5 and the long-lived OT base in s1.
   Fixed a0/a1 ABI locals move both args before func_8006658C, freeing its delay slot for the disjoint s0=s2 copy.
   Leaving buffer_shift naturally allocated preserves retail's xor-in-v0 followed by sltu-into-s2 sequence. */
