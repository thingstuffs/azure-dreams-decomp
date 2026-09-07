#include "common.h"

typedef struct Packet81976F70 {
    u8 link_bytes[3];
    u8 type;
    u8 x0_hi;
    u8 x0_mid;
    u8 x0_lo;
    u8 unk7;
    u16 u8;
    u16 uA;
    u8 color0;
    u8 unkD;
    u16 unkE;
    u8 x1_hi;
    u8 x1_mid;
    u8 x1_lo;
    u8 pad13;
    u16 u14;
    u16 u16;
    u8 unk18;
    u8 unk19;
    u16 random;
    u8 x2_hi;
    u8 x2_mid;
    u8 x2_lo;
    u8 pad1F;
    u16 u20;
    u16 u22;
    u8 color2;
    u8 unk25;
    u8 pad26[2];
} Packet81976F70;

typedef struct State81976F70 {
    u8 pad0[0x8D0];
    Packet81976F70 *next;
} State81976F70;

typedef struct Scratch81976F70 {
    u32 *ordering_table;
    s32 ordering_index;
    u8 pad8[8];
    s16 x0;
    s16 y0;
    s16 z0;
    u8 pad16[2];
    s16 x1;
    s16 y1;
    s16 z1;
    u8 pad1E[2];
    s16 x2;
    s16 y2;
    s16 z2;
    u8 pad26[0xA];
    s32 vx0;
    s32 vy0;
    s32 vz0;
    u8 pad3C[4];
    s32 vx1;
    s32 vy1;
    s32 vz1;
    u8 pad4C[4];
    s32 vx2;
    s32 vy2;
    s32 vz2;
    u8 pad5C[0x14];
    u16 out0;
    u16 out1;
    u16 out2;
    u16 out3;
    u16 out4;
    u16 out5;
} Scratch81976F70;

extern u8 D_80083160[];
extern s32 *D_80026208;
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);

s32 func_81976F70(s32 arg0, s32 arg1, s32 arg2)
{
    State81976F70 *state;
    Packet81976F70 *packet;
    Scratch81976F70 *scratch = (Scratch81976F70 *)0x1F800000;
    s32 *offset;
    s32 color;
    s32 random;
    void *out4;
    void *out5;
    void *out6;
    void *out7;
    u32 ordering_link;

    state = *(State81976F70 **)D_80083160;
    scratch->ordering_table = (u32 *)((u8 *)state + 0xB0);
    packet = state->next;
    state->next = packet + 1;

    packet->type = 9;
    packet->unk7 = 0x36;
    random = func_80066460(0, 3, 0x300, 0x100);
    out4 = (void *)((u32)scratch | 0x74);
    out5 = (void *)((u32)scratch | 0x78);
    out6 = (void *)((u32)scratch | 8);
    out7 = scratch;
    packet->random = random;
    packet->unkE = 0x7DCF;
    color = 0xC0;
    packet->color0 = color;
    packet->unkD = 0x7F;
    packet->unk18 = 0xFF;
    packet->unk19 = 0x40;
    packet->unk25 = 0x40;
    packet->x0_hi = arg0 >> 16;
    packet->x0_mid = arg0 >> 8;
    packet->x1_hi = arg1 >> 16;
    packet->x1_mid = arg1 >> 8;
    packet->x2_hi = arg2 >> 16;
    packet->x2_mid = arg2 >> 8;
    packet->color0 = color;
    packet->color2 = color;
    packet->x0_lo = arg0;
    packet->x1_lo = arg1;
    packet->x2_lo = arg2;

    offset = D_80026208;
    scratch->x0 = (scratch->vx0 + offset[0]) >> 16;
    scratch->x1 = (scratch->vx1 + offset[0]) >> 16;
    scratch->x2 = (scratch->vx2 + offset[0]) >> 16;
    scratch->y0 = (scratch->vy0 + offset[1]) >> 16;
    scratch->y1 = (scratch->vy1 + offset[1]) >> 16;
    scratch->y2 = (scratch->vy2 + offset[1]) >> 16;
    scratch->z0 = (scratch->vz0 + offset[2]) >> 16;
    scratch->z1 = (scratch->vz1 + offset[2]) >> 16;
    scratch->z2 = (scratch->vz2 + offset[2]) >> 16;

    scratch->ordering_index = func_80065530(
        (void *)((u32)scratch | 0x10), (void *)((u32)scratch | 0x18),
        (void *)((u32)scratch | 0x20), (void *)((u32)scratch | 0x70),
        out4, out5, out6, (void *)((u32)out7 | 0xC));

    packet->u8 = scratch->out0;
    packet->uA = scratch->out1;
    packet->u14 = scratch->out2;
    packet->u16 = scratch->out3;
    packet->u20 = scratch->out4;
    packet->u22 = scratch->out5;

    if ((u32)scratch->ordering_index < 0x1E0U) {
        ordering_link = scratch->ordering_table[scratch->ordering_index];
        *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                        (ordering_link & 0x00FFFFFF);
        scratch->ordering_table[scratch->ordering_index] =
            (scratch->ordering_table[scratch->ordering_index] & 0xFF000000) |
            ((u32)packet & 0x00FFFFFF);
    }

    return 0;
}
