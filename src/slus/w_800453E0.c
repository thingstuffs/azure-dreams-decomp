#include "common.h"

typedef struct Command Command;
typedef struct Entry Entry;
typedef struct Packet Packet;

struct Entry {
    u8 pad00[6];
    s16 depth_bias;
    Command *commands;
    union {
        u32 word;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u8 mode;
        } bytes;
    } packet;
    u16 texture_bias;
    u16 texture_base;
    u16 flags;
    u16 angle_x;
    u16 angle_y;
    u16 angle_z;
    u16 scale_x;
    u16 scale_y;
    u16 sprite_w;
    u16 sprite_h;
};

struct Command {
    u8 flags;
    u8 mode;
    s8 x;
    s8 y;
    u16 attr;
    u16 texture_offset;
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
};

struct Packet {
    u32 tag;
    u32 packet_word;
    u16 x0;
    u16 y0;
    u16 u0;
    u16 v0;
    u16 x1;
    u16 y1;
    u16 u1;
    u16 attr;
    u16 x2;
    u16 y2;
    u16 u2;
    u16 v2;
    u16 x3;
    u16 y3;
    u16 u3;
    u16 v3;
};

typedef s32 (*CommandFn)(void *, void *, Entry *, Command *, Packet *);

extern void *D_80083160[3];
extern u32 D_8006CD30[8];
extern s32 D_80081510;

extern u32 RotTransPers(void *, void *, void *, void *);
extern void RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void RotMatrix(void *, void *);
extern void ScaleMatrix(void *, void *);
extern void CompMatrix(void *, void *, void *);
extern void SetTransMatrix(void *);
extern void SetRotMatrix(void *);

#define SP8(base, off)  (*(u8 *)((base) + (off)))
#define SPS8(base, off) (*(s8 *)((base) + (off)))
#define SP16(base, off) (*(u16 *)((base) + (off)))
#define SPS16(base, off) (*(s16 *)((base) + (off)))
#define SP32(base, off) (*(u32 *)((base) + (off)))
#define E8(base, off) (*(u8 *)((u8 *)(base) + (off)))
#define E16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define E32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define C8(base, off) (*(u8 *)((u8 *)(base) + (off)))
#define CS8(base, off) (*(s8 *)((u8 *)(base) + (off)))
#define C16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define P16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define PS16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define P32(base, off) (*(u32 *)((u8 *)(base) + (off)))

/* Project sprite commands and link visible textured quads into the ordering table. */
void func_800453E0(void *context, void *position, Entry *entry, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    void **render_state = D_80083160;
    Packet *packet;
    Command *command;
    u32 projected_depth;
    u32 sort_depth;
    s32 callback_result;
    s16 coord;
    u32 sprite_extent;
    s32 rotation_y;
    u32 scale_x;
    u32 scale_y;
    u32 vertex_0_visible;
    u32 vertex_1_visible;
    u32 vertex_2_visible;
    u32 vertex_3_visible;
    u32 any_visible;
    u32 uv_edge;
    u32 address_mask;
    u8 uv_start;
    u8 uv_extent;

    SP32(scratch, 0xEC) = 0;
    SP16(scratch, 0x8C) = 0;
    SP16(scratch, 0x84) = 0;
    SP16(scratch, 0x7C) = 0;
    SP16(scratch, 0x74) = 0;
    SP32(scratch, 0x20) = (u32)render_state[0] + 0xB0;

    SP16(scratch, 0x00) = *(u16 *)((u8 *)position + 2);
    SP16(scratch, 0x02) = *(u16 *)((u8 *)position + 6);
    SP16(scratch, 0x04) = *(u16 *)((u8 *)position + 0xA);
    packet = *(Packet **)((u8 *)render_state[0] + 0x8D0);

    SP32(scratch, 0xC0) = RotTransPers(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
    E16(entry, 0x14) |= 0x8000;
    projected_depth = *(volatile u32 *)(scratch + 0xC0);
    {
        u32 base_depth;
        sort_depth = (base_depth = projected_depth - 10, base_depth - depth_bias);
    }
    D_8006CD30[7] = projected_depth * 4;
    SP32(scratch, 0xC0) = sort_depth;

    if (sort_depth < 0x1D6U) {
        PushMatrix();
        address_mask = 0xFFFFFF;

        {
            register u8 *rotation_input ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            u16 screen_x;
            register u32 matrix_arg_guard ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s32 rotation_z;
            rotation_input = scratch;
            ASM_KEEP_NV(rotation_input);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            screen_x = *(volatile u16 *)(scratch + 0xB8);
            rotation_input = (u8 *)((u32)rotation_input | 0x100);
            SP16(scratch, 0xB8) = screen_x - 0xA0;
            SP16(scratch, 0xBA) -= 0x78;
            SP32(scratch, 0x30) = *(s16 *)((u8 *)render_state + 0xC4);
            SP32(scratch, 0x34) = *(s16 *)((u8 *)render_state + 0xC6);
            SP32(scratch, 0x38) = *(s16 *)((u8 *)render_state + 0xC8);

            SP16(scratch, 0x100) = E16(entry, 0x16);
            ASM_KEEP_NV(matrix_arg_guard);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            rotation_z = *(u16 *)((u8 *)render_state + 0xB8) +
                (E16(entry, 0x1A) - SP16(scratch, 0x34));
            SP16(scratch, 0x104) = rotation_z;
            ASM_USE2_NV(matrix_arg_guard, rotation_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            rotation_y = E16(entry, 0x18) - 0x100;
            rotation_y += (SP16(scratch, 0x38) + 0x100) & 0x1FF;
            SP16(scratch, 0x102) = rotation_y;
            sprite_extent = E16(entry, 0x20);
            SP32(scratch, 0xE4) = sprite_extent;
            SP16(scratch, 0x108) = sprite_extent;
            sprite_extent = E16(entry, 0x22);
            SP32(scratch, 0xE8) = sprite_extent;
            SP16(scratch, 0x10A) = sprite_extent;

            RotMatrix(rotation_input, scratch + 0xD0);
        }
        scale_x = E16(entry, 0x1C);
        SP32(scratch, 0x30) = scale_x;
        scale_y = E16(entry, 0x1E);
        SP32(scratch, 0x38) = 0x1000;
        SP32(scratch, 0x34) = scale_y;
        ScaleMatrix(scratch + 0xD0, scratch + 0x30);
        CompMatrix(D_8006CD30, scratch + 0xD0, scratch + 0x50);
        SetTransMatrix(scratch + 0x50);
        SetRotMatrix(scratch + 0x50);

        command = *(Command **)((u8 *)entry + 8);
        SP16(scratch, 0x24) = E16(entry, 0x14);

        do {
            if (!(C8(command, 0) & 0x20)) {
                uv_start = C8(command, 8);
                SP32(scratch, 0x08) = uv_start;
                uv_extent = C8(command, 0xA);
                SP32(scratch, 0x10) = uv_extent;
                if ((uv_start + uv_extent >= 0x100) || E16(entry, 0x1A) != 0) {
                    SP32(scratch, 0x10) = uv_extent - 1;
                }

                uv_start = C8(command, 9);
                SP32(scratch, 0x0C) = uv_start;
                uv_extent = C8(command, 0xB);
                SP32(scratch, 0x14) = uv_extent;
                if ((uv_start + uv_extent >= 0x100) || E16(entry, 0x1A) != 0) {
                    SP32(scratch, 0x14) = uv_extent - 1;
                }

                if ((C8(command, 0) ^ SP16(scratch, 0x24)) & 1) {
                    coord = -CS8(command, 2) - SP16(scratch, 0x108);
                    SP16(scratch, 0x80) = coord;
                    SP16(scratch, 0x70) = coord;
                    coord -= SP16(scratch, 0x10);
                    SP16(scratch, 0x88) = coord;
                    SP16(scratch, 0x78) = coord;
                } else {
                    coord = CS8(command, 2) - SP16(scratch, 0x108);
                    SP16(scratch, 0x80) = coord;
                    SP16(scratch, 0x70) = coord;
                    coord += SP16(scratch, 0x10);
                    SP16(scratch, 0x88) = coord;
                    SP16(scratch, 0x78) = coord;
                }

                if ((C8(command, 0) ^ SP16(scratch, 0x24)) & 2) {
                    coord = SP16(scratch, 0x13C) + (-CS8(command, 3) - SP16(scratch, 0x10A));
                    SP16(scratch, 0x7A) = coord;
                    SP16(scratch, 0x72) = coord;
                    coord -= SP16(scratch, 0x14);
                    SP16(scratch, 0x8A) = coord;
                    SP16(scratch, 0x82) = coord;
                } else {
                    coord = SP16(scratch, 0x13C) + (CS8(command, 3) - SP16(scratch, 0x10A));
                    SP16(scratch, 0x7A) = coord;
                    SP16(scratch, 0x72) = coord;
                    coord += SP16(scratch, 0x14);
                    SP16(scratch, 0x8A) = coord;
                    SP16(scratch, 0x82) = coord;
                }

                RotTransPers4(scratch + 0x70, scratch + 0x78,
                    scratch + 0x80, scratch + 0x88,
                    scratch + 0xF0, scratch + 0xF4,
                    scratch + 0xF8, scratch + 0xFC,
                    scratch + 0x90, scratch + 0x94);

                *(volatile u16 *)((u8 *)packet + 0x08) = SP16(scratch, 0xF0) + SP16(scratch, 0xB8);
                *(volatile u16 *)((u8 *)packet + 0x0A) = SP16(scratch, 0xF2) + SP16(scratch, 0xBA);
                *(volatile u16 *)((u8 *)packet + 0x10) = SP16(scratch, 0xF4) + SP16(scratch, 0xB8);
                *(volatile u16 *)((u8 *)packet + 0x12) = SP16(scratch, 0xF6) + SP16(scratch, 0xBA);
                *(volatile u16 *)((u8 *)packet + 0x18) = SP16(scratch, 0xF8) + SP16(scratch, 0xB8);
                *(volatile u16 *)((u8 *)packet + 0x1A) = SP16(scratch, 0xFA) + SP16(scratch, 0xBA);
                vertex_0_visible = 0;
                *(volatile u16 *)((u8 *)packet + 0x20) = SP16(scratch, 0xFC) + SP16(scratch, 0xB8);
                coord = SP16(scratch, 0xFE) + SP16(scratch, 0xBA);
                P16(packet, 0x22) = coord;

                if ((u16)(P16(packet, 8) + 0x20) < 0x181U) {
                    vertex_0_visible = (u16)(P16(packet, 0xA) + 0x20) < 0x121U;
                }
                vertex_1_visible = 0;
                if ((u16)(P16(packet, 0x10) + 0x20) < 0x181U) {
                    vertex_1_visible = (u16)(P16(packet, 0x12) + 0x20) < 0x121U;
                }
                vertex_2_visible = 0;
                if ((vertex_0_visible = vertex_1_visible | vertex_0_visible,
                     (u16)(P16(packet, 0x18) + 0x20) < 0x181U)) {
                    vertex_2_visible = (u16)(P16(packet, 0x1A) + 0x20) < 0x121U;
                }
                vertex_3_visible = 0;
                if ((any_visible = vertex_0_visible | vertex_2_visible,
                     (u16)(P16(packet, 0x20) + 0x20) < 0x181U)) {
                    vertex_3_visible = (u16)(coord + 0x20) < 0x121U;
                }
                if (any_visible | vertex_3_visible) {
                    *(u8 *)((u8 *)packet + 3) = 9;
                    E16(entry, 0x14) &= 0x7FFF;

                    SP32(scratch, 0x10) += SP32(scratch, 0x08);
                    SP32(scratch, 0x14) =
                        (SP32(scratch, 0x14) + SP32(scratch, 0x0C)) << 8;
                    SP32(scratch, 0x0C) <<= 8;

                    if (SP16(scratch, 0x24) & 0x100) {
                        P16(packet, 0xE) = E16(entry, 0x12);
                    } else {
                        P16(packet, 0xE) = E16(entry, 0x12) + C16(command, 6);
                    }
                    P16(packet, 0xC) = SP16(scratch, 0x0C) + SP16(scratch, 0x08);
                    P16(packet, 0x14) = SP16(scratch, 0x0C) + SP16(scratch, 0x10);
                    if (E16(entry, 0x10) != 0) {
                        P16(packet, 0x16) = E16(entry, 0x10) + (C16(command, 4) & 0xFF9F);
                    } else {
                        P16(packet, 0x16) = C16(command, 4);
                    }
                    P16(packet, 0x1C) = SP16(scratch, 0x14) | SP16(scratch, 0x08);
                    P16(packet, 0x24) = SP16(scratch, 0x14) | SP16(scratch, 0x10);

                    if (SPS16(scratch, 0x50) >= 0x1800) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x24);
                        *(u8 *)((u8 *)packet + 0x24) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x14) = uv_edge;
                    }
                    if (SPS16(scratch, 0x58) >= 0x1800) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x25);
                        *(u8 *)((u8 *)packet + 0x25) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x1D) = uv_edge;
                    }
                    if (PS16(packet, 8) > PS16(packet, 0x20)) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x24);
                        *(u8 *)((u8 *)packet + 0x24) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x14) = uv_edge;
                    }
                    if (PS16(packet, 0xA) > PS16(packet, 0x22)) {
                        uv_edge = *(u8 *)((u8 *)packet + 0x25);
                        *(u8 *)((u8 *)packet + 0x25) = uv_edge + 0xFF;
                        *(u8 *)((u8 *)packet + 0x1D) = uv_edge;
                    }

                    {
                        u32 command_mode;
                        u32 entry_flags;
                        u32 packet_mode;
                        command_mode = C8(command, 1);
                        E8(entry, 0x0F) = command_mode;
                        entry_flags = SP16(scratch, 0x24);
                        if (entry_flags & 8) {
                            if (entry_flags & 4) {
                                packet_mode = command_mode | 2;
                            } else {
                                packet_mode = command_mode & 0xFD;
                            }
                            E8(entry, 0x0F) = packet_mode;
                        }
                    }

                    P32(packet, 4) = E32(entry, 0x0C);
                    {
                        s32 depth_delta;
                        depth_delta = -((u32)(D_80081510 * CS8(command, 3)) >> 14);
                        SP32(scratch, 0xCC) = depth_delta;
                        if (depth_delta > 0) {
                            SP32(scratch, 0xCC) = 0;
                        }
                    }

                    {
                        u32 depth_or_tag_mask = SP32(scratch, 0xC0);
                        u32 depth_offset = SP32(scratch, 0xCC);
                        if (depth_or_tag_mask + depth_offset < 0x1D6U) {
                            u32 depth_address;
                            u32 bucket_address;
                            u32 ordering_table;
                            do {
                                bucket_address = depth_offset * 4;
                                depth_address = depth_or_tag_mask * 4;
                            } while (0);
                            ordering_table = SP32(scratch, 0x20);
                            depth_or_tag_mask = 0xFF000000;
                            depth_address += ordering_table;
                            bucket_address += depth_address;
                            P32(packet, 0) = (P32(packet, 0) & depth_or_tag_mask) |
                                (*(u32 *)bucket_address & address_mask);
                            *(u32 *)(SP32(scratch, 0x20) +
                                (SP32(scratch, 0xC0) * 4) +
                                (SP32(scratch, 0xCC) * 4)) =
                                (*(u32 *)(SP32(scratch, 0x20) +
                                (SP32(scratch, 0xC0) * 4) +
                                (SP32(scratch, 0xCC) * 4)) & depth_or_tag_mask) |
                                ((u32)packet & address_mask);
                        }
                    }
                    packet++;
                }
            } else {
                CommandFn callback = *(CommandFn *)((u8 *)command + 8);
                if (callback != 0) {
                    SP32(scratch, 0xCC) = SP32(scratch, 0xC0);
                    callback_result = callback(context, position, entry, command, packet);
                    if (callback_result > 0) {
                        command = (Command *)(callback_result | 0x80000000U);
                    } else {
                        packet = (Packet *)callback_result;
                    }
                    SP32(scratch, 0xC0) = SP32(scratch, 0xCC);
                }
            }
        } while (CS8(command++, 0) >= 0);

        PopMatrix();
    }

    *(Packet **)((u8 *)render_state[0] + 0x8D0) = packet;
}
