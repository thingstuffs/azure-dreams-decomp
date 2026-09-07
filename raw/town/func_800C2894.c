#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct PacketTag { unsigned addr : 24; unsigned len : 8; u8 r0; u8 g0; u8 b0; u8 code; } PacketTag;
#define setaddr(packet, address) (((PacketTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) (setaddr((primitive), getaddr(ordering_table)), setaddr((ordering_table), (primitive)))
typedef union PackedColor { u32 word; struct { u8 r; u8 g; u8 b; u8 code; } channel; } PackedColor;
typedef struct LineG2 { u32 tag; PackedColor color0; s16 x0; s16 y0; PackedColor color1; s16 x1; s16 y1; } LineG2;
typedef struct RenderState { u8 pad0[0x8D0]; u8 *next_prim; } RenderState;
typedef struct TownState { RenderState *render_state; } TownState;
static __inline__ void init_line_colors(LineG2 *line, u32 color0, u32 color1) { line->color0.word = color0; line->color1.word = color1; }
extern TownState D_80083160;
s32 func_80065420(void *, void *, void *, void *);
s32 func_80066460(s32, s32, s32, s32);
void func_80066640(LineG2 *, s32);
void func_800667D0(LineG2 *);
void func_80067F20(void *, s32, s32, s32, s32);

s32 func_800BFFF4(u8 *node)
{
    u16 coordinates[3]; s32 result1; s32 result2; TownState *global; RenderState *root;
    LineG2 *object; u8 *new_object; u8 *next; s16 first; s32 average; s32 offset; s32 zero;
    global = &D_80083160;
    do {
        object = (LineG2 *)global->render_state->next_prim;
        global->render_state->next_prim = (u8 *)object + 0x14;
        init_line_colors(object, 0x202020, 0); func_800667D0(object); func_80066640(object, 1);
        coordinates[0] = FIELD(node, u16, 0x1E); coordinates[1] = FIELD(node, u16, 0x22); coordinates[2] = FIELD(node, u16, 0x26);
        first = func_80065420(coordinates, (u8 *)object + 8, &result1, &result2);
        average = (first + func_80065420(node + 0xC, (u8 *)object + 0x10, &result1, &result2)) >> 1;
        zero = 0;
        if ((u16)average < 0x1E0U) {
            offset = (s16)average * 4;
            addPrim((u8 *)(offset + (s32)global->render_state) + 0xB0, object);
            root = global->render_state; new_object = root->next_prim; root->next_prim = new_object + 0xC;
            func_80067F20(new_object, 0, 0, func_80066460(zero, 1, zero, zero) & 0xFFFF, 0);
            addPrim((u8 *)(offset + (s32)global->render_state) + 0xB0, new_object);
        }
        next = FIELD(node, u8 *, -8);
        if (next != 0) {
            node = next + 0x20;
            continue;
        }
        break;
    } while (1);
    return 0;
}
