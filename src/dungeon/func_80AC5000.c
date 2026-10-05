#include "common.h"
#include "shared/game_work.h"

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

typedef void (*Callback)(void);

extern void func_80171158(void);
extern void func_80171320(void);
extern void func_80171B54(void);
extern void func_80171B80(void);
extern void func_80171B00(void);
extern void func_80171AAC(void);
extern void func_80171AE4(void);
extern void func_80171B44(void);
extern void func_80173020(void);
extern void func_80173070(void);
extern void func_801730E4(void);
extern void func_80173158(void);
extern void func_801731D0(void);
extern void func_8017329C(void);
extern void func_801734CC(void);
extern void func_80173514(void);
extern void func_80173744(void);
extern void func_801737CC(void);
extern void func_8017334C(void);
extern void func_80173344(void);
extern void func_8017333C(void);
extern void func_80173354(void);
extern void func_801732F8(void);
extern void func_801732F0(void);
extern void func_801732E8(void);

struct CallbackBlock {
    Callback callbacks[33];
    u32 vectors[8];
};

const struct CallbackBlock func_80AC5000 __attribute__((section(".text.func_80AC5000"))) = {
    {
        func_80171158, func_80171320, func_80171B54, func_80171B54,
        func_80171B54, func_80171B80, func_80171B00, func_80171B00,
        func_80171B00, func_80171AAC, func_80171AE4, func_80171B80,
        func_80171B80, func_80171B44, func_80173020, func_80173070,
        func_801730E4, func_80173158, func_801731D0, 0,
        func_8017329C, func_801734CC, func_80173514, func_80173744,
        func_801737CC, 0, func_8017334C, func_80173344,
        func_8017333C, func_80173354, func_801732F8, func_801732F0,
        func_801732E8
    },
    {
        0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
        0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001
    }
};

#ifdef __mips__
__asm__(".size func_80AC5000, 644");
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

/* Projects a point and queues a semitransparent pixel and its drawing mode. */
s32 func_80AC50A4(u8 *node_data, u16 *position)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    void **global_state = ((void * *)(&gameWork));
    RenderState *render_state = (RenderState *)global_state[0];
    Packet *first_packet = (Packet *)render_state->next_prim;
    Packet *packet;
    Packet *mode_packet;
    s32 depth_index;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = position[1];
        packet = (Packet *)scratch->current;
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

            mode_packet = (Packet *)scratch->current;
            scratch->current = (u8 *)mode_packet + 0xC;
            tpage = (u16)func_80066460(0, 1, 0, 0);
            func_80067F20(mode_packet, 0, 0, tpage, 0);

            *(u32 *)mode_packet = (*(u32 *)mode_packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            mode_packet = (Packet *)((u32)mode_packet & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    (u32)mode_packet;
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

