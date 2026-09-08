#include "common.h"

typedef struct S_8002415C_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8002415C_0_pre;   /* the 0x8 bytes before node in func_8002415C, addressed as node[-1] */

typedef struct S_8002415C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0xC];
    u16 unk_24;
} S_8002415C_0;   /* node in func_8002415C */

typedef struct S_8002415C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8002415C_1;   /* record in func_8002415C */



typedef struct PacketTag {
    unsigned addr : 24;
    unsigned len : 8;
} PacketTag;

#define setaddr(packet, address) (((PacketTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
    (setaddr((primitive), getaddr(ordering_table)), \
     setaddr((ordering_table), (primitive)))

typedef struct RenderState {
    u8 pad0[0x8D0];
    u8 *next_prim;
} RenderState;

typedef struct TownState {
    RenderState *render_state;
} TownState;

extern TownState D_80083160;
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_800667BC(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

/* Queue enabled nodes as line primitives with draw modes, sorted by average depth. */
s32 func_8002415C(u8 *node)
{
    s32 coords[2];
    s32 *second_coord;
    TownState *town_state;
    RenderState *render_state;
    u8 *line_prim;
    u8 *draw_mode_prim;
    u8 *next_link;
    s16 first_depth;
    s32 avg_depth;
    s32 ot_offset;

    town_state = &D_80083160;
    second_coord = &coords[1];
    for (;;) {
        if (!(((S_8002415C_0 *)node)->unk_24 & 1)) {
            render_state = town_state->render_state;
            line_prim = render_state->next_prim;
            render_state->next_prim = line_prim + 0x10;
            ((S_8002415C_1 *)line_prim)->unk_04 = ((S_8002415C_0 *)node)->unk_14;
            func_800667BC(line_prim);
            func_80066640(line_prim, 1);
            first_depth = func_80065420(node + 4, line_prim + 8,
                                  &coords[0], second_coord);
            avg_depth = (first_depth + func_80065420(node + 0xC, line_prim + 0xC,
                                             &coords[0], second_coord)) >> 1;
            if ((u16)avg_depth < 0x1E0U) {
                ot_offset = (s16)avg_depth * 4;
                addPrim((u8 *)(ot_offset + (s32)town_state->render_state) + 0xB0,
                        line_prim);

                render_state = town_state->render_state;
                draw_mode_prim = render_state->next_prim;
                render_state->next_prim = draw_mode_prim + 0xC;
                func_80067F20(draw_mode_prim, 0, 0,
                    func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
                addPrim((u8 *)(ot_offset + (s32)town_state->render_state) + 0xB0,
                        draw_mode_prim);
            }
        }

        next_link = ((S_8002415C_0_pre *)node)[-1].unk_00;
        if (next_link != 0) {
            node = next_link + 0x20;
            continue;
        }
        break;
    }
    return 0;
}
