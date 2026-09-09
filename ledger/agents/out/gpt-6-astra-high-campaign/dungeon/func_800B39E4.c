#include "common.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define VU8(p, o) (*(volatile u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define VU16(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))
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

extern Root *D_80083160[];

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
    register s16 saved_mode ASM_REG("$23") = draw_mode;
    Root *root = D_80083160[0];
    Record *part = P32(sprite, 8);
    Root **global_slot = D_80083160;
    u8 *scratch_base;
    u8 *packet;
    s32 mode_bits;

    VU16(scratch, 0x8C) = 0;
    VU16(scratch, 0x84) = 0;
    VU16(scratch, 0x7C) = 0;
    VU16(scratch, 0x74) = 0;
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
        register s32 x ASM_REG("$6");
        register s32 y ASM_REG("$7");
        s32 x_component;
        register s32 y_component ASM_REG("$3");

        x = U16(input, 0);
        S16(scratch, 0x00) = x;
        y = U16(input, 2);
        x = (s16)x;
        S16(scratch, 0x02) = y;
        scratch_base = (u8 *)0x1F800000;
        x_component = U16(sprite, 0x1C);
        y = (s16)y;
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
        y_component = (s16)y_component;
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

next_part:
    if (!(U8(part, 0) & 0x20)) {
        S32(scratch, 8) = U8(part, 8);
        S32(scratch, 0xC) = U8(part, 9);
        S32(scratch, 0x10) = U8(part, 0xA);
        S32(scratch, 0x14) = U8(part, 0xB);

        {
            register s32 edge ASM_REG("$2");
            if (((U8(part, 0) ^ U16(scratch, 0x24)) & 1) != 0) {
                register s32 origin_x ASM_REG("$3");
                s32 width;

                edge = VU8(part, 2);
                origin_x = U16(scratch, 0x108);
                width = U16(scratch, 0x10);
                edge = (s8)edge;
                edge = -edge - origin_x;
                U16(scratch, 0x80) = edge;
                U16(scratch, 0x70) = edge;
                edge -= width;
            } else {
                s32 origin_x;
                s32 width;

                edge = VU8(part, 2);
                origin_x = U16(scratch, 0x108);
                width = U16(scratch, 0x10);
                edge = (s8)edge;
                edge -= origin_x;
                U16(scratch, 0x80) = edge;
                U16(scratch, 0x70) = edge;
                edge += width;
            }
            U16(scratch, 0x88) = edge;
            U16(scratch, 0x78) = edge;
        }

        {
            register s32 edge ASM_REG("$2");
            if (((U8(part, 0) ^ U16(scratch, 0x24)) & 2) != 0) {
                register s32 origin_y ASM_REG("$3");
                s32 height;

                edge = VU8(part, 3);
                origin_y = U16(scratch, 0x10A);
                height = U16(scratch, 0x14);
                edge = (s8)edge;
                edge = -edge - origin_y;
                U16(scratch, 0x7A) = edge;
                U16(scratch, 0x72) = edge;
                edge -= height;
            } else {
                s32 origin_y;
                s32 height;

                edge = VU8(part, 3);
                origin_y = U16(scratch, 0x10A);
                height = U16(scratch, 0x14);
                edge = (s8)edge;
                edge -= origin_y;
                U16(scratch, 0x7A) = edge;
                U16(scratch, 0x72) = edge;
                edge += height;
            }
            U16(scratch, 0x8A) = edge;
            U16(scratch, 0x82) = edge;
        }

        ASM_KEEP(scratch);
        func_80065320((u16 *)scratch + 0x38, (u16 *)scratch + 0x4C, scratch_base);
        func_80065320((u16 *)scratch + 0x3C, (u16 *)scratch + 0x50, scratch_base);
        func_80065320((u16 *)scratch + 0x40, (u16 *)scratch + 0x54, scratch_base);
        func_80065320((u16 *)scratch + 0x44, (u16 *)scratch + 0x58, scratch_base);

        {
            s32 vertex_xy;
            register s32 last_vertex_xy ASM_REG("$3");

            vertex_xy = S32(scratch, 0x98);
            S32(packet, 8) = vertex_xy;
            vertex_xy = S32(scratch, 0xA0);
            S32(packet, 0x10) = vertex_xy;
            vertex_xy = S32(scratch, 0xA8);
            S32(packet, 0x18) = vertex_xy;
            last_vertex_xy = S32(scratch, 0xB0);
            vertex_xy = 9;
            U8(packet, 3) = vertex_xy;
            S32(packet, 0x20) = last_vertex_xy;
        }

        {
            s32 tex_extent;
            register s32 tex_end ASM_REG("$3");

            tex_extent = S32(scratch, 0x10);
            tex_end = S32(scratch, 8);
            tex_extent -= 1;
            tex_end = tex_extent + tex_end;
            S32(scratch, 0x10) = tex_end;
            if (tex_end & 0x100) {
                tex_extent = tex_end - 1;
                S32(scratch, 0x10) = tex_extent;
            }
        }
        {
            s32 tex_extent;
            register s32 tex_end ASM_REG("$3");

            tex_extent = S32(scratch, 0x14);
            tex_end = S32(scratch, 0xC);
            tex_extent -= 1;
            tex_end = tex_extent + tex_end;
            S32(scratch, 0x14) = tex_end;
            if (tex_end & 0x100) {
                tex_extent = tex_end - 1;
                S32(scratch, 0x14) = tex_extent;
            }
        }

        S32(scratch, 0x14) <<= 8;
        S32(scratch, 0xC) <<= 8;

        {
            register s32 clut ASM_REG("$2");
            s32 clut_offset = U16(sprite, 0x12);
            if (clut_offset != 0) {
                if (U16(scratch, 0x24) & 0x100) {
                    U16(packet, 0x0E) = clut_offset;
                } else {
                    clut = U16(part, 6);
                    clut = clut_offset + clut;
                    U16(packet, 0x0E) = clut;
                }
            } else {
                clut = U16(part, 6);
                U16(packet, 0x0E) = clut;
            }
        }

        S16(packet, 0x0C) = U16(scratch, 0xC) + U16(scratch, 8);
        S16(packet, 0x14) = U16(scratch, 0xC) + U16(scratch, 0x10);

        {
            register s32 tex_page ASM_REG("$2");
            s32 page_offset = U16(sprite, 0x10);
            if (page_offset != 0) {
                tex_page = U16(part, 4);
                tex_page &= 0xFF9F;
                tex_page = page_offset + tex_page;
            } else {
                tex_page = U16(part, 4);
            }
            U16(packet, 0x16) = tex_page;
        }
        {
            register s32 edge_work ASM_REG("$2");
            s32 uv_work;
            register s32 right_u ASM_REG("$4");
            register s32 left_x ASM_REG("$5");

            edge_work = U16(scratch, 0x14);
            uv_work = U16(scratch, 8);
            left_x = S16(packet, 8);
            edge_work |= uv_work;
            S16(packet, 0x1C) = edge_work;
            uv_work = U16(scratch, 0x14);
            right_u = U16(scratch, 0x10);
            edge_work = S16(packet, 0x20);
            uv_work |= right_u;
            edge_work = edge_work < left_x;
            S16(packet, 0x24) = uv_work;
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
            register s32 part_code ASM_REG("$4") = U8(part, 1);
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

    if ((s8)U8(part++, 0) >= 0) {
        goto next_part;
    }
    {
        register s32 end_mode_bits ASM_REG("$2") = saved_mode << 16;
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
