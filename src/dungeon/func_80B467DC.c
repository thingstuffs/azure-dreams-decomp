#include "modules/dungeon_resource12_slot0.h"

s32 build_linked_curved_wireframe_grid(u8 *node, s32 next_node, s32 callback_arg2)
{
    R12_80173FDC_Frame frame;
    u8 *effect;
    u8 *vertex_depths;
    u8 *transform_work;
    u8 *depth_base;
    u8 *xy_base;
    u8 *xy_row;
    u8 *ring_depth_row;
    u8 *vertical_xy_row;
    u8 *screen_xy;
    R12_80173FDC_GridPoint *point_base;
    u8 *vertical_depth_row;
    u8 *ring_xy;
    R12_80173FDC_LineG2 *line;
    u8 *tpage;
    u8 *display;
    s32 row;
    s32 col;
    s32 ot_index;
    s32 sin_angle;
    s32 cos_angle;
    s32 addr_mask;
    u8 **display_root = (u8 **)((u8 *)(&g_game_work));

    screen_xy = (u8 *)0x1F800000;
    vertex_depths = (u8 *)0x1F800100;
    transform_work = (u8 *)0x1F800180;
    addr_mask = 0x00FFFFFF;

    for (;;) {
        (frame.desc).points0 = &(frame.points)[0][0];
        (frame.desc).points1 = &(frame.points)[0][0];
        (frame.desc).zero = 0;
        (frame.desc).angle = ((R12_80173FDC_S_80173FDC_0 *)node)->unk_10 - 0x400;
        effect = node;
        if (*(s32 *)screen_xy && next_node) {
            /* retail evidence (decision 45, docs/evidence/r97_decisions.md): both operands of this test are loaded in retail's
               compilation and the arm compiled away. next_node: the tail's successor load (lw $5,8($5)) survives as this test's
               operand (lane r118_fable_f4). The scratchpad word: jump2 deleted it with the branch; its fingerprint is the empty
               load-delay slot after the (frame.desc).angle field load (sched2 cannot issue the effect store there while this load waits on
               the angle store), and the branch's label is why node is reloaded for ((s16)func_80065F90(lane r118_opus_o9; JP build:
               this placement matches JP at stock 2.7.2)). The arm reconstructs a conditional update of a local nothing reads; the
               bytes fix the test's shape (a scratchpad word, then next_node), not its meaning. The second parameter is the
               loop-carried successor field the tail reloads. */
            row = 0;
        }
        (frame.desc).value = ((s16)func_80065F90(((R12_80173FDC_S_80173FDC_0 *)node)->unk_12, 0x40));
        row = 0;
grid_row:
        col = 7;
grid_loop:
        {
            R12_80173FDC_GridPoint *point;
            s32 angle;
            s32 point_offset;

            next_node = row * ((8 - ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_0E) << 4);
            point_base = &(frame.points)[0][0];
            point_offset = col << 3;
            point_offset += row << 6;
            point = (R12_80173FDC_GridPoint *)((u8 *)point_base + point_offset);

            if (next_node < 0) {
                next_node += 7;
            }
            point->y = next_node >> 3;
            angle = col << 9;
            sin_angle = func_800644B8(angle);
            point->x = (sin_angle * func_800644B8(
                ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
            cos_angle = func_80064584(angle);
            point->z = (cos_angle * func_800644B8(
                ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
        }
        col--;
        if (col >= 0) {
            goto grid_loop;
        }
        row++;
        if (row < 8) {
            goto grid_row;
        }

        (frame.desc).count = 0x40;
        (frame.desc).header = *(R12_80173FDC_Header8 *)effect;
        (frame.desc).one = 1;
        transform_rotated_vertices(&(frame.desc));

        {
            u8 *vertex_depth;
            u8 *xy;

            func_80065770((frame.points), screen_xy, vertex_depths, transform_work, transform_work, (frame.desc).count);
            row = 0x38;
            vertical_xy_row = screen_xy + 0xE0;
            vertical_depth_row = vertex_depths + 0x70;
            while (row > 0) {
                col = 7;
                xy = vertical_xy_row + 0x1C;
                vertex_depth = vertical_depth_row + 0x0E;
                while (col >= 0) {
                    ot_index = ((s16)((R12_80173FDC_S_80173FDC_2 *)vertex_depth)->unk_00 +
                        (s16)((R12_80173FDC_S_80173FDC_2_pre *)vertex_depth)[-1].unk_00) >> 3;
                    if ((u32)ot_index < 0x1E0) {
                        display = *(u8 * *)display_root;
                        line = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = (u8 *)line + 0x14;

                        display = *(u8 * *)display_root;
                        tpage = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = tpage + 0x0C;

                        func_80067F20(tpage, 0, 0,(u16)(((u16)func_80066460(0, 1, 0, 0))), 0);

                        line->color0 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        line->color1 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        func_800667D0(line);
                        func_80066640(line, 1);

                        line->xy0 = ((R12_80173FDC_S_80173FDC_4 *)xy)->unk_00;
                        line->xy1 = ((R12_80173FDC_S_80173FDC_4_pre *)xy)[-1].unk_00;

                        line->tag = (line->tag & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)line & addr_mask);

                        ((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 = (((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)tpage & addr_mask);
                    }
                    xy -= 4;
                    vertex_depth -= 2;
                    col--;
                }
                vertical_depth_row -= 0x10;
                vertical_xy_row -= 0x20;
                row -= 8;
            }
        }

        {
            u8 *ring_depth;

            row = 0x30;
            xy_row = screen_xy + 0xC0;
            ring_depth_row = vertex_depths + 0x60;
            while (row > 0) {
                depth_base = ring_depth_row;
                ring_xy = xy_row + 0x1C;
                xy_base = xy_row;
                col = 7;
                ring_depth = ring_depth_row + 0x0E;
                while (col >= 0) {
                    s32 next_col = (col + 1) & 7;
                    ot_index = ((s16)((R12_80173FDC_S_80173FDC_6 *)ring_depth)->unk_00 +
                        (*(s16 *)((u8 *)depth_base + next_col * 2))) >> 3;
                    if ((u32)ot_index < 0x1E0) {
                        display = *(u8 * *)display_root;
                        line = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = (u8 *)line + 0x14;

                        display = *(u8 * *)display_root;
                        tpage = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = tpage + 0x0C;

                        func_80067F20(tpage, 0, 0,(u16)(((u16)func_80066460(0, 1, 0, 0))), 0);

                        line->color0 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        line->color1 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        func_800667D0(line);
                        func_80066640(line, 1);

                        line->xy0 = ((R12_80173FDC_S_80173FDC_7 *)ring_xy)->unk_00;
                        line->xy1 = (*(u32 *)((u8 *)xy_base + next_col * 4));

                        line->tag = (line->tag & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)line & addr_mask);

                        ((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 = (((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)tpage & addr_mask);
                    }
                    ring_xy -= 4;
                    ring_depth -= 2;
                    col--;
                }
                xy_row -= 0x20;
                ring_depth_row -= 0x10;
                row -= 8;
            }
        }

        {

            next_node = (s32)((R12_80173FDC_S_80173FDC_0_pre *)node)[-1].unk_00;
            if (next_node == 0) {
                break;
            }
            node = (u8 *)next_node + 0x20;
            next_node = (s32)((R12_80173FDC_S_80173FDC_8 *)next_node)->unk_08;
        }
    }
    return 0;
}
