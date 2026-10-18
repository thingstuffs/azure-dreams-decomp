#include "modules/dungeon_ovl_18ee800.h"
#include "shared/gpu_packets.h"
/* func_8002403C (dungeon, foff 0x18EE83C) -- true base 0x8002403C by bank law
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
#include "shared/game_work.h"





   /* state in func_8002403C */

   /* scratch in func_8002403C */

   /* input in func_8002403C */

   /* packet in func_8002403C */

   /* the 0x8 bytes before node in func_8002403C, addressed as node[-1] */

   /* node in func_8002403C */

   /* previous in func_8002403C */

   /* final_state in func_8002403C */



/* Project linked nodes and enqueue shaded point primitives with their draw modes. */
s32 func_8002403C(void *start_node, void *start_coords)
{
    u8 **state_ptr;
    u8 *scratch;
    u8 *render_state;
    u8 *final_state;
    u8 *packet_end;
    u8 *packet;
    u8 *node;
    u8 *coords;
    void *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (u8 **)((u8 *)(&g_game_work));
    render_state = *(u8 **)((u8 *)(&g_game_work));
    scratch = (u8 *)0x1F800000;

    *(u8 * *)(scratch + 0x18) = ((GpuContext *)render_state)->packetCursor;
    ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p = render_state + 0xB0;

    for (;;) {
        coord_x = ((B32_818CE83C_S_8002403C_2 *)coords)->unk_02;
        packet = *(u8 * *)(scratch + 0x18);
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_00 = coord_x;
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_02 = ((B32_818CE83C_S_8002403C_2 *)coords)->unk_06;
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_04 = ((B32_818CE83C_S_8002403C_2 *)coords)->unk_0A;
        *(u8 * *)(scratch + 0x18) = packet + 0xC;

        depth_index = func_80065420(scratch, packet + 8, scratch + 0x90,
                             scratch + 0x94);
        ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            s32 texture_depth;
            s32 blend_mode;
            u32 page_x;
            s32 opcode;
            u8 *mode_packet;

            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at00.v = ((B32_818CE83C_S_8002403C_4 *)node)->unk_08;
            color_or_tpage = ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at00u.v * ((B32_818CE83C_S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at00u.v = color_or_tpage >> 8;

            color_or_tpage = ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at01.v * ((B32_818CE83C_S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at01.v = color_or_tpage >> 8;

            color_or_tpage = ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at02.v * ((B32_818CE83C_S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
                texture_depth = 0;
            } else {
                texture_depth = 0;
            }
            blend_mode = 1;
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at02.v = color_or_tpage >> 8;
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_00.at03.v = 2;
            opcode = 0x6A;
            page_x = texture_depth;
            ((B32_818CE83C_S_8002403C_3 *)packet)->unk_04.at03.v = opcode;

            ((B32_818CE83C_PacketTag *)packet)->addr =
                ((B32_818CE83C_PacketTag *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4)))->addr;
            {
                u32 *ot_entry;
                u32 ot_tag;
                u32 packet_addr;

                ot_entry = (u32 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 << 2);
                ot_entry = (u32 *)((u32)ot_entry +
                                (u32)((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2);
                ot_tag = *ot_entry;
                *ot_entry = ((u32)((ot_tag & 0xFF000000) | ((u32)((u32)packet & 0x00FFFFFF))));
            }

            mode_packet = *(u8 * *)(scratch + 0x18);
            ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_18 = mode_packet + 0xC;
            color_or_tpage = func_80066460(texture_depth, blend_mode, page_x, texture_depth);
            func_80067F20(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((B32_818CE83C_PacketTag *)mode_packet)->addr =
                ((B32_818CE83C_PacketTag *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4)))->addr;
            mode_packet = (u8 *)((u32)mode_packet & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4))) =
                ((*(u32 *)((u8 *)(((B32_818CE83C_S_8002403C_1 *)scratch)->unk_20.p2) + (((B32_818CE83C_S_8002403C_1 *)scratch)->unk_C0 * 4))) & 0xFF000000) |
                (u32)mode_packet;
        }

        prev_entry = ((B32_818CE83C_S_8002403C_4_pre *)node)[-1].unk_00;
        node = (u8 *)prev_entry + 0x20;
        if (prev_entry == 0) {
            break;
        }
        coords = ((B32_818CE83C_S_8002403C_5 *)prev_entry)->unk_08;
    }

    final_state = *state_ptr;
    packet_end = ((B32_818CE83C_S_8002403C_1 *)scratch)->unk_18;
    ((GpuContext *)final_state)->packetCursor = packet_end;
    return 0;
}
