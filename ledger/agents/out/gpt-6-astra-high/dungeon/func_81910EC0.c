#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define KEEP_MEMDEP_NV_EXPR(v, s, m) ({ ASM_KEEP_MEMDEP_NV(v, s, m); 0; })
/* Same address as D_80083160 (0x80083178 - 0x18); spelled off D_80083178 so the
   %hi page is one CONST rtx shared with the pin below.  Links to identical words. */
#define GFX_ROOT_SLOT (((u8 *)&D_80083178) - 0x18)
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))
#define VS32_AT(p, o) (*(volatile s32 *)((u8 *)(p) + (o)))

typedef struct GfxContext {
    u8 pad0[0x8D0];
    u8 *cursor;
} GfxContext;

extern GfxContext *D_80083160[3];

extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

/* Build and enqueue five translucent quads between interpolated points. */
void func_81910EC0(void *shape_data, void *position, s16 scale_num, s16 scale_den)
{
    u8 *page_scratch;
    u8 *shape = shape_data;
    u8 *gfx = (KEEP_MEMDEP_NV_EXPR(shape, page_scratch, *(u8 **)GFX_ROOT_SLOT),
                  *(u8 **)GFX_ROOT_SLOT);
    s32 edge = 0;
    s32 scale = scale_num;
    s32 divisor = scale_den;
    s32 interpolate = scale < divisor;
    register u32 addr_mask ASM_REG("$20") = 0x00FFFFFF;   /* MATCH pin: load-bearing for the whole function shape */
    u32 length_mask = 0xFF000000;
    u8 *start_point = shape;
    u8 *scratchpad = (u8 *)0x1F800000;
    u8 *gfx_slot;

    PTR_AT(scratchpad, 0x18) = gfx + 0xB0;
    gfx_slot = GFX_ROOT_SLOT;
    do {
        GfxContext **gfx_pool = (GfxContext **)gfx_slot;
        u8 *packet;
        u8 *end_point;
        s32 coord_delta;
        u16 coord;
        u16 vertex_y;
        u32 depth;

        packet = (*gfx_pool)->cursor;
        (*gfx_pool)->cursor = packet + 0x24;

        U8_AT(packet, 3) = 8;
        U8_AT(packet, 7) = 0x3A;
        U8_AT(packet, 4) = U8_AT(shape, 0x40);
        U8_AT(packet, 5) = U8_AT(shape, 0x41);
        U8_AT(packet, 6) = U8_AT(shape, 0x42);
        U8_AT(packet, 0xC) = U8_AT(shape, 0x40);
        U8_AT(packet, 0xD) = U8_AT(shape, 0x41);
        U8_AT(packet, 0xE) = U8_AT(shape, 0x42);
        U8_AT(packet, 0x14) = U8_AT(shape, 0x40);
        U8_AT(packet, 0x15) = U8_AT(shape, 0x41);
        U8_AT(packet, 0x16) = U8_AT(shape, 0x42);
        U8_AT(packet, 0x1C) = U8_AT(shape, 0x40);
        U8_AT(packet, 0x1D) = U8_AT(shape, 0x41);
        U8_AT(packet, 0x1E) = U8_AT(shape, 0x42);

        end_point = shape + (((edge + 2) % 5) * 4);
        {
            u16 start_x = VU16_AT(start_point, 0x1A);

            U16_AT(scratchpad, 0x74) = start_x;
            U16_AT(scratchpad, 0x64) = start_x;
        }

        coord_delta = S32_AT(end_point, 0x18) - VS32_AT(start_point, 0x18);
        S32_AT(scratchpad, 0x108) = coord_delta;
        if (interpolate) {
            S32_AT(scratchpad, 0x108) = (coord_delta / divisor) * scale;
        }

        coord = VU16_AT(start_point, 0x1A) + U16_AT(scratchpad, 0x10A);
        U16_AT(scratchpad, 0x7C) = coord;
        U16_AT(scratchpad, 0x6C) = coord;

        vertex_y = VU16_AT(start_point, 0x2E);
        U16_AT(scratchpad, 0x76) = vertex_y;
        U16_AT(scratchpad, 0x66) = vertex_y;

        coord_delta = S32_AT(end_point, 0x2C) - VS32_AT(start_point, 0x2C);
        S32_AT(scratchpad, 0x10C) = coord_delta;
        if (interpolate) {
            S32_AT(scratchpad, 0x10C) = (coord_delta / divisor) * scale;
        }

        vertex_y = VU16_AT(start_point, 0x2E) + U16_AT(scratchpad, 0x10E);
        U16_AT(scratchpad, 0x7E) = vertex_y;
        U16_AT(scratchpad, 0x6E) = vertex_y;

        coord = U16_AT(position, 0xA) - U16_AT(shape, 0x10);
        U16_AT(scratchpad, 0x70) = coord;
        U16_AT(scratchpad, 0x68) = coord;

        coord = U16_AT(position, 0xA);
        U16_AT(scratchpad, 0x78) = coord;
        U16_AT(scratchpad, 0x80) = coord;

        U32_AT(scratchpad, 0xB4) = func_80065590(
            scratchpad + 0x64, scratchpad + 0x6C,
            scratchpad + 0x74, scratchpad + 0x7C,
            scratchpad + 0xD8, scratchpad + 0xDC,
            scratchpad + 0xE0, scratchpad + 0xE4,
            scratchpad + 0x84, scratchpad + 0x88);

        U16_AT(packet, 8) = U16_AT(scratchpad, 0xD8);
        U16_AT(packet, 0xA) = U16_AT(scratchpad, 0xDA);
        U16_AT(packet, 0x10) = U16_AT(scratchpad, 0xDC);
        U16_AT(packet, 0x12) = U16_AT(scratchpad, 0xDE);
        U16_AT(packet, 0x18) = U16_AT(scratchpad, 0xE0);
        U16_AT(packet, 0x1A) = U16_AT(scratchpad, 0xE2);
        U16_AT(packet, 0x20) = U16_AT(scratchpad, 0xE4);
        U16_AT(packet, 0x22) = U16_AT(scratchpad, 0xE6);

        depth = U32_AT(scratchpad, 0xB4);
        if (depth < 0x1E0) {
            U32_AT(packet, 0) = (U32_AT(packet, 0) & length_mask) |
                (*(u32 *)(PTR_AT(scratchpad, 0x18) + depth * 4) & addr_mask);
            *(u32 *)(PTR_AT(scratchpad, 0x18) + U32_AT(scratchpad, 0xB4) * 4) =
                (*(u32 *)(PTR_AT(scratchpad, 0x18) + U32_AT(scratchpad, 0xB4) * 4) & length_mask) |
                ((u32)packet & addr_mask);

            gfx_pool = (GfxContext **)gfx_slot;
            packet = (*gfx_pool)->cursor;
            (*gfx_pool)->cursor = packet + 0xC;
            func_80067F20(packet, 0, 0,
                (u16)func_80066460(0, S16_AT(shape, 0x12), 0, 0), 0);

            U32_AT(packet, 0) = (U32_AT(packet, 0) & length_mask) |
                (*(u32 *)(PTR_AT(scratchpad, 0x18) + U32_AT(scratchpad, 0xB4) * 4) & addr_mask);
            {
                u32 packet_depth = U32_AT(scratchpad, 0xB4);

                packet = (u8 *)((u32)packet & addr_mask);
                *(u32 *)(PTR_AT(scratchpad, 0x18) + packet_depth * 4) =
                    (*(u32 *)(PTR_AT(scratchpad, 0x18) + packet_depth * 4) & length_mask) |
                    (u32)packet;
            }
        }

        edge++;
        start_point += 4;
    } while (edge < 5);
}
