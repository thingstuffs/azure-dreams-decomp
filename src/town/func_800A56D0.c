#include "common.h"

typedef struct S_800A2E30_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A2E30_0;

typedef struct S_800A2E30_1 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} S_800A2E30_1;

typedef struct S_800A2E30_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A2E30_2;

typedef struct InputPair {
    u32 first;
    u32 second;
} InputPair;

typedef struct OutputPair {
    u16 first;
    u16 second;
    u32 pad;
} OutputPair;

extern u8 D_80083160[];

extern s32 func_800654B0(InputPair *, InputPair *, InputPair *, InputPair *,
                        OutputPair *, OutputPair *, OutputPair *, OutputPair *,
                        u32 *, u32 *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_80066708(void *, void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

/* Project and enqueue a shaded quad, then enqueue its draw mode packet. */
void func_800A2E30(InputPair vertex_0, InputPair vertex_1, InputPair vertex_2,
                   InputPair vertex_3, u16 shade)
{
    OutputPair screen_0;
    OutputPair screen_1;
    OutputPair screen_2;
    OutputPair screen_3;
    u32 depth_cue;
    u32 transform_flags;
    s32 depth_or_page;
    u8 *draw_ctx;
    u8 *packet;

    {
        u8 *quad_ctx;

        quad_ctx = *(u8 **)D_80083160;
        packet = ((S_800A2E30_0 *)quad_ctx)->unk_8D0;
        ((S_800A2E30_0 *)quad_ctx)->unk_8D0 = packet + 0x24;
        ((S_800A2E30_1 *)packet)->unk_16 = shade;
        ((S_800A2E30_1 *)packet)->unk_15 = shade;
        ((S_800A2E30_1 *)packet)->unk_14 = shade;
        ((S_800A2E30_1 *)packet)->unk_06 = shade;
        ((S_800A2E30_1 *)packet)->unk_05 = shade;
        ((S_800A2E30_1 *)packet)->unk_04 = shade;
        ((S_800A2E30_1 *)packet)->unk_1E = 0;
        ((S_800A2E30_1 *)packet)->unk_1D = 0;
        ((S_800A2E30_1 *)packet)->unk_1C = 0;
        ((S_800A2E30_1 *)packet)->unk_0E = 0;
        ((S_800A2E30_1 *)packet)->unk_0D = 0;
        ((S_800A2E30_1 *)packet)->unk_0C = 0;
        func_80066708(packet, quad_ctx);
    }
    func_80066640(packet, 1);

    depth_or_page = func_800654B0(&vertex_0, &vertex_1, &vertex_2, &vertex_3,
                          &screen_0, &screen_1, &screen_2, &screen_3, &depth_cue, &transform_flags);

    ((S_800A2E30_1 *)packet)->unk_08 = screen_0.first;
    ((S_800A2E30_1 *)packet)->unk_0A = screen_0.second;
    ((S_800A2E30_1 *)packet)->unk_10 = screen_1.first;
    ((S_800A2E30_1 *)packet)->unk_12 = screen_1.second;
    ((S_800A2E30_1 *)packet)->unk_18 = screen_2.first;
    ((S_800A2E30_1 *)packet)->unk_1A = screen_2.second;
    ((S_800A2E30_1 *)packet)->unk_20 = screen_3.first;
    ((S_800A2E30_1 *)packet)->unk_22 = screen_3.second;

    if (depth_or_page >= 0x1E0) {
        depth_or_page = 0x1DF;
    }

    func_8006658C(*(u8 **)D_80083160 + 0xD8, packet + depth_or_page - depth_or_page);

    draw_ctx = *(u8 **)D_80083160;
    packet = ((S_800A2E30_2 *)draw_ctx)->unk_8D0;
    ((S_800A2E30_2 *)draw_ctx)->unk_8D0 = packet + 0xC;
    depth_or_page = func_80066460(0, 1, 0x140, 0);
    func_80067F20(packet, 0, 0, (u16)depth_or_page, 0);

    func_8006658C(*(u8 **)D_80083160 + 0xD8, packet);
}
