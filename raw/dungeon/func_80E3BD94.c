#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_800666F4(void *);
extern u8 D_8006CD30[];
extern u8 D_80083160[];

typedef struct {
    s32 tag;
    s32 color;
    s16 x0;
    s16 y0;
    u16 uv0;
    u16 clut;
    s16 x1;
    s16 y1;
    u16 uv1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u16 uv2;
    u16 pad2;
    s16 x3;
    s16 y3;
    u16 uv3;
    u16 pad3;
} Packet;

typedef struct {
    s8 flag;
    u8 pad;
    s8 x;
    s8 y;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
} Texture;

void func_80175594(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 **global = (u8 **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *state;
    u8 *matrix;
    Packet *packet;
    Texture *texture;
    s32 value;
    s32 screen_x;
    s32 screen_y;
    s32 visible0;
    s32 visible1;
    s32 visible2;
    s32 visible3;
    s32 visible01;
    s32 visible012;

    if (FIELD(arg0, s16, 0x1C) == 0) {
        return;
    }

    state = *global;
    FIELD(scratch, s32, 0xEC) = 0;
    FIELD(scratch, s16, 0x8C) = 0;
    FIELD(scratch, s16, 0x84) = 0;
    FIELD(scratch, s16, 0x7C) = 0;
    FIELD(scratch, s16, 0x74) = 0;
    FIELD(scratch, u8 *, 0x20) = state + 0xB0;
    FIELD(scratch, u16, 0) = FIELD(arg1, u16, 2);
    FIELD(scratch, u16, 2) = FIELD(arg1, u16, 6);
    FIELD(scratch, u16, 4) = FIELD(arg1, u16, 0xA);
    packet = (Packet *)FIELD(state, u8 *, 0x8D0);
    FIELD(scratch, s32, 0xC0) = func_80065420(
        scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);

    FIELD(arg2, u16, 0x14) |= 0x8000;
    {
        u32 projected = *(volatile u32 *)(scratch + 0xC0);
        u32 adjusted;
        u32 bias_temp;
        adjusted = (bias_temp = projected - 6, bias_temp - (s16)arg3);
        matrix = D_8006CD30;
        FIELD(matrix, s32, 0x1C) = projected * 4;
        FIELD(scratch, s32, 0xC0) = adjusted;
    }

    if ((u32)FIELD(scratch, s32, 0xC0) < 0x1E0U) {
        func_800649A0();
        FIELD(scratch, u16, 0xB8) -= 0xA0;
        FIELD(scratch, u16, 0xBA) -= 0x78;
        FIELD(scratch, s32, 0x30) = FIELD(global, s16, 0xC4);
        FIELD(scratch, s32, 0x34) = FIELD(global, s16, 0xC6);
        FIELD(scratch, s32, 0x38) = FIELD(global, s16, 0xC8);

        FIELD(scratch, u16, 0x100) = FIELD(arg2, u16, 0x16);
        FIELD(scratch, u16, 0x104) =
            FIELD(global, u16, 0xB8) +
            (FIELD(arg2, u16, 0x1A) - FIELD(scratch, u16, 0x34));
        screen_x = (FIELD(scratch, u16, 0x38) + 0x100) & 0x1FF;
        screen_y = FIELD(arg2, u16, 0x18) - 0x100;
        FIELD(scratch, u16, 0x102) = screen_x + screen_y;

        FIELD(scratch, u16, 0x108) = FIELD(scratch, s32, 0xE4) =
            FIELD(arg2, u16, 0x20);
        FIELD(scratch, u16, 0x10A) = FIELD(scratch, s32, 0xE8) =
            FIELD(arg2, u16, 0x22);
        func_80065820(scratch + 0x100, scratch + 0xD0);

        FIELD(scratch, s32, 0x30) = FIELD(arg2, u16, 0x1C);
        FIELD(scratch, s32, 0x34) = FIELD(arg2, u16, 0x1E);
        FIELD(scratch, s32, 0x38) = 0x1000;
        func_80064BC0(scratch + 0xD0, scratch + 0x30);
        func_80064840(matrix, scratch + 0xD0, scratch + 0x50);
        func_80064D80(scratch + 0x50);
        func_80064CF0(scratch + 0x50);

        texture = (Texture *)FIELD(arg2, u8 *, 8);
        FIELD(scratch, u16, 0x24) = FIELD(arg2, u16, 0x14);

        for (;;) {
            FIELD(scratch, s32, 8) = texture->f8;
            FIELD(scratch, s32, 0xC) = texture->f9;
            FIELD(scratch, s32, 0x10) = texture->fA;
            FIELD(scratch, s32, 0x14) = texture->fB;

            value = (texture->x -
                     (s16)FIELD(scratch, u16, 0x108)) *
                    FIELD(arg0, s16, 0x22);
            FIELD(scratch, s16, 0x70) = value >> 12;
            value = (texture->x -
                     (s16)FIELD(scratch, u16, 0x108)) *
                    FIELD(arg0, s16, 0x2A);
            FIELD(scratch, s16, 0x80) = value >> 12;
            value = ((s16)FIELD(scratch, u16, 0x70) +
                     FIELD(scratch, s32, 0x10)) *
                    FIELD(arg0, s16, 0x28);
            FIELD(scratch, s16, 0x78) = value >> 12;
            value = ((s16)FIELD(scratch, u16, 0x70) +
                     FIELD(scratch, s32, 0x10)) *
                    FIELD(arg0, s16, 0x30);
            FIELD(scratch, s16, 0x88) = value >> 12;

            value = (texture->y -
                     (s16)FIELD(scratch, u16, 0x10A)) *
                    FIELD(arg0, s16, 0x24);
            FIELD(scratch, s16, 0x72) = value >> 12;
            value = (texture->y -
                     (s16)FIELD(scratch, u16, 0x10A)) *
                    FIELD(arg0, s16, 0x28);
            FIELD(scratch, s16, 0x7A) = value >> 12;
            value = ((s16)FIELD(scratch, u16, 0x72) +
                     FIELD(scratch, s32, 0x14)) *
                    FIELD(arg0, s16, 0x2C);
            FIELD(scratch, s16, 0x82) = value >> 12;
            {
                register void *call_y ASM_REG("$5") = scratch + 0x78;
                register void *call_z ASM_REG("$6") = scratch + 0x80;
                register void *call_w ASM_REG("$7") = scratch + 0x88;
                register void *call_out0 ASM_REG("$8");
                register s32 final_partial ASM_REG("$2");
                register s32 final_coeff ASM_REG("$3");

                final_partial = FIELD(scratch, u16, 0x72);
                ASM_KEEP(final_partial);
                call_out0 = scratch + 0xF0;
                ASM_KEEP_DEP_NV(final_partial, call_out0);
                final_partial = (s16)final_partial +
                                FIELD(scratch, s32, 0x14);
                ASM_KEEP(final_partial);
                final_coeff = FIELD(arg0, s16, 0x30);
                value = final_partial * final_coeff;
                FIELD(scratch, s16, 0x8A) = value >> 12;

                func_800654B0(scratch + 0x70, call_y,
                              call_z, call_w,
                              call_out0, scratch + 0xF4,
                              scratch + 0xF8, scratch + 0xFC,
                              scratch + 0x90, scratch + 0x94);
            }

            FIELD(packet, s16, 8) =
                FIELD(scratch, u16, 0xF0) + FIELD(scratch, u16, 0xB8);
            FIELD(packet, s16, 0xA) =
                FIELD(scratch, u16, 0xF2) + FIELD(scratch, u16, 0xBA);
            FIELD(packet, s16, 0x10) =
                FIELD(scratch, u16, 0xF4) + FIELD(scratch, u16, 0xB8);
            FIELD(packet, s16, 0x12) =
                FIELD(scratch, u16, 0xF6) + FIELD(scratch, u16, 0xBA);
            FIELD(packet, s16, 0x18) =
                FIELD(scratch, u16, 0xF8) + FIELD(scratch, u16, 0xB8);
            FIELD(packet, s16, 0x1A) =
                FIELD(scratch, u16, 0xFA) + FIELD(scratch, u16, 0xBA);
            FIELD(packet, s16, 0x20) =
                FIELD(scratch, u16, 0xFC) + FIELD(scratch, u16, 0xB8);
            FIELD(packet, s16, 0x22) =
                FIELD(scratch, u16, 0xFE) + FIELD(scratch, u16, 0xBA);

            visible0 = 0;
            if ((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181U) {
                visible0 =
                    (u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121U;
            }
            visible1 = 0;
            if ((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181U) {
                visible1 =
                    (u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121U;
            }
            visible01 = visible0 | visible1;
            visible2 = 0;
            if ((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181U) {
                visible2 =
                    (u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121U;
            }
            visible012 = visible01 | visible2;
            visible3 = 0;
            if ((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181U) {
                visible3 =
                    (u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121U;
            }

            if ((visible012 | visible3) != 0) {
                FIELD(scratch, s32, 0x10) += FIELD(scratch, s32, 8);
                FIELD(scratch, s32, 0x14) =
                    (FIELD(scratch, s32, 0xC) +
                     FIELD(scratch, s32, 0x14)) << 8;
                FIELD(scratch, s32, 0xC) <<= 8;

                FIELD(packet, u16, 0xE) =
                    FIELD(arg2, u16, 0x12) + texture->f6;
                FIELD(packet, u16, 0xC) =
                    FIELD(scratch, u16, 0xC) + FIELD(scratch, u16, 8);
                FIELD(packet, u16, 0x14) =
                    FIELD(scratch, u16, 0xC) + FIELD(scratch, u16, 0x10);
                if (FIELD(arg2, u16, 0x10) != 0) {
                    FIELD(packet, u16, 0x16) =
                        FIELD(arg2, u16, 0x10) +
                        (texture->f4 & 0xFF9F);
                } else {
                    FIELD(packet, u16, 0x16) = texture->f4;
                }
                FIELD(packet, u16, 0x1C) =
                    FIELD(scratch, u16, 0x14) + FIELD(scratch, u16, 8);
                FIELD(packet, u16, 0x24) =
                    FIELD(scratch, u16, 0x14) + FIELD(scratch, u16, 0x10);

                if (FIELD(packet, u8, 0x14) == 0) {
                    FIELD(packet, u8, 0x14)--;
                    FIELD(packet, u8, 0x24)--;
                }
                if (FIELD(packet, u8, 0x1D) == 0) {
                    FIELD(packet, u8, 0x1D)--;
                    FIELD(packet, u8, 0x25)--;
                }

                FIELD(packet, s32, 4) = FIELD(arg2, s32, 0xC);
                func_800666F4(packet);
                if (FIELD(scratch, u16, 0x24) & 8) {
                    FIELD(packet, u8, 7) |= 2;
                }

                func_8006658C(FIELD(scratch, u8 *, 0x20) +
                                  FIELD(scratch, s32, 0xC0) * 4,
                              packet);
                packet++;
            }

            if (texture->flag < 0) {
                break;
            }
            texture++;
        }

        func_80064A40();
    }

    FIELD(*global, u8 *, 0x8D0) = packet;
}
