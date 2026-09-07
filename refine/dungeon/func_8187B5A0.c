#include "common.h"

#define FIELD_U8(base, off)  (*(u8 *)((u8 *)(base) + (off)))
#define FIELD_S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define FIELD_U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define FIELD_U32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define FIELD_PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))
#define VOL_U32(base, off) (*(volatile u32 *)((u8 *)(base) + (off)))
#define VOL_PTR(base, off) (*(u8 * volatile *)((u8 *)(base) + (off)))

extern u8 D_80080000[];
extern void func_80024DF8() __attribute__((noreturn));
extern u32 func_80065420();
extern s32 func_80066460();
extern s32 func_80067F20();

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 func_8187B5A0(u8 *render_data, u8 *source_vertex)
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
    register u32 length_mask ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    u32 address_mask;
    u32 *mode_ot_entry;
    register u8 *tail_scratch ASM_REG("$4");   /* MATCH pin: retail delay-slot contents depend on it */

    context = FIELD_PTR(D_80080000, 0x3160);
    context_slot = (u8 **)(D_80080000 + 0x3160);
    ASM_KEEP_NV(context_slot);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    address_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(length_mask);   /* MATCH pin: retail schedule: same instructions, different order without it */
    FIELD_PTR(scratch, 0x18) = FIELD_PTR(context, 0x8D0);
    FIELD_PTR(scratch, 0x20) = context + 0xB0;
    ASM_KEEP(scratch);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    point_packet = VOL_PTR(scratch, 0x18);
    vertex_x = FIELD_U16(vertex, 2);
    FIELD_U16(scratch, 0) = vertex_x;
    FIELD_U16(scratch, 2) = FIELD_U16(vertex, 6);
    FIELD_U16(scratch, 4) = FIELD_U16(vertex, 0xA);
    FIELD_PTR(scratch, 0x18) = point_packet + 0xC;

    depth_index = func_80065420(scratch, point_packet + 8, scratch + 0x90, scratch + 0x94);
    FIELD_U32(scratch, 0xC0) = depth_index;
    if (depth_index < 0x1E0U) {
        FIELD_U32(point_packet, 4) = FIELD_U32(render_data, 0);
        FIELD_U8(point_packet, 4) = (u8)((FIELD_U8(point_packet, 4) * FIELD_S16(render_data, 0x10)) /
                                  FIELD_S16(render_data, 0x12));
        FIELD_U8(point_packet, 5) = (u8)((FIELD_U8(point_packet, 5) * FIELD_S16(render_data, 0x10)) /
                                  FIELD_S16(render_data, 0x12));
        blue = (u8)((FIELD_U8(point_packet, 6) * FIELD_S16(render_data, 0x10)) /
                    FIELD_S16(render_data, 0x12));
        FIELD_U8(point_packet, 3) = 2;
        FIELD_U8(point_packet, 7) = 0x6A;
        FIELD_U8(point_packet, 6) = blue;

        FIELD_U32(point_packet, 0) = (FIELD_U32(point_packet, 0) & length_mask) |
            (*(u32 *)((VOL_U32(scratch, 0xC0) * 4) + (u32)VOL_PTR(scratch, 0x20)) & address_mask);
        {
            u32 *ot_entry;
            register u32 ot_tag ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            ot_entry = (u32 *)((VOL_U32(scratch, 0xC0) * 4) +
                              (u32)VOL_PTR(scratch, 0x20));
            ot_tag = *ot_entry;
            *ot_entry = (ot_tag & length_mask) |
                       ((u32)point_packet & address_mask);
        }

        mode_packet = FIELD_PTR(scratch, 0x18);
        FIELD_PTR(scratch, 0x18) = mode_packet + 0xC;
        func_80067F20(mode_packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

        FIELD_U32(mode_packet, 0) = (FIELD_U32(mode_packet, 0) & length_mask) |
            (*(u32 *)((VOL_U32(scratch, 0xC0) * 4) + (u32)VOL_PTR(scratch, 0x20)) & address_mask);
        mode_ot_entry = (u32 *)((VOL_U32(scratch, 0xC0) * 4) + (u32)VOL_PTR(scratch, 0x20));
        *mode_ot_entry = (*mode_ot_entry & length_mask) | ((u32)mode_packet & address_mask);
    }

    next_node = FIELD_PTR(render_data, -8);
    render_data = next_node + 0x20;
    if (next_node != 0) {
        vertex = FIELD_PTR(next_node, 8);
        ASM_KEEP(render_data);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(vertex);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        tail_scratch = scratch;
        ASM_TAILSLOT_PIN_TIED(tail_scratch);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024DF8();
    }
    FIELD_PTR(*context_slot, 0x8D0) = FIELD_PTR(scratch, 0x18);
    return 0;
}
