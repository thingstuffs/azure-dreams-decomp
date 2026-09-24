#include "common.h"

typedef struct QuadVertex {
    u32 xy;
    u16 z;
    u16 pad;
} QuadVertex;

typedef struct Quad {
    u8 pad_00[0x10];
    QuadVertex v[4];
} Quad;

typedef struct QuadLink {
    u8 pad_00[0xC];
    struct Material *material;
    u8 pad_10[0x10];
    Quad quad;
} QuadLink;

typedef struct Scratch {
    u8 pad_00[0x20];
    u32 ot_base;
    u8 pad_24[0x4C];
    QuadVertex v[4];
    s32 out_a;
    s32 out_b;
    u8 pad_98[0x28];
    u32 depth;
} Scratch;

typedef struct PolyFT4 {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} PolyFT4;

typedef struct Texture {
    u8 pad_00[0x4];
    u16 tpage;
    u8 pad_06[0x2];
    u8 u, v, w, h;
} Texture;

typedef struct Material {
    u8 pad_00[0x8];
    Texture *texture;
    u32 color;
} Material;

typedef struct RenderState {
    u8 pad_00[0x8D0];
    u8 *packet;
} RenderState;

extern RenderState *D_80083160[];
extern s32 func_800654B0();
extern s32 func_8006658C();
extern s32 func_800666F4();

#define SCRATCH ((Scratch *)0x1F800000)

/* Project a textured quad and queue it with semitransparency when its depth is in range. */
s32 func_819611CC(Quad *quad, s32 unused, Material *material)
{
    Scratch *scratch;
    PolyFT4 *packet;
    Texture *texture;
    PolyFT4 *draw_packet;
    QuadLink *link;
    u32 depth;
    RenderState **slot;
    u32 xy3;
    u16 z0;
    u16 z;
    u16 z3;

    slot = D_80083160;
    packet = (PolyFT4 *)(*slot)->packet;
    scratch = SCRATCH;
    scratch->ot_base = (u32)*slot + 0xB0;
    for (;;) {
        scratch->v[0].xy = quad->v[0].xy;
        scratch->v[1].xy = quad->v[1].xy;
        scratch->v[2].xy = quad->v[2].xy;
        z0 = quad->v[0].z;
        texture = material->texture;
        xy3 = quad->v[3].xy;
        scratch->v[0].z = z0;
        z = quad->v[1].z;
        scratch->v[1].z = z;
        z = quad->v[2].z;
        scratch->v[3].xy = xy3;
        scratch->v[2].z = z;
        z3 = quad->v[3].z;
        scratch->v[3].z = z3;
        depth = func_800654B0(&scratch->v[0], &scratch->v[1], &scratch->v[2], &scratch->v[3],
                              &packet->x0, &packet->x1, &packet->x2, &packet->x3,
                              &scratch->out_a, &scratch->out_b) - 8;
        scratch->depth = depth;
        if (depth < 480) {
            packet->u0 = packet->u2 = texture->u;
            packet->u1 = packet->u3 = texture->u + texture->w;
            packet->v0 = packet->v1 = texture->v;
            packet->v2 = packet->v3 = texture->v + texture->h;
            packet->tpage = texture->tpage;
            *(u32 *)&packet->r0 = material->color;
            func_800666F4(packet);
            draw_packet = packet;
            packet->code |= 2;
            packet++;
            func_8006658C(scratch->ot_base + (scratch->depth << 2), draw_packet);
        }
        link = ((QuadLink **)quad)[-2];
        if (link == 0) {
            break;
        }
        quad = &link->quad;
        material = link->material;
    }
    (*slot)->packet = (u8 *)packet;
    return 0;
}
