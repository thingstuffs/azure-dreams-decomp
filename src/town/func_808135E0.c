#include "common.h"

extern u8 *D_8012F130;

extern s32 func_8006BC50(void *, void *, s32 *, s32 *);
extern u32 func_8006D9DC(s32, s32, s32, s32);
extern void func_8006DBBC(void *, s32);
extern void func_8006DD38(void *);
extern void func_8006F49C(void *, s32, s32, u32, s32);

/* Builds line and draw-state packets for visible list items and links them by depth. */
s32 func_808135E0(void *first_item)
{
    u8 *item;
    u8 **render_context;
    u8 *line_pool;
    u8 *pool_or_endpoint;
    u8 *line_table;
    register u8 *work_ptr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *state_pool;
    u8 *state_table;
    u8 *line_packet;
    u8 *after_line;
    u8 *after_state;
    u8 *state_packet;
    u32 *line_head;
    u32 *line_slot;
    u32 *state_head;
    u32 *state_slot;
    register u32 address_mask ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 length_mask;
    s32 screen_coords[2];
    s32 *screen_y;
    register s32 *out_x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 *out_y ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 start_depth;
    register s32 depth_sum ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 end_depth;
    s32 depth_index;
    s32 table_offset;
    u32 draw_mode;

    item = first_item;
    render_context = &D_8012F130;
    screen_y = &screen_coords[1];
    address_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;

    do {
        if ((*(u16 *)(item + 0x24) & 1) == 0) {
            after_line = 0;
            line_pool = *render_context;
            line_packet = *(u8 **)(line_pool + 0x8D0);
            pool_or_endpoint = line_pool;
            if (line_packet != 0) {
                u32 line_pool_limit;
                line_pool_limit = 0x108D4;
                after_line = line_packet + 0x10;
                after_line = (u8 *)((u32)after_line & -(u32)(after_line <= pool_or_endpoint + line_pool_limit));
            }
            *(u8 **)(line_pool + 0x8D0) = after_line;

            *(u32 *)(line_packet + 4) = *(u32 *)(item + 0x14);
            func_8006DD38(line_packet);
            func_8006DBBC(line_packet, 1);

            start_depth = func_8006BC50(item + 4, line_packet + 8, &screen_coords[0], screen_y);
            work_ptr = item + 0xC;
            pool_or_endpoint = line_packet + 0xC;
            out_x = &screen_coords[0];
            out_y = screen_y;
            ASM_USE2(out_x, out_y);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            depth_sum = start_depth;
            end_depth = func_8006BC50(work_ptr, pool_or_endpoint, out_x, out_y);
            depth_sum = (s16)depth_sum;
            depth_sum += end_depth;
            depth_index = depth_sum >> 1;
            if ((u16)depth_index < 0x200) {
                depth_index = (s16)depth_index;
                table_offset = depth_index * 4;
                line_table = *render_context;
                line_head = (u32 *)(table_offset + (u32)line_table + 0xB0);
                *(u32 *)line_packet = (*(u32 *)line_packet & length_mask) | (*line_head & address_mask);

                work_ptr = *render_context;
                line_slot = (u32 *)(table_offset + (u32)work_ptr + 0xB0);
                *line_slot = (*line_slot & length_mask) | ((u32)line_packet & address_mask);

                state_pool = *render_context;
                after_state = 0;
                state_packet = *(u8 **)(state_pool + 0x8D0);
                work_ptr = state_pool;
                if (state_packet != 0) {
                    register u32 state_pool_limit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    state_pool_limit = 0x108D4;
                    after_state = state_packet + 0xC;
                    after_state = (u8 *)((u32)after_state & -(u32)(after_state <= work_ptr + state_pool_limit));
                }

                *(u8 **)(state_pool + 0x8D0) = after_state;
                draw_mode = func_8006D9DC(0, 0, 0, 0);
                func_8006F49C(state_packet, 0, 0, (u16)draw_mode, 0);

                state_table = *render_context;
                state_head = (u32 *)(table_offset + (u32)state_table + 0xB0);
                *(u32 *)state_packet = (*(u32 *)state_packet & length_mask) | (*state_head & address_mask);

                work_ptr = *render_context;
                state_slot = (u32 *)(table_offset + (u32)work_ptr + 0xB0);
                *state_slot = (*state_slot & length_mask) | ((u32)state_packet & address_mask);
            }
        }

        work_ptr = *(u8 **)(item - 8);
        item = work_ptr + 0x20;
    } while (work_ptr != 0);

    ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return 0;
}

/* MECHANISM: A two-word screen_coords frame line_packet yields sp+0x18 and held s7=sp+0x1c.
   Split v0 bound live ranges and short ABI pins reproduce both pool/RMW regions.
   Prepared a0-a3 plus ASM_USE2 fences sink the depth_sum-result copy into the jal slot. */
