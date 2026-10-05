#include "common.h"

typedef struct Scratch800D1A48
{
    u8 pad00[8];
    s32 data08;
    s32 data0C;
    s32 data10;
    s32 data14;
    u8 pad18[8];
    u8 *data20;
    u16 flags24;
    u8 pad26[0x4A];
    u16 data70;
    u16 data72;
    u8 pad74[4];
    u16 data78;
    u16 data7A;
    u8 pad7C[4];
    u16 data80;
    u16 data82;
    u8 pad84[4];
    u16 data88;
    u16 data8A;
    u8 pad8C[0x2C];
    u16 dataB8;
    u16 dataBA;
    u8 padBC[4];
    u32 dataC0;
    u8 padC4[0x2C];
    u16 dataF0;
    u16 dataF2;
    u16 dataF4;
    u16 dataF6;
    u16 dataF8;
    u16 dataFA;
    u16 dataFC;
    u16 dataFE;
    u8 pad100[8];
    u16 data108;
    u16 data10A;
}
Scratch800D1A48;
typedef struct OrderingTag { u32 addr : 24; u32 count : 8; } OrderingTag;
extern void *func_800654B0(u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *);
/* Build visible textured quads for the matching sprite and link them into the ordering table. */
void *func_800D71A8(u8 *sprite_list, s32 count_hint, s32 render_state_addr, u8 *placement, u8 *packet_buf)
{
    Scratch800D1A48 *scratch;
    s32 index;

    u8 *sprite;
    u8 *packet;
    u8 *part;
    u8 *quad;
    s32 bottom_y;

    sprite = 0;
    index = 0;
    packet = packet_buf;
    scratch = (Scratch800D1A48 *) 0x1F800000;
    {
        s16 sprite_count;
        sprite_count = *((s16 *) (((u8 *) sprite_list) + 0x9E));
        for (; index < sprite_count; index++) {
            u8 *sprite_entry = *((u8 **) (((u8 *) sprite_list) + 0xA4));
            if (sprite_entry != 0) {
                sprite = sprite_entry + 0x20;
                if ((*((u16 *) (((u8 *) placement) + 6))) == (*((u16 *) (((u8 *) sprite) + 6)))) {
                    break;
                }
            }
            sprite_list += 4;
        }
    }
    index = 0;
    if ((*((s16 *) (((u8 *) sprite) + 2))) > 0) {
        do {
            s32 part_offset;
            part_offset = (index * 3) << 4;
            part_offset += 8;
            part = sprite + part_offset;
            quad = *((u8 **) (((u8 *) part) + 8));
            for (;;) {
                if (!(quad[0] & 0x20)) {
                    scratch->data08 = quad[8];
                    scratch->data0C = quad[9];
                    scratch->data10 = quad[10];
                    scratch->data14 = quad[11];
                    {
                        s16 x;
                        u8 quad_flags;
                        quad_flags = quad[0];
                        if ((quad_flags ^ scratch->flags24) & 1) {
                            s32 width;
                            x = -(s8)quad[2] - scratch->data108;
                            width = *((u16 *) (((u8 *) scratch) + 0x10));
                            scratch->data80 = x;
                            scratch->data70 = x;
                            x -= width;
                            scratch->data88 = x;
                            scratch->data78 = x;
                        }
                        else {
                            s32 width;
                            width = *((u16 *) (((u8 *) scratch) + 0x10));
                            x = (s8)quad[2] + scratch->data108;
                            scratch->data80 = x;
                            scratch->data70 = x;
                            x += width;
                            scratch->data88 = x;
                            scratch->data78 = x;
                        }
                    }
                    {
                        s16 x;
                        if ((placement[0] ^ (*((u16 *) (((u8 *) ((u8 *) render_state_addr)) + 0x14)))) & 1) {
                            x = scratch->data80 - (s8)placement[2];
                            scratch->data80 = x;
                            scratch->data70 = x;
                            x = scratch->data88 - (s8)placement[2];
                            scratch->data88 = x;
                            scratch->data78 = x;
                        }
                        else {
                            x = scratch->data80 + (s8)placement[2];
                            scratch->data80 = x;
                            scratch->data70 = x;
                            x = scratch->data88 + (s8)placement[2];
                            scratch->data88 = x;
                            scratch->data78 = x;
                        }
                    }
                    {
                        s16 y;
                        u8 quad_flags;
                        quad_flags = quad[0];
                        if ((quad_flags ^ scratch->flags24) & 2) {
                            s32 width;
                            y = -(s8)quad[3] - scratch->data10A;
                            width = *((u16 *) (((u8 *) scratch) + 0x14));
                            scratch->data7A = y;
                            scratch->data72 = y;
                            y -= width;
                            scratch->data8A = y;
                            scratch->data82 = y;
                        }
                        else {
                            s32 width;
                            width = *((u16 *) (((u8 *) scratch) + 0x14));
                            y = (s8)quad[3] - scratch->data10A;
                            scratch->data7A = y;
                            scratch->data72 = y;
                            y += width;
                            scratch->data8A = y;
                            scratch->data82 = y;
                        }
                    }
                    {
                        s16 y;
                        if ((placement[0] ^ (*((u16 *) (((u8 *) ((u8 *) render_state_addr)) + 0x14)))) & 2) {
                            y = scratch->data7A - (s8)placement[3];
                            scratch->data7A = y;
                            scratch->data72 = y;
                            y = scratch->data8A - (s8)placement[3];
                            scratch->data8A = y;
                            scratch->data82 = y;
                        }
                        else {
                            y = scratch->data7A + (s8)placement[3];
                            scratch->data7A = y;
                            scratch->data72 = y;
                            y = scratch->data8A + (s8)placement[3];
                            scratch->data8A = y;
                            scratch->data82 = y;
                        }
                    }
                    func_800654B0(&scratch->data70, &scratch->data78, &scratch->data80, &scratch->data88, &scratch->dataF0,
                        &scratch->dataF4, &scratch->dataF8, &scratch->dataFC, (u16 *) (((u8 *) scratch) + 0x90),
                        (u16 *) (((u8 *) scratch) + 0x94));
                    *((u16 *) (packet + 0x8)) = scratch->dataF0 + scratch->dataB8;
                    *((u16 *) (packet + 0xA)) = scratch->dataF2 + scratch->dataBA;
                    *((u16 *) (packet + 0x10)) = scratch->dataF4 + scratch->dataB8;
                    *((u16 *) (packet + 0x12)) = scratch->dataF6 + scratch->dataBA;
                    *((u16 *) (packet + 0x18)) = scratch->dataF8 + scratch->dataB8;
                    *((u16 *) (packet + 0x1A)) = scratch->dataFA + scratch->dataBA;
                    *((u16 *) (packet + 0x20)) = scratch->dataFC + scratch->dataB8;
                    bottom_y = scratch->dataFE + scratch->dataBA;
                    *((s16 *) (packet + 0x22)) = bottom_y;
                    {
                        s32 pair_visible;
                        s32 clip_test;
                        s32 corner_visible;
                        s32 third_visible;
                        s32 any_visible;
                        pair_visible = 0;
                        if (((u16) ((*((u16 *) (packet + 0x8))) + 0x20)) < 0x181U) {
                            clip_test = (u16) ((*((u16 *) (packet + 0xA))) + 0x20);
                            pair_visible = clip_test < 0x121U;
                        }
                        corner_visible = 0;
                        if (((u16) ((*((u16 *) (packet + 0x10))) + 0x20)) < 0x181U) {
                            corner_visible = ((u16) ((*((u16 *) (packet + 0x12))) + 0x20)) < 0x121U;
                        }
                        third_visible = 0;
                        clip_test = (u16) ((*((u16 *) (packet + 0x18))) + 0x20);
                        pair_visible |= corner_visible;
                        if (clip_test < 0x181U) {
                            clip_test = (u16) ((*((u16 *) (packet + 0x1A))) + 0x20);
                            third_visible = clip_test < 0x121U;
                        }
                        corner_visible = 0;
                        any_visible = pair_visible | third_visible;
                        if (((u16) ((*((u16 *) (packet + 0x20))) + 0x20)) < 0x181U) {
                            corner_visible = ((u16) (bottom_y + 0x20)) < 0x121U;
                        }
                        clip_test = any_visible | corner_visible;
                        if (clip_test != 0) {
                            *((s8 *) (packet + 3)) = 9;
                            scratch->data10 += scratch->data08;
                            if (scratch->data10 & 0x100) {
                                scratch->data10 -= 1;
                            }
                            scratch->data14 += scratch->data0C;
                            if (scratch->data14 & 0x100) {
                                scratch->data14 -= 1;
                            }
                            scratch->data14 <<= 8;
                            scratch->data0C <<= 8;
                            *((s32 *) (packet + 0xC)) = (scratch->data0C + scratch->data08)
                                + (((*((u16 *) (((u8 *) ((u8 *) render_state_addr)) + 0x12)))
                                + (*((u16 *) (quad + 0x6)))) << 16);
                            *((s16 *) (packet + 0x14)) =
                                (*((u16 *) (((u8 *) scratch) + 0x0C))) + (*((u16 *) (((u8 *) scratch) + 0x10)));
                            {
                                u16 blend_mode;
                                u16 tpage;
                                blend_mode = *((u16 *) (((u8 *) ((u8 *) render_state_addr)) + 0x10));
                                if (blend_mode != 0) {
                                    tpage = blend_mode + ((*((u16 *) (quad + 0x4))) & 0xFF9F);
                                }
                                else {
                                    tpage = *((u16 *) (quad + 0x4));
                                }
                                *((u16 *) (packet + 0x16)) = tpage;
                            }
                            *((s16 *) (packet + 0x1C)) =
                                (*((u16 *) (((u8 *) scratch) + 0x14))) + (*((u16 *) (((u8 *) scratch) + 0x08)));
                            {
                                s32 bottom_right_uv;
                                s32 right_x;
                                s32 count_or_x;
                                bottom_right_uv = *((u16 *) (((u8 *) scratch) + 0x14));
                                bottom_right_uv += *((u16 *) (((u8 *) scratch) + 0x10));
                                *((s16 *) (packet + 0x24)) = bottom_right_uv;
                                count_or_x = *((s16 *) (packet + 0x8));
                                right_x = *((s16 *) (packet + 0x20));
                                if (right_x < count_or_x) {
                                    *((u8 *) (packet + 0x14)) -= 1;
                                    *((u8 *) (packet + 0x24)) -= 1;
                                }
                            }
                            if ((*((s16 *) (packet + 0xA))) > (*((s16 *) (packet + 0x22)))) {
                                *((u8 *) (packet + 0x1D)) -= 1;
                                *((u8 *) (packet + 0x25)) -= 1;
                            }
                            {
                                u16 part_flags;
                                u8 flags;
                                part_flags = *((u16 *) (((u8 *) part) + 0x14));
                                flags = quad[1];
                                *((u8 *) (((u8 *) part) + 0xF)) = flags;
                                if (part_flags & 8) {
                                    u8 draw_flags;
                                    if (part_flags & 4) {
                                        draw_flags = flags | 2;
                                    }
                                    else {
                                        draw_flags = flags & 0xFD;
                                    }
                                    *((u8 *) (((u8 *) part) + 0xF)) = draw_flags;
                                }
                            }
                            {
                                u8 flags;
                                if ((*((u16 *) (((u8 *) part) + 0x14))) & 0x10) {
                                    flags = (*((u8 *) (((u8 *) part) + 0xF))) | 1;
                                }
                                else {
                                    flags = (*((u8 *) (((u8 *) part) + 0xF))) & 0xFE;
                                }
                                *((u8 *) (((u8 *) part) + 0xF)) = flags;
                            }
                            *((s32 *) (packet + 0x4)) = *((s32 *) (((u8 *) part) + 0xC));
                            if (!((*((u16 *) (((u8 *) sprite) + 4))) & 0x8000)) {
                                ((OrderingTag *)packet)->addr = ((OrderingTag *)((scratch->dataC0 << 2) + (u32)scratch->data20))->addr;
                                ((OrderingTag *)((scratch->dataC0 << 2) + (u32)scratch->data20))->addr = (u32)packet;
                            }
                            packet += 0x28;
                        }
                    }
                }
                if (((s8) quad[0]) < 0) {
                    break;
                }
                quad += 0xC;
            }
            index += 1;
        } while (index < (*((s16 *) (((u8 *) sprite) + 2))));

    }
    return packet;
}
