#include "common.h"
#include "shared/game_work.h"

typedef struct RenderState {
    u8 pad0[0x8D0];
    u8 *next_prim;
} RenderState;

typedef struct GlobalState {
    RenderState *render_state;
    u8 pad04[0x20];
} GlobalState;

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

typedef struct Input {
    u8 pad0[2];
    u16 in0;
    u8 pad4[2];
    u16 in1;
    u8 pad8[2];
    u16 in2;
} Input;

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

/* Builds and links rendering packets for a chain of positioned entries. */
s32 func_8015E884(u8 *entry, u16 *position)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    void **globals = ((void * *)(&gameWork));
    RenderState *render_state = (RenderState *)globals[0];
    Packet *first_packet = (Packet *)render_state->next_prim;
    Packet *packet;
    s32 ot_index;
    u32 address_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = *(volatile u16 *)&position[1];
        packet = (Packet *)*(u8 * volatile *)&scratch->current;
        scratch->in1 = position[3];
        scratch->in2 = position[5];

        scratch->current = (u8 *)packet + 0xC;
        ot_index = func_80065420(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = ot_index;

        if ((u32)ot_index < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            packet->data.link = *(u32 *)(entry + 8);
            packet->code = 2;
            r = packet->data.color.r;
            g = packet->data.color.g;
            b = packet->data.color.b;
            packet->data.color.r = r;
            packet->data.color.g = g;
            packet->data.color.b = b;
            packet->data.color.command = 106;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & address_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & address_mask);

            packet = (Packet *)scratch->current;
            scratch->current = (u8 *)packet + 0xC;
            tpage = (u16)func_80066460(0, 1, 0, 0);
            func_80067F20(packet, 0, 0, tpage, 0);

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & address_mask);
            packet = (Packet *)((u32)packet & address_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    (u32)packet;
        }

        {
            u8 *next_entry = *(u8 **)(entry - 8);

            if (next_entry == 0)
                break;
            entry = next_entry + 0x20;
            position = (u16 *)*(u8 **)(next_entry + 8);
        }
    }

    ((RenderState *)globals[0])->next_prim = scratch->current;
    return 0;
}
