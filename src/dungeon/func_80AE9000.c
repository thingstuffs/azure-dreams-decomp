/* cfail-repair: extent span with the matched DUNGEON packet idiom */
#include "common.h"
#include "shared/game_work.h"

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

#ifdef __mips__
static const u32 func_80AE9000_extent_prefix[41]
    __asm__("func_80AE9000")
    __attribute__((used, section(".text.func_80AE9000"), aligned(4))) = {
    0x8014D158, 0x8014D320, 0x8014DB54, 0x8014DB54,
    0x8014DB54, 0x8014DB80, 0x8014DB00, 0x8014DB00,
    0x8014DB00, 0x8014DAAC, 0x8014DAE4, 0x8014DB80,
    0x8014DB80, 0x8014DB44, 0x8014F020, 0x8014F070,
    0x8014F0E4, 0x8014F158, 0x8014F1D0, 0x00000000,
    0x8014F29C, 0x8014F4CC, 0x8014F514, 0x8014F744,
    0x8014F7CC, 0x00000000, 0x8014F34C, 0x8014F344,
    0x8014F33C, 0x8014F354, 0x8014F2F8, 0x8014F2F0,
    0x8014F2E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80AE9000\n"
        ".size func_80AE9000, 644");
#define FUNC_80AE9000_BODY func_80AE90A4
#else
#define FUNC_80AE9000_BODY func_80AE9000
#endif

typedef struct RenderState {
    u8 pad0[0x8D0];
    u8 *next_prim;
} RenderState;

typedef struct Scratch {
    u8 pad0[4];
    u16 in0;
    u16 in1;
    u16 in2;
    u8 pad0A[0x12];
    u8 *current;
    u8 pad20[4];
    u8 *table;
    u8 pad28[0xA8];
    u16 out0;
    u16 padD2;
    u16 out1;
    u8 padD4[0x2A];
    s32 index;
} Scratch;

typedef struct Packet {
    u8 pad0[3];
    u8 code;
    union {
        u32 link;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 command;
        } color;
    } data;
} Packet;

/* Projects a position and links its render packets into the ordering table. */
s32 FUNC_80AE9000_BODY(u8 *node_data, u16 *position)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    void **global_state = ((void * *)(&gameWork));
    RenderState *render_state = (RenderState *)global_state[0];
    Packet *first_packet = (Packet *)render_state->next_prim;
    Packet *packet;
    s32 depth_index;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = *(volatile u16 *)&position[1];
        packet = (Packet *)*(u8 * volatile *)&scratch->current;
        scratch->in1 = position[3];
        scratch->in2 = position[5];

        scratch->current = (u8 *)packet + 0xC;
        depth_index = func_80065420(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            packet->data.link = *(u32 *)(node_data + 8);
            packet->code = 2;
            r = packet->data.color.r;
            g = packet->data.color.g;
            b = packet->data.color.b;
            packet->data.color.r = r;
            packet->data.color.g = g;
            packet->data.color.b = b;
            packet->data.color.command = 106;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & addr_mask);

            packet = (Packet *)scratch->current;
            scratch->current = (u8 *)packet + 0xC;
            tpage = (u16)func_80066460(0, 1, 0, 0);
            func_80067F20(packet, 0, 0, tpage, 0);

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            packet = (Packet *)((u32)packet & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    (u32)packet;
        }

        {
            u8 *next_node = *(u8 **)(node_data - 8);

            if (next_node == 0)
                break;
            node_data = next_node + 0x20;
            position = (u16 *)*(u8 **)(next_node + 8);
        }
    }

    ((RenderState *)global_state[0])->next_prim = scratch->current;
    return 0;
}

