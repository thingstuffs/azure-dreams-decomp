#include "common.h"

extern u8 *D_8012F130;

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

extern s32 func_8006BC50(void *, void *, s32 *, s32 *);
extern u32 func_8006D9DC(s32, s32, s32, s32);
extern void func_8006DBBC(void *, s32);
extern void func_8006DD38(void *);
extern void func_8006F49C(void *, s32, s32, u32, s32);

/* Builds line and draw-state packets for visible list items and links them by depth. */
s32 build_visible_item_line_packets(void *first_item)
{
    u8 *item;
    u8 **render_context;
    u8 *line_pool;
    u8 *pool_or_endpoint;
    u8 *line_table;
    u8 *work_ptr;
    u8 *state_work;
    u32 table_sum;
    u8 *state_pool;
    u8 *state_table;
    u8 *line_packet;
    u32 *line_slot;
    u32 *state_head;
    u32 *state_slot;
    s32 screen_coords[2];
    s32 *screen_y;
    s32 *out_x;
    s32 *out_y;
    s32 start_depth;
    s32 depth_sum;
    s32 first_depth;
    s32 end_depth;
    s32 depth_index;
    s32 table_offset;
    u32 next;
    u32 pool_limit;

    item = first_item;
    render_context = &D_8012F130;
    screen_y = &screen_coords[1];

    do {
        if ((*(u16 *)(item + 0x24) & 1) == 0) {
            depth_index = 0;
            line_pool = *render_context;
            line_packet = *(u8 **)(line_pool + 0x8D0);
            pool_or_endpoint = line_pool;
            if (line_packet != 0) {
                pool_limit = 0x108D4;
                depth_index = (s32)(line_packet + 0x10);
                pool_limit += (u32)pool_or_endpoint;
                pool_limit = (u32)depth_index <= pool_limit;
                pool_limit = -pool_limit;
                depth_index = (s32)((u32)depth_index & pool_limit);
            }
            *(u8 **)(line_pool + 0x8D0) = (u8 *)depth_index;

            *(u32 *)(line_packet + 4) = *(u32 *)(item + 0x14);
            func_8006DD38(line_packet);
            func_8006DBBC(line_packet, 1);

            line_pool = item + 4;
            start_depth = func_8006BC50(line_pool, line_packet + 8, &screen_coords[0], screen_y);
            line_pool = item + 0xC;
            pool_or_endpoint = line_packet + 0xC;
            out_x = &screen_coords[0];
            out_y = screen_y;
            first_depth = start_depth;
            end_depth = func_8006BC50(line_pool, pool_or_endpoint, out_x, out_y);
            depth_sum = (s16)first_depth + end_depth;
            depth_index = depth_sum >> 1;
            if ((u16)depth_index < 0x200) {
                depth_index = (s16)depth_index;
                table_offset = depth_index * 4;
                line_table = *render_context;
                out_x = (s32 *)(table_offset + (unsigned long)line_table + 0xB0);
                next = ((P_TAG *)out_x)->addr;
                *(u32 *)line_packet = (*(u32 *)line_packet & 0xFF000000) | (next & 0x00FFFFFF);

                work_ptr = *render_context;
                table_sum = table_offset + (u32)work_ptr;
                work_ptr = (u8 *)table_sum;
                line_slot = (u32 *)(work_ptr + 0xB0);
                *line_slot = (*line_slot & 0xFF000000) | ((u32)line_packet & 0x00FFFFFF);

                state_pool = *render_context;
                depth_index = 0;
                depth_sum = (s32)*(u8 **)(state_pool + 0x8D0);
                state_work = state_pool;
                if (depth_sum != 0) {
                    pool_limit = 0x108D4;
                    depth_index = depth_sum + 0xC;
                    pool_limit += (u32)state_work;
                    pool_limit = (u32)depth_index <= pool_limit;
                    pool_limit = -pool_limit;
                    depth_index = (s32)((u32)depth_index & pool_limit);
                }

                *(u8 **)(state_pool + 0x8D0) = (u8 *)depth_index;
                state_work = (u8 *)func_8006D9DC(0, 0, 0, 0);
                func_8006F49C((u8 *)depth_sum, 0, 0, (u16)((u32)state_work), 0);

                state_table = *render_context;
                state_head = (u32 *)(table_offset + (unsigned long)state_table + 0xB0);
                next = ((P_TAG *)state_head)->addr;
                *(u32 *)depth_sum = (*(u32 *)depth_sum & 0xFF000000) | (next & 0x00FFFFFF);

                work_ptr = *render_context;
                table_sum = table_offset + (u32)work_ptr;
                work_ptr = (u8 *)table_sum;
                state_slot = (u32 *)(work_ptr + 0xB0);
                *state_slot = (*state_slot & 0xFF000000) | ((u32)depth_sum & 0x00FFFFFF);
            }
        }

        work_ptr = *(u8 **)(item - 8);
        item = work_ptr + 0x20;
    } while (work_ptr != 0);

    return 0;
}
