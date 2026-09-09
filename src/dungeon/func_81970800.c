/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"



#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern u8 D_80083160[];

#ifdef __mips__
static const u32 func_81970800_prefix[] __asm__("func_81970800")
    __attribute__((section(".text.func_81970800"))) = {
    0x8002512C,
    0x00000000,
    0x80024D5C,
    0x80024D64,
    0x80024D6C,
    0x80024D74,
    0x80024D7C,
    0x80024D7C,
    0x80024D74,
    0x80024D6C,
    0x80024D64,
    0x80024D5C,
    0x80024D5C,
    0x80024D64,
    0x80024D6C,
    0x80024D74,
    0x80024D7C,
    0x80024D7C,
    0x80024D74,
    0x80024D6C,
    0x80024D64,
    0x80024D5C,
    0x80025190,
    0x800251EC,
    0x80025258,
    0x80025E74,
    0x80025F44,
};
__asm__(".globl func_81970800\n"
        ".type func_81970800,@function\n"
        ".size func_81970800,1348");
#define BODY_NAME func_8197086C
#else
#define BODY_NAME func_81970800
#endif

typedef struct S_func_81970800_1 {
    u8 pad_00[0x24];
    u32 *unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_func_81970800_1;

typedef struct S_func_81970800_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_81970800_2;

typedef struct S_func_81970800_3 {
    u8 pad_00[0x8];
    u8 *unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_func_81970800_3;

typedef struct S_func_81970800_4 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x30];
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
} S_func_81970800_4;

typedef struct S_func_81970800_5 {
    union {
        u32 unk_00;
        struct {
            u8 pad_00[3];
            u8 unk_03;
        } unk_03;
    } unk_00;
    union {
        u32 unk_04;
        struct {
            u8 pad_04[3];
            u8 unk_07;
        } unk_07;
    } unk_04;
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} S_func_81970800_5;

typedef struct S_func_81970800_6 {
    u8 pad_00[0xB0];
    u32 unk_B0;
    u8 pad_B4[0x81C];
    u8 *unk_8D0;
} S_func_81970800_6;

/* Project and enqueue a shaded quad if its depth and screen bounds are visible. */
void BODY_NAME(S_func_81970800_4 *quad, S_func_81970800_2 *position, S_func_81970800_3 *object, s16 depth_bias)
{
    S_func_81970800_1 *scratch = (S_func_81970800_1 *)0x1F800000;
    S_func_81970800_5 *packet;
    u8 *texture;
    s32 depth;
    u16 draw_flags;
    u8 tex_flags;
    u8 **render_context_ref = (u8 **)D_80083160;
    MATRIX matrix;

    scratch->unk_24 = (u32 *)(*(u8 **)D_80083160 + 0xB0);
    scratch->unk_88 = position->unk_02;
    scratch->unk_8C = position->unk_06;
    scratch->unk_90 = position->unk_0A;
    object->unk_14 |= 0x8000;

    func_800649A0();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = object->unk_16;
    scratch->unk_A8 = object->unk_1A;
    scratch->unk_A6 = object->unk_18;
    func_80065820((u8 *)scratch + 0xA4, (u8 *)scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, (u8 *)scratch + 0x74, (u8 *)scratch + 0x54);
    func_80064BC0((u8 *)scratch + 0x54, (u8 *)scratch + 0x34);
    func_80064D80((u8 *)scratch + 0x54);
    func_80064CF0((u8 *)scratch + 0x54);

    texture = object->unk_08;
    scratch->unk_28 = object->unk_14;

    packet = (S_func_81970800_5 *)((S_func_81970800_6 *)*(u8 **)D_80083160)->unk_8D0;
    ((S_func_81970800_6 *)*(u8 **)D_80083160)->unk_8D0 = (u8 *)packet + 0xC;
    func_80067F20(packet, 0, 0, func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
    (*(u32 *)((u8 *)packet + 0)) = (packet->unk_00.unk_00 & 0xFF000000) |
        (((S_func_81970800_6 *)*(u8 **)D_80083160)->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)*(u8 **)D_80083160 + 0xB0)) =
        (((S_func_81970800_6 *)*(u8 **)D_80083160)->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        S_func_81970800_6 *render_context;

        render_context = (S_func_81970800_6 *)*(u8 * volatile *)D_80083160;
        packet = (S_func_81970800_5 *)render_context->unk_8D0;
        render_context->unk_8D0 = (u8 *)packet + 0x24;
    }

    scratch->unk_B0 = quad->unk_4C;
    scratch->unk_B8 = quad->unk_52;
    scratch->unk_C0 = quad->unk_58;
    scratch->unk_C8 = quad->unk_5E;
    scratch->unk_B2 = quad->unk_4E;
    scratch->unk_BA = quad->unk_54;
    scratch->unk_C2 = quad->unk_5A;
    scratch->unk_CA = quad->unk_60;
    scratch->unk_B4 = quad->unk_50;
    scratch->unk_BC = quad->unk_56;
    scratch->unk_C4 = quad->unk_5C;
    scratch->unk_CC = quad->unk_62;

    depth = func_80065590((u8 *)scratch + 0xB0, (u8 *)scratch + 0xB8,
                          (u8 *)scratch + 0xC0, (u8 *)scratch + 0xC8,
                          (u8 *)packet + 8, (u8 *)packet + 0x10,
                          (u8 *)packet + 0x18, (u8 *)packet + 0x20,
                          (u8 *)scratch + 0xD0, (u8 *)scratch + 0xD4) - depth_bias - 6;
    scratch->unk_100 = depth;

    if ((u32)depth < 0x1E0) {
        if ((((u16)(packet->unk_08 + 0x20) < 0x181) &&
             ((u16)(packet->unk_0A + 0x20) < 0x121)) |
            (((u16)(packet->unk_10 + 0x20) < 0x181) &&
             ((u16)(packet->unk_12 + 0x20) < 0x121)) |
            (((u16)(packet->unk_18 + 0x20) < 0x181) &&
             ((u16)(packet->unk_1A + 0x20) < 0x121)) |
            (((u16)(packet->unk_20 + 0x20) < 0x181) &&
             ((u16)(packet->unk_22 + 0x20) < 0x121))) {
            object->unk_14 &= 0x7FFF;
            tex_flags = texture[1];
            object->unk_0F = tex_flags;
            draw_flags = scratch->unk_28;
            if (draw_flags & 8) {
                object->unk_0F = (draw_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            packet->unk_04.unk_04 = quad->unk_0C;
            packet->unk_0C = quad->unk_10;
            packet->unk_14 = quad->unk_14;
            packet->unk_1C = quad->unk_18;
            packet->unk_00.unk_03.unk_03 = 8;
            packet->unk_04.unk_07.unk_07 = 0x3A;

            packet->unk_00.unk_00 = (packet->unk_00.unk_00 & 0xFF000000) |
                (scratch->unk_24[scratch->unk_100] & 0x00FFFFFF);
            (*(u32 *)((u8 *)scratch->unk_24 + scratch->unk_100 * 4)) =
                (scratch->unk_24[scratch->unk_100] & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = (S_func_81970800_5 *)((S_func_81970800_6 *)(*render_context_ref))->unk_8D0;
            ((S_func_81970800_6 *)(*render_context_ref))->unk_8D0 = (u8 *)packet + 0xC;
            func_80067F20(packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            packet->unk_00.unk_00 = (packet->unk_00.unk_00 & 0xFF000000) |
                (scratch->unk_24[scratch->unk_100] & 0x00FFFFFF);
            scratch->unk_24[scratch->unk_100] =
                (scratch->unk_24[scratch->unk_100] & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
