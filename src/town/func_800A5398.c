#include "common.h"

extern u8 D_80083160[];

extern s32 func_80065420();
extern s32 func_80066460();
extern void func_80066640();
extern void func_800667D0();
extern void func_80067F20();
extern s32 rand();
extern void func_800A130C();

/* Queues a randomly colored line between two projected points with draw mode commands. */
void func_800A2AF8(s32 end_point, s32 start_point)
{
    s32 end_pos = end_point;
    s32 start_pos = start_point;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *draw_ctx;
    register u32 *line ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 *draw_mode;
    register s32 color_factor ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 depth_or_tpage;
    u32 low_mask = 0x00FFFFFF;
    u32 length_mask;
    register s32 texture_depth ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 texture_y ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    draw_ctx = *(u8 **)D_80083160;
    *(u8 **)(scratch + 0x24) = draw_ctx + 0xB0;
    line = *(u32 **)(draw_ctx + 0x8D0);
    *(u8 **)(draw_ctx + 0x8D0) = (u8 *)line + 0x14;

    color_factor = rand();
    line[1] = (color_factor * rand()) & low_mask;
    color_factor = rand();
    line[3] = (color_factor * rand()) & low_mask;

    func_800667D0(line);
    func_80066640(line, 1);

    func_800A130C(scratch + 0x74, start_pos);
    func_800A130C(scratch + 0x7C, end_pos);
    *(s32 *)(scratch + 0xC4) = func_80065420(
        scratch + 0x74, scratch + 0xE8, scratch + 0x94, scratch + 0x98);
    func_80065420(
        scratch + 0x7C, scratch + 0xEC, scratch + 0x94, scratch + 0x98);

    {
        register u16 start_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        depth_or_tpage = *(s32 *)(scratch + 0xC4);
        start_x = *(u16 *)(scratch + 0xE8);
        depth_or_tpage -= 0x30;
        *(s32 *)(scratch + 0xC4) = depth_or_tpage;
        *(u16 *)((u8 *)line + 8) = start_x;
    }
    *(u16 *)((u8 *)line + 0xA) = *(u16 *)(scratch + 0xEA);
    *(u16 *)((u8 *)line + 0x10) = *(u16 *)(scratch + 0xEC);
    *(u16 *)((u8 *)line + 0x12) = *(u16 *)(scratch + 0xEE);

    if (*(volatile s32 *)(scratch + 0xC4) >= 0x1E0) {
        *(s32 *)(scratch + 0xC4) = 0x1DF;
    }
    if (*(volatile s32 *)(scratch + 0xC4) < 0) {
        *(s32 *)(scratch + 0xC4) = 0;
    }

    draw_ctx = *(u8 **)D_80083160;
    draw_mode = *(u32 **)(draw_ctx + 0x8D0);
    *(u8 **)(draw_ctx + 0x8D0) = (u8 *)draw_mode + 0xC;
    depth_or_tpage = func_80066460(0, 0, 0x140, 0);
    func_80067F20(draw_mode, 1, 0, (u16)depth_or_tpage, 0);

    length_mask = 0xFF000000;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    texture_depth = 0;
    texture_y = 0;
    {
        u32 *ot_entry;
        ot_entry = (u32 *)(((u32)*(s32 *)(scratch + 0xC4) << 2) +
            (u32)*(u32 **)(scratch + 0x24));
        draw_mode[0] = (draw_mode[0] & length_mask) | (*ot_entry & low_mask);
    }
    {
        s32 ot_index = *(s32 *)(scratch + 0xC4);
        u32 ot_tag = ((u32 *)*(u32 **)(scratch + 0x24))[ot_index];
        ((u32 *)*(u32 **)(scratch + 0x24))[ot_index] =
            (ot_tag & length_mask) | ((u32)draw_mode & low_mask);
    }

    {
        u32 ot_tag;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ot_tag = ((u32 *)*(u32 **)(scratch + 0x24))[*(s32 *)(scratch + 0xC4)];
        line[0] = (line[0] & length_mask) | (ot_tag & low_mask);
    }
    {
        register s32 ot_index ASM_REG("$6") = *(s32 *)(scratch + 0xC4);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u32 ot_tag = ((u32 *)*(u32 **)(scratch + 0x24))[ot_index];
        ((u32 *)*(u32 **)(scratch + 0x24))[ot_index] =
            (ot_tag & length_mask) | ((u32)line & low_mask);
    }

    ASM_KEEP(line);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    draw_ctx = *(u8 **)D_80083160;
    draw_mode = *(u32 **)(draw_ctx + 0x8D0);
    *(u8 **)(draw_ctx + 0x8D0) = (u8 *)draw_mode + 0xC;
    depth_or_tpage = func_80066460(texture_depth, 1, 0x140, texture_y);
    func_80067F20(draw_mode, 1, 0, (u16)depth_or_tpage, 0);

    {
        u32 *ot_entry =
            (u32 *)(((u32)*(s32 *)(scratch + 0xC4) << 2) +
                (u32)*(u32 **)(scratch + 0x24));
        draw_mode[0] = (draw_mode[0] & length_mask) | (*ot_entry & low_mask);
    }
    {
        u32 ot_tag = ((u32 *)*(u32 **)(scratch + 0x24))[*(s32 *)(scratch + 0xC4)];
        ((u32 *)*(u32 **)(scratch + 0x24))[*(s32 *)(scratch + 0xC4)] =
            (ot_tag & length_mask) | ((u32)draw_mode & low_mask);
    }
}
