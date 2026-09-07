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

s32 func_8014C884(u8 *arg0, u16 *arg1)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    void **global = D_80083160;
    RenderState *ctx = (RenderState *)global[0];
    Packet *initial_obj = (Packet *)ctx->next_prim;
    Packet *obj;
    s32 index;
    u32 mask_lo = 0x00FFFFFF;
    u32 mask_hi = 0xFF000000;

    scratch->table = (u8 *)ctx + 0xB0;
    scratch->current = (u8 *)initial_obj;
    for (;;) {
        scratch->in0 = *(volatile u16 *)&arg1[1];
        obj = (Packet *)*(u8 * volatile *)&scratch->current;
        scratch->in1 = arg1[3];
        scratch->in2 = arg1[5];

        scratch->current = (u8 *)obj + 0xC;
        index = func_80065420(&scratch->in0, (u8 *)obj + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = index;

        if ((u32)index < 480U) {
        u16 tpage;
        register s32 call_zero ASM_REG("$4") = 0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        register s32 call_one ASM_REG("$5") = 1;   /* MATCH pin: retail schedule: same instructions, different order without it */
        u32 link;
        u32 color_r;
        register u32 color_g ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register u32 color_b ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register u32 code_command ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

        link = *(u32 *)(arg0 + 8);
        obj->data.link = link;
        code_command = 2;
        obj->code = code_command;
        code_command = 106;
        color_r = obj->data.color.r;
        color_g = obj->data.color.g;
        color_b = obj->data.color.b;
        ASM_KEEP(color_g);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ASM_KEEP(color_b);   /* MATCH pin: retail register colouring depends on it */
        obj->data.color.command = code_command;

        *(u32 *)obj = (*(u32 *)obj & mask_hi) |
                      (((u32 *)scratch->table)[scratch->index] & mask_lo);
        ((u32 *)scratch->table)[scratch->index] =
                                (((u32 *)scratch->table)[scratch->index] & mask_hi) |
                                ((u32)obj & mask_lo);

        obj = (Packet *)scratch->current;
        scratch->current = (u8 *)obj + 0xC;
        tpage = (u16)func_80066460(call_zero, call_one, call_zero, call_zero);
        func_80067F20(obj, 0, 0, tpage, 0);

        *(u32 *)obj = (*(u32 *)obj & mask_hi) |
                      (((u32 *)scratch->table)[scratch->index] & mask_lo);
        obj = (Packet *)((u32)obj & mask_lo);
        ((u32 *)scratch->table)[scratch->index] =
                                (((u32 *)scratch->table)[scratch->index] & mask_hi) |
                                (u32)obj;
        }

        {
            u8 *next = *(u8 **)(arg0 - 8);

            if (next == 0)
                break;
            arg0 = next + 0x20;
            arg1 = (u16 *)*(u8 **)(next + 8);
        }
    }

    ((RenderState *)global[0])->next_prim = scratch->current;
    return 0;
}
