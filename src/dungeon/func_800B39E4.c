#include "common.h"
#include "shared/game_work.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define P32(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[0x8D0];
    u8 *record;
} Root;

typedef struct {
    u8 pad70[0x70];
    u16 h70;
    u16 h72;
    u16 h74;
    u16 h76;
    u16 h78;
    u16 h7A;
    u16 h7C;
    u16 h7E;
    u16 h80;
    u16 h82;
    u16 h84;
    u16 h86;
    u16 h88;
    u16 h8A;
    u8 pad8C[8];
    s32 w94;
    s32 w98;
    s32 wA0;
    s32 wA8;
    s32 wB0;
} Scratch;

typedef struct {
    u8 bytes[12];
} Record;


extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064B90(void *, void *, s32, s32);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(s32, void *);
extern void func_80067EF4();

/* Build transformed textured quads from sprite parts and append them to the draw list. */
void func_800B9144(void *position, void *context, s32 depth, s16 draw_mode)
{
    s32 (*callback)(void *, s32, void *, void *, void *);
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *sprite = P32(context, -0x14);
    s32 callback_arg = S32(context, -0x18);
    s16 saved_mode = draw_mode;
    Root *root = gameWork.unk_000;
    Record *part = P32(sprite, 8);
    Root **global_slot = ((Root * *)(&gameWork));
    u8 *scratch_base;
    u8 *packet;
    s32 mode_bits;
    s32 extent;
    u8 edge_byte;
    s32 tex_result;
    s32 y_component;

    U16(scratch, 0x8C) = 0;
    U16(scratch, 0x84) = 0;
    U16(scratch, 0x7C) = 0;
    U16(scratch, 0x74) = 0;
    packet = root->record;
    mode_bits = draw_mode << 16;
    S32(scratch, 0x20) = depth;
    S32(scratch, 0xC0) = 0;
    if (mode_bits != 0) {
        func_80067EF4(packet, 0, 0, mode_bits);
        func_8006658C(S32(scratch, 0x20), packet);
        packet += 12;
    }
    func_800649A0();

    {
        u16 *input = position;
        s32 x;
        s32 y;
        s32 raw_x;
        s32 raw_y;
        s32 x_component;

        raw_x = U16(input, 0);
        S16(scratch, 0x00) = raw_x;
        raw_y = U16(input, 2);
        x = (s16)raw_x;
        S16(scratch, 0x02) = raw_y;
        scratch_base = (u8 *)0x1F800000;
        x_component = U16(sprite, 0x1C);
        y = (s16)raw_y;
        S32(scratch, 0x30) = x_component;
        y_component = U16(sprite, 0x1E);
        x_component = 0x1000;
        S32(scratch, 0x38) = x_component;
        S32(scratch, 0x34) = y_component;
        x_component = U16(sprite, 0x20);
        U16(scratch, 0x108) = x_component;
        x_component = (s16)x_component;
        y_component = U16(sprite, 0x22);
        x += x_component;
        S32(scratch, 0x40) = x;
        S32(scratch, 0x48) = 0;
        U16(scratch, 0x10A) = y_component;
        y_component <<= 16;
        y_component >>= 16;
        y += y_component;
        S32(scratch, 0x44) = y;
        func_80064B90((u8 *)scratch + 0x50, (u8 *)scratch + 0x40,
                      x, y);
        func_80065820(sprite + 0x16, scratch_base + 0x50);
        func_80064BC0(scratch_base + 0x50, (u8 *)scratch + 0x30);
        func_80064CF0(scratch_base + 0x50);
        func_80064D80(scratch_base + 0x50);
        U16(scratch, 0x24) = U16(sprite, 0x14);
        scratch_base += 0x94;
    }

    do {
        scratch = (Scratch *)0x1F800000;
        if (!(U8(part, 0) & 0x20)) {
            s32 edge;
            s16 edge1;
            s16 edge2;
            S32(scratch, 8) = U8(part, 8);
            S32(scratch, 0xC) = U8(part, 9);
            S32(scratch, 0x10) = U8(part, 0xA);
            S32(scratch, 0x14) = U8(part, 0xB);

            {
                if (((U8(part, 0) ^ U16(scratch, 0x24)) & 1) != 0) {

                    edge_byte = U8(part, 2);
                    y_component = U16(scratch, 0x108);
                    extent = U16(scratch, 0x10);
                    edge1 = (s8)edge_byte;
                    edge1 = -edge1 - y_component;
                    U16(scratch, 0x80) = edge1;
                    U16(scratch, 0x70) = edge1;
                    edge1 -= extent;
                    U16(scratch, 0x88) = edge1;
                    U16(scratch, 0x78) = edge1;
                } else {

                    edge_byte = U8(part, 2);
                    y_component = U16(scratch, 0x108);
                    extent = U16(scratch, 0x10);
                    edge1 = (s8)edge_byte;
                    edge1 -= y_component;
                    U16(scratch, 0x80) = edge1;
                    U16(scratch, 0x70) = edge1;
                    edge1 += extent;
                    U16(scratch, 0x88) = edge1;
                    U16(scratch, 0x78) = edge1;
                }
            }

            {
                if (((U8(part, 0) ^ U16(scratch, 0x24)) & 2) != 0) {

                    edge_byte = U8(part, 3);
                    y_component = U16(scratch, 0x10A);
                    extent = U16(scratch, 0x14);
                    edge2 = (s8)edge_byte;
                    edge2 = -edge2 - y_component;
                    U16(scratch, 0x7A) = edge2;
                    U16(scratch, 0x72) = edge2;
                    edge2 -= extent;
                    U16(scratch, 0x8A) = edge2;
                    U16(scratch, 0x82) = edge2;
                } else {

                    edge_byte = U8(part, 3);
                    y_component = U16(scratch, 0x10A);
                    extent = U16(scratch, 0x14);
                    edge2 = (s8)edge_byte;
                    edge2 -= y_component;
                    U16(scratch, 0x7A) = edge2;
                    U16(scratch, 0x72) = edge2;
                    edge2 += extent;
                    U16(scratch, 0x8A) = edge2;
                    U16(scratch, 0x82) = edge2;
                }
            }

            func_80065320((u16 *)scratch + 0x38, (u16 *)scratch + 0x4C, scratch_base);
            func_80065320((u16 *)scratch + 0x3C, (u16 *)scratch + 0x50, scratch_base);
            func_80065320((u16 *)scratch + 0x40, (u16 *)scratch + 0x54, scratch_base);
            func_80065320((u16 *)scratch + 0x44, (u16 *)scratch + 0x58, scratch_base);

            {
                s32 vertex_xy;

                vertex_xy = S32(scratch, 0x98);
                S32(packet, 8) = vertex_xy;
                vertex_xy = S32(scratch, 0xA0);
                S32(packet, 0x10) = vertex_xy;
                vertex_xy = S32(scratch, 0xA8);
                S32(packet, 0x18) = vertex_xy;
                depth = S32(scratch, 0xB0);
                vertex_xy = 9;
                U8(packet, 3) = vertex_xy;
                S32(packet, 0x20) = depth;
            }

            {
                s32 tex_extent;

                tex_extent = S32(scratch, 0x10);
                y_component = S32(scratch, 8);
                tex_extent -= 1;
                tex_result = tex_extent + y_component;
                S32(scratch, 0x10) = tex_result;
                if (tex_result & 0x100) {
                    tex_extent = tex_result - 1;
                    S32(scratch, 0x10) = tex_extent;
                }
            }
            {
                s32 tex_extent;

                tex_extent = S32(scratch, 0x14);
                y_component = S32(scratch, 0xC);
                tex_extent -= 1;
                tex_result = tex_extent + y_component;
                S32(scratch, 0x14) = tex_result;
                if (tex_result & 0x100) {
                    tex_extent = tex_result - 1;
                    S32(scratch, 0x14) = tex_extent;
                }
            }

            S32(scratch, 0x14) <<= 8;
            S32(scratch, 0xC) <<= 8;

            {
                s32 clut;
                s32 clut_offset = U16(sprite, 0x12);
                if (clut_offset != 0) {
                    if (U16(scratch, 0x24) & 0x100) {
                        U16(packet, 0x0E) = clut_offset;
                    } else {
                        clut = U16(part, 6);
                        U16(packet, 0x0E) = clut_offset + clut;
                    }
                } else {
                    clut = U16(part, 6);
                    U16(packet, 0x0E) = clut;
                }
            }

            S16(packet, 0x0C) = U16(scratch, 0xC) + U16(scratch, 8);
            S16(packet, 0x14) = U16(scratch, 0xC) + U16(scratch, 0x10);

            {
                s32 page_input;
                s32 page_offset = U16(sprite, 0x10);
                if (page_offset != 0) {
                    page_input = U16(part, 4);
                    page_input &= 0xFF9F;
                    edge = page_offset + page_input;
                } else {
                    edge = U16(part, 4);
                }
                U16(packet, 0x16) = edge;
            }
            {
                s16 edge_work;
                s32 uv_work;
                s32 uv_work_2;
                u16 right_u;
                s32 left_x;

                edge_work = U16(scratch, 0x14);
                uv_work = U16(scratch, 8);
                left_x = S16(packet, 8);
                edge_work |= uv_work;
                S16(packet, 0x1C) = edge_work;
                uv_work_2 = U16(scratch, 0x14);
                right_u = U16(scratch, 0x10);
                edge_work = S16(packet, 0x20);
                uv_work_2 |= right_u;
                edge_work = edge_work < left_x;
                S16(packet, 0x24) = uv_work_2;
                if (edge_work != 0) {
                    uv_work = U8(packet, 0x24);
                    edge_work = uv_work + 0xFF;
                    U8(packet, 0x24) = edge_work;
                    U8(packet, 0x14) = uv_work;
                }
            }
            {
                s32 bottom_y;
                s32 top_y;
                top_y = S16(packet, 0x0A);
                bottom_y = S16(packet, 0x22);
                if (bottom_y < top_y) {
                    top_y = U8(packet, 0x25);
                    bottom_y = top_y + 0xFF;
                    U8(packet, 0x25) = bottom_y;
                    U8(packet, 0x1D) = top_y;
                }
            }

            {
                s32 part_code = U8(part, 1);
                s32 draw_code;
                s32 draw_flags;
                U8(sprite, 0x0F) = part_code;
                draw_flags = U16(scratch, 0x24);
                draw_code = draw_flags & 8;
                if (draw_code != 0) {
                    draw_code = draw_flags & 4;
                    if (draw_code == 0) {
                        draw_code = part_code & 0xFD;
                    } else {
                        draw_code = part_code | 2;
                    }
                    U8(sprite, 0x0F) = draw_code;
                }
            }

            {
                u8 *draw_packet;
                s32 color_code;
                color_code = S32(sprite, 0x0C);
                draw_packet = packet;
                S32(packet, 4) = color_code;
                func_8006658C(S32(scratch, 0x20), draw_packet);
                packet += 40;

            }
        } else {
            callback = P32(part, 8);
            if (callback != 0) {
                register s32 callback_result;
                callback_result = callback(context, callback_arg, sprite, part, packet);
                if (callback_result > 0) {
                    u32 cached_base = 0x80000000;
                    part = (Record *)(callback_result | cached_base);
                } else {
                    packet = (u8 *)callback_result;
                }
            }
        }

        if ((s8)U8(part++, 0) < 0) {
            break;
        }
    } while (1);
    {
        s32 end_mode_bits = saved_mode << 16;
        if (end_mode_bits != 0) {
            func_80067EF4(packet, 0, 1);
            func_8006658C(S32(scratch, 0x20), packet);
            packet += 12;
        }
    }
    func_80064A40();
    (*global_slot)->record = packet;
    return;
}
