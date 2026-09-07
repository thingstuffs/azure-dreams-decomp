#include "common.h"

typedef struct S_8008896C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_8008896C_0;   /* line in func_8008896C */

typedef struct S_8008896C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_8008896C_1;   /* arg1 in func_8008896C */

typedef struct S_8008896C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8008896C_2_pre;   /* the 0x8 bytes before arg0 in func_8008896C, addressed as arg0[-1] */

typedef struct S_8008896C_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_8008896C_3;   /* next in func_8008896C */



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
            ((S_8008896C_0 *)line)->unk_04 = 0x808080;
            func_80066758(line);
            func_80066668(line, 1);
            ((S_8008896C_0 *)line)->unk_08 = inner << 8;
            ((S_8008896C_0 *)line)->unk_0A = base_y - ((S_8008896C_1 *)arg1)->unk_06;
            ((S_8008896C_0 *)line)->unk_10 = 0x100;
            ((S_8008896C_0 *)line)->unk_12 = 0x100;
            ((S_8008896C_0 *)line)->unk_0C = 0;
            ((S_8008896C_0 *)line)->unk_0E = func_8006649C(0, 0x1F0);
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

        next = ((S_8008896C_2_pre *)arg0)[-1].unk_00;
        if (next == 0) {
            return 0;
        }
        arg0 = next + 0x20;
        arg1 = ((S_8008896C_3 *)next)->unk_08;
    }
}
