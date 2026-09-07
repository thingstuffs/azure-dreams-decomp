#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct PacketTag {
    unsigned addr : 24;
    unsigned len : 8;
} PacketTag;

#ifdef NON_MATCHING
#define PTR32(address) ((u32)(unsigned long)(address))
#else
#define PTR32(address) ((u32)(address))
#endif
#define setaddr(packet, address) (((PacketTag *)(packet))->addr = PTR32(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
    (setaddr((primitive), getaddr(ordering_table)), \
     setaddr((ordering_table), (primitive)))

typedef struct RenderState {
    u8 pad0[0x82C];
    u32 ordering_table;
    u8 pad830[0xA0];
    u8 *next_prim;
} RenderState;

typedef struct MainState {
    RenderState *render_state;
} MainState;

extern MainState D_80083160;

extern s32 func_80066460(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s16 func_8006649C(s32 arg0, s32 arg1);
extern void func_80066668(void *arg0, s32 arg1);
extern void func_80066758(void *arg0);
extern void func_80067F20(void *arg0, s32 arg1, s32 arg2, u16 arg3, s32 arg4);

s32 func_8008896C(u8 *arg0, u8 *arg1)
{
    MainState *global;
    u8 *line;
    u8 *primitive;
    u8 *next;
    s32 outer;
    s32 inner;
    s32 vertical;
    s32 color;
    s32 base_y;

    global = &D_80083160;
    for (;;) {
        outer = 0;
        do {
        inner = 1;
        base_y = outer << 8;
        color = 0x280;
        do {
            line = global->render_state->next_prim;
            global->render_state->next_prim = line + 0x14;
            FIELD(line, s32, 4) = 0x808080;
            func_80066758(line);
            func_80066668(line, 1);
            FIELD(line, s16, 8) = inner << 8;
            FIELD(line, s16, 0xA) = base_y - FIELD(arg1, u16, 6);
            FIELD(line, s16, 0x10) = 0x100;
            FIELD(line, s16, 0x12) = 0x100;
            FIELD(line, s16, 0xC) = 0;
            FIELD(line, s16, 0xE) = func_8006649C(0, 0x1F0);
            addPrim(&global->render_state->ordering_table, line);

            primitive = global->render_state->next_prim;
            global->render_state->next_prim = primitive + 0xC;
            vertical = func_80066460(1, 0, color, base_y);
            func_80067F20(primitive, 0, 0, vertical & 0xFFFF, 0);
            inner--;
            addPrim(&global->render_state->ordering_table, primitive);
            color -= 0x80;
        } while (inner >= 0);
        outer++;
        } while (outer < 2);

        next = FIELD(arg0, u8 *, -8);
        if (next == 0) {
            return 0;
        }
        arg0 = next + 0x20;
        arg1 = FIELD(next, u8 *, 8);
    }
}
