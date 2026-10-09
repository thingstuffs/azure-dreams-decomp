/* Selector 59, retail file [0x1990D98, 0x1990FE8); complete callable clone. */
#include "common.h"
#include "shared/game_work.h"

#define FIELD_U8(base, off)  (*(u8 *)((u8 *)(base) + (off)))
#define FIELD_S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define FIELD_U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define FIELD_U32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define FIELD_PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))

extern u32 func_80065420();
extern s32 func_80066460();
extern s32 func_80067F20();

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 func_80024598(u8 *render_data, u8 *source_vertex)
{
    u8 **context_slot;
    u8 *scratch;
    u8 *context;
    u8 *point_packet;
    u8 *mode_packet;
    u8 *next_node;
    u8 *vertex = source_vertex;
    u16 vertex_x;
    u8 blue;
    u32 depth_index;
    u32 length_mask;
    u32 address_mask;
    u32 *mode_ot_entry;

    context = *(u8 **)&gameWork;
    context_slot = (u8 **)&gameWork;
    address_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    FIELD_PTR(scratch, 0x18) = FIELD_PTR(context, 0x8D0);
    FIELD_PTR(scratch, 0x20) = context + 0xB0;
    do {
        point_packet = FIELD_PTR(scratch, 0x18);
        vertex_x = FIELD_U16(vertex, 2);
        FIELD_U16(scratch, 0) = vertex_x;
        FIELD_U16(scratch, 2) = FIELD_U16(vertex, 6);
        FIELD_U16(scratch, 4) = FIELD_U16(vertex, 0xA);
        FIELD_PTR(scratch, 0x18) = point_packet + 0xC;

        depth_index = func_80065420(scratch, point_packet + 8, scratch + 0x90, scratch + 0x94);
        FIELD_U32(scratch, 0xC0) = depth_index;
        if (depth_index < 0x1E0U) {
            FIELD_U32(point_packet, 4) = FIELD_U32(render_data, 8);
            FIELD_U8(point_packet, 4) = (u8)((FIELD_U8(point_packet, 4) * FIELD_S16(render_data, 0x32)) /
                                      FIELD_S16(render_data, 0x34));
            FIELD_U8(point_packet, 5) = (u8)((FIELD_U8(point_packet, 5) * FIELD_S16(render_data, 0x32)) /
                                      FIELD_S16(render_data, 0x34));
            blue = (u8)((FIELD_U8(point_packet, 6) * FIELD_S16(render_data, 0x32)) /
                        FIELD_S16(render_data, 0x34));
            FIELD_U8(point_packet, 3) = 2;
            FIELD_U8(point_packet, 7) = 0x6A;
            FIELD_U8(point_packet, 6) = blue;

            FIELD_U32(point_packet, 0) = (FIELD_U32(point_packet, 0) & length_mask) |
                (*(u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20)) & address_mask);
            {
                u32 *ot_entry;
                u32 ot_tag;
                ot_entry = (u32 *)((FIELD_U32(scratch, 0xC0) * 4) +
                                   (u32)FIELD_PTR(scratch, 0x20));
                ot_tag = *ot_entry;
                *ot_entry = (ot_tag & length_mask) |
                           ((u32)point_packet & address_mask);
            }

            mode_packet = FIELD_PTR(scratch, 0x18);
            FIELD_PTR(scratch, 0x18) = mode_packet + 0xC;
            func_80067F20(mode_packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

            FIELD_U32(mode_packet, 0) = (FIELD_U32(mode_packet, 0) & length_mask) |
                (*(u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20)) & address_mask);
            mode_ot_entry = (u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20));
            *mode_ot_entry = (*mode_ot_entry & length_mask) | ((u32)mode_packet & address_mask);
        }

        next_node = FIELD_PTR(render_data, -8);
        render_data = next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        vertex = FIELD_PTR(next_node, 8);
    } while (1);
    FIELD_PTR(*context_slot, 0x8D0) = FIELD_PTR(scratch, 0x18);
    return 0;
}
