#include "modules/dungeon_ovl_1930844.h"

void dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(u8 *shape, void *position, s16 scale_num, s16 scale_den)
{
    u8 *gfx_slot = ovl_1930844_81910EC0_GFX_ROOT_SLOT;
    u8 *gfx = *(u8 **)gfx_slot;
    s32 edge = 0;
    s32 scale = scale_num;
    s32 divisor = scale_den;
    s32 interpolate = scale < divisor;
    u8 *scratchpad = (u8 *)0x1F800000;

    ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) = gfx + 0xB0;
    do {
        GpuContext **gfx_pool = (GpuContext **)gfx_slot;
        u8 *start_point = shape + edge * 4;
        u8 *packet;
        u8 *end_point;
        s32 coord_delta;
        u16 coord;
        u16 vertex_y;
        u32 depth;

        packet = (*gfx_pool)->packetCursor;
        (*gfx_pool)->packetCursor = packet + 0x24;

        ovl_1930844_81910EC0_U8_AT(packet, 3) = 8;
        ovl_1930844_81910EC0_U8_AT(packet, 7) = 0x3A;
        ovl_1930844_81910EC0_U8_AT(packet, 4) = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        ovl_1930844_81910EC0_U8_AT(packet, 5) = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        ovl_1930844_81910EC0_U8_AT(packet, 6) = ovl_1930844_81910EC0_U8_AT(shape, 0x42);
        ovl_1930844_81910EC0_U8_AT(packet, 0xC) = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        ovl_1930844_81910EC0_U8_AT(packet, 0xD) = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        ovl_1930844_81910EC0_U8_AT(packet, 0xE) = ovl_1930844_81910EC0_U8_AT(shape, 0x42);
        ovl_1930844_81910EC0_U8_AT(packet, 0x14) = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        ovl_1930844_81910EC0_U8_AT(packet, 0x15) = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        ovl_1930844_81910EC0_U8_AT(packet, 0x16) = ovl_1930844_81910EC0_U8_AT(shape, 0x42);
        ovl_1930844_81910EC0_U8_AT(packet, 0x1C) = ovl_1930844_81910EC0_U8_AT(shape, 0x40);
        ovl_1930844_81910EC0_U8_AT(packet, 0x1D) = ovl_1930844_81910EC0_U8_AT(shape, 0x41);
        ovl_1930844_81910EC0_U8_AT(packet, 0x1E) = ovl_1930844_81910EC0_U8_AT(shape, 0x42);

        end_point = shape + (((edge + 2) % 5) * 4);
        {
            u16 start_x = ovl_1930844_81910EC0_U16_AT(start_point, 0x1A);

            ovl_1930844_81910EC0_U16_AT(scratchpad, 0x74) = start_x;
            ovl_1930844_81910EC0_U16_AT(scratchpad, 0x64) = start_x;
        }

        coord_delta = ovl_1930844_81910EC0_S32_AT(end_point, 0x18) - ovl_1930844_81910EC0_S32_AT(start_point, 0x18);
        ovl_1930844_81910EC0_S32_AT(scratchpad, 0x108) = coord_delta;
        if (interpolate) {
            ovl_1930844_81910EC0_S32_AT(scratchpad, 0x108) = (coord_delta / divisor) * scale;
        }

        coord = ovl_1930844_81910EC0_U16_AT(start_point, 0x1A) + ovl_1930844_81910EC0_U16_AT(scratchpad, 0x10A);
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x7C) = coord;
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x6C) = coord;

        vertex_y = ovl_1930844_81910EC0_U16_AT(start_point, 0x2E);
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x76) = vertex_y;
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x66) = vertex_y;

        coord_delta = ovl_1930844_81910EC0_S32_AT(end_point, 0x2C) - ovl_1930844_81910EC0_S32_AT(start_point, 0x2C);
        ovl_1930844_81910EC0_S32_AT(scratchpad, 0x10C) = coord_delta;
        if (interpolate) {
            ovl_1930844_81910EC0_S32_AT(scratchpad, 0x10C) = (coord_delta / divisor) * scale;
        }

        vertex_y = ovl_1930844_81910EC0_U16_AT(start_point, 0x2E) + ovl_1930844_81910EC0_U16_AT(scratchpad, 0x10E);
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x7E) = vertex_y;
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x6E) = vertex_y;

        coord = ovl_1930844_81910EC0_U16_AT(position, 0xA) - ovl_1930844_81910EC0_U16_AT(shape, 0x10);
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x70) = coord;
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x68) = coord;

        coord = ovl_1930844_81910EC0_U16_AT(position, 0xA);
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x78) = coord;
        ovl_1930844_81910EC0_U16_AT(scratchpad, 0x80) = coord;

        ovl_1930844_81910EC0_U32_AT(scratchpad, 0xB4) = func_80065590(
            scratchpad + 0x64, scratchpad + 0x6C,
            scratchpad + 0x74, scratchpad + 0x7C,
            scratchpad + 0xD8, scratchpad + 0xDC,
            scratchpad + 0xE0, scratchpad + 0xE4,
            scratchpad + 0x84, scratchpad + 0x88);

        ovl_1930844_81910EC0_U16_AT(packet, 8) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xD8);
        ovl_1930844_81910EC0_U16_AT(packet, 0xA) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xDA);
        ovl_1930844_81910EC0_U16_AT(packet, 0x10) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xDC);
        ovl_1930844_81910EC0_U16_AT(packet, 0x12) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xDE);
        ovl_1930844_81910EC0_U16_AT(packet, 0x18) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xE0);
        ovl_1930844_81910EC0_U16_AT(packet, 0x1A) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xE2);
        ovl_1930844_81910EC0_U16_AT(packet, 0x20) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xE4);
        ovl_1930844_81910EC0_U16_AT(packet, 0x22) = ovl_1930844_81910EC0_U16_AT(scratchpad, 0xE6);

        depth = ovl_1930844_81910EC0_U32_AT(scratchpad, 0xB4);
        if (depth < 0x1E0) {
            u32 addr_mask = 0x00FFFFFF;
            u32 length_mask = 0xFF000000;

            ((ovl_1930844_81910EC0_P_TAG *)packet)->addr = ((ovl_1930844_81910EC0_P_TAG *)(u32 *)(ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) + depth * 4))->addr;
            *(u32 *)(ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) + ovl_1930844_81910EC0_U32_AT(scratchpad, 0xB4) * 4) =
                (*(u32 *)(ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) + ovl_1930844_81910EC0_U32_AT(scratchpad, 0xB4) * 4) & length_mask) |
                ((u32)packet & addr_mask);

            gfx_pool = (GpuContext **)gfx_slot;
            packet = (*gfx_pool)->packetCursor;
            (*gfx_pool)->packetCursor = packet + 0xC;
            func_80067F20(packet, 0, 0,
                (u16)func_80066460(0, ovl_1930844_81910EC0_S16_AT(shape, 0x12), 0, 0), 0);

            ovl_1930844_81910EC0_U32_AT(packet, 0) = (ovl_1930844_81910EC0_U32_AT(packet, 0) & length_mask) |
                (*(u32 *)(ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) + ovl_1930844_81910EC0_U32_AT(scratchpad, 0xB4) * 4) & addr_mask);
            {
                u32 packet_depth = ovl_1930844_81910EC0_U32_AT(scratchpad, 0xB4);

                packet = (u8 *)((u32)packet & addr_mask);
                *(u32 *)(ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) + packet_depth * 4) =
                    (*(u32 *)(ovl_1930844_81910EC0_PTR_AT(scratchpad, 0x18) + packet_depth * 4) & length_mask) |
                    (u32)packet;
            }
        }

        edge++;
    } while (edge < 5);
}
