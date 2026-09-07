#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch800248EC;

typedef struct {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet800248EC;

extern u8 D_80083160[];
extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_80024944() __attribute__((noreturn));

s32 func_800248EC(void *arg0, void *arg1)
{
    register void *cur ASM_REG("$19") = arg0;
    register void *input ASM_REG("$8") = arg1;
    u8 *global = D_80083160;
    register u32 low_mask ASM_REG("$18") = 0x00FFFFFF;
    register u8 *ctx ASM_REG("$2") = *(u8 **)D_80083160;
    register u8 *initial_next ASM_REG("$3");
    register u32 high_mask ASM_REG("$20") = 0xFF000000;
    register Scratch800248EC *scratch ASM_REG("$17") =
        (Scratch800248EC *)0x1F800000;
    Packet800248EC *packet;
    Packet800248EC *packet2;
    register u8 *final_ctx ASM_REG("$4");
    s32 value;
    register void *next ASM_REG("$5");
    register s32 call_arg0 ASM_REG("$4");
    register s32 call_arg1 ASM_REG("$5");
    register s32 call_arg2 ASM_REG("$6");
    register u32 packet_code ASM_REG("$2");

    ASM_KEEP(cur);
    ASM_KEEP(input);
    ASM_KEEP(global);
    ASM_KEEP(low_mask);
    ASM_KEEP(high_mask);
    ASM_KEEP(scratch);
    initial_next = FIELD(ctx, u8 *, 0x8D0);
    scratch->ot = (u32 *)(ctx + 0xB0);
    scratch->cursor = initial_next;
    ASM_KEEP(initial_next);
    packet = *(Packet800248EC *volatile *)&scratch->cursor;
    scratch->x = FIELD(input, u16, 2);
    scratch->y = FIELD(input, u16, 6);
    scratch->z = FIELD(input, u16, 0xA);
    scratch->cursor = (u8 *)packet + 0xC;
    scratch->index = func_80065420(scratch, (u8 *)packet + 8,
                                  &scratch->xy, &scratch->depth);

    if (scratch->index < 0x1E0U) {
        FIELD(packet, u32, 4) = FIELD(cur, u32, 8);

        value = (s32)packet->r * FIELD(cur, s16, 0x32);
        if (value < 0) {
            value += 0x7F;
        }
        packet->r = value >> 7;

        value = (s32)packet->g * FIELD(cur, s16, 0x32);
        if (value < 0) {
            value += 0x7F;
        }
        packet->g = value >> 7;

        value = (s32)packet->b * FIELD(cur, s16, 0x32);
        if (value < 0) {
            value += 0x7F;
        }
        packet->b = value >> 7;

        call_arg0 = 0;
        call_arg1 = 1;
        FIELD(packet, u8, 3) = 2;
        ASM_KEEP(call_arg0);
        packet_code = 0x6A;
        ASM_KEEP(packet_code);
        call_arg2 = call_arg0;
        FIELD(packet, u8, 7) = packet_code;
        packet->tag = (packet->tag & high_mask) |
                      (scratch->ot[scratch->index] & low_mask);
        {
            u32 old_tag = scratch->ot[scratch->index];
            register u32 packet_mask ASM_REG("$2") =
                (u32)packet & low_mask;

            scratch->ot[scratch->index] =
                (old_tag & high_mask) | packet_mask;
            ASM_KEEP(packet_mask);
        }

        packet2 = (Packet800248EC *)scratch->cursor;
        scratch->cursor = (u8 *)packet2 + 0xC;
        value = func_80066460(call_arg0, call_arg1, call_arg2, call_arg0);
        func_80067F20(packet2, 0, 0, (u16)value, 0);

        packet2->tag = (packet2->tag & high_mask) |
                       (scratch->ot[scratch->index] & low_mask);
        scratch->ot[scratch->index] =
            (scratch->ot[scratch->index] & high_mask) |
            ((u32)packet2 & low_mask);
    }

    next = FIELD(cur, void *, -8);
    if (next != 0) {
        cur = (u8 *)next + 0x20;
        input = FIELD(next, void *, 8);
        ASM_KEEP(cur);
        ASM_KEEP(input);
        ASM_KEEP(low_mask);
        final_ctx = (u8 *)scratch;
        ASM_TAILSLOT_PIN(final_ctx);
        func_80024944(final_ctx);
    }

    ASM_KEEP(next);
    final_ctx = *(u8 **)global;
    FIELD(final_ctx, u8 *, 0x8D0) = scratch->cursor;
    return 0;
}
