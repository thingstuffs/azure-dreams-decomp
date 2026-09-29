/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);


#ifdef __mips__
static const u32 prefix_words[] __asm__("func_80AD7000")
    __attribute__((section(".text.func_80AD7000"), aligned(4))) = {
    0x8015F158, 0x8015F320, 0x8015FB54, 0x8015FB54,
    0x8015FB54, 0x8015FB80, 0x8015FB00, 0x8015FB00,
    0x8015FB00, 0x8015FAAC, 0x8015FAE4, 0x8015FB80,
    0x8015FB80, 0x8015FB44, 0x80161020, 0x80161070,
    0x801610E4, 0x80161158, 0x801611D0, 0x00000000,
    0x8016129C, 0x801614CC, 0x80161514, 0x80161744,
    0x801617CC, 0x00000000, 0x8016134C, 0x80161344,
    0x8016133C, 0x80161354, 0x801612F8, 0x801612F0,
    0x801612E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80AD7000\n"
        ".size func_80AD7000, 644");
#define BODY_NAME func_80AD70A4
#else
#define BODY_NAME func_80AD7000
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

/* Projects an object's point and queues its pixel and draw-state primitives in the ordering table. */
s32 BODY_NAME(u8 *node_data, u16 *position)
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

