#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"


















#define SCRATCH ((Bank56_819611CC_Scratch *)0x1F800000)

/* Project a textured quad and queue it with semitransparency when its depth is in range. */
s32 dungeonProjectAndQueueSemitransparentQuad(Quad *quad, s32 unused, Material *material)
{
    Bank56_819611CC_Scratch *scratch;
    Bank56_819611CC_PolyFT4 *packet;
    Texture *texture;
    Bank56_819611CC_PolyFT4 *draw_packet;
    QuadLink *link;
    u32 depth;
    RenderState **slot;
    u32 xy3;
    u16 z0;
    u16 z;
    u16 z3;

    slot = ((RenderState * *)(&gameWork));
    packet = (Bank56_819611CC_PolyFT4 *)(*slot)->packet;
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
