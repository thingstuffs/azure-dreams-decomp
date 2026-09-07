#include "common.h"

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
            volatile u8 r;
            volatile u8 g;
            volatile u8 b;
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

extern void *D_80083160[3];
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

/* Builds and links render packets for a list of positioned entries. */
s32 func_8016A884(u8 *entry_data, u16 *coords)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    void **globals = D_80083160;
    RenderState *render_state = (RenderState *)globals[0];
    Packet *first_packet = (Packet *)render_state->next_prim;
    Packet *packet;
    s32 depth_index;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = *(volatile u16 *)&coords[1];
        packet = (Packet *)*(u8 * volatile *)&scratch->current;
        scratch->in1 = coords[3];
        scratch->in2 = coords[5];

        scratch->current = (u8 *)packet + 0xC;
        depth_index = func_80065420(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            register s32 call_zero ASM_REG("$4") = 0;   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 call_one ASM_REG("$5") = 1;   /* MATCH pin: retail schedule: same instructions, different order without it */
            u32 packed_color;
            u32 color_r;
            register u32 color_g ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
            register u32 color_b ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
            register u32 code_command ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

            packed_color = *(u32 *)(entry_data + 8);
            packet->data.link = packed_color;
            code_command = 2;
            packet->code = code_command;
            code_command = 106;
            color_r = packet->data.color.r;
            color_g = packet->data.color.g;
            color_b = packet->data.color.b;
            ASM_KEEP(color_g);   /* MATCH pin: keeps a statement from moving across a call/branch */
            ASM_KEEP(color_b);   /* MATCH pin: retail register colouring depends on it */
            packet->data.color.command = code_command;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & addr_mask);

            packet = (Packet *)scratch->current;
            scratch->current = (u8 *)packet + 0xC;
            tpage = (u16)func_80066460(call_zero, call_one, call_zero, call_zero);
            func_80067F20(packet, 0, 0, tpage, 0);

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            packet = (Packet *)((u32)packet & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    (u32)packet;
        }

        {
            u8 *next_entry = *(u8 **)(entry_data - 8);

            if (next_entry == 0)
                break;
            entry_data = next_entry + 0x20;
            coords = (u16 *)*(u8 **)(next_entry + 8);
        }
    }

    ((RenderState *)globals[0])->next_prim = scratch->current;
    return 0;
}
