#include "common.h"

typedef struct S_81988C1C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
    u8 pad_28[0x18];
    u8 unk_40;
    u8 pad_41[0x1];
    u8 unk_42;
    u8 pad_43[0x1];
    u8 unk_44;
    u8 pad_45[0x1];
    u8 unk_46;
    u8 pad_47[0x7];
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
} S_81988C1C_0;   /* item in func_81988C1C */

typedef struct S_81988C1C_1 {
    u16 unk_00;
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_81988C1C_1;   /* output in func_81988C1C */

typedef struct S_81988C1C_2 {
    union { void * s; u32 u; } unk_00;   /* accessed as both */
} S_81988C1C_2;   /* base in func_81988C1C */

typedef struct S_81988C1C_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_81988C1C_3;   /* pool in func_81988C1C */

typedef struct S_81988C1C_4 {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x4];
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x2];
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[0x4];
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
} S_81988C1C_4;   /* packet in func_81988C1C */

typedef struct S_81988C1C_5 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_81988C1C_5;   /* (u8 *)index in func_81988C1C */

typedef struct S_81988C1C_6_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_81988C1C_6_pre;   /* the 0x8 bytes before node in func_81988C1C, addressed as node[-1] */

typedef struct S_81988C1C_7 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_81988C1C_7;   /* (u8 *)(index + ((S_81988C1C_2 *)base)->unk_00.u) in func_81988C1C */


typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} S_800A1600_D80083160;

#ifdef NON_MATCHING
#define READ_ZERO(var) ((var) = 0)
#else
#define READ_ZERO(var) ASM_UNDEF(var)
#endif

extern S_800A1600_D80083160 D_80083160;
extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

s32 func_81988C1C(void *arg0) {
    u16 input[4];
    u8 output[8];
    s32 work;
    void *node = arg0;
    S_800A1600_D80083160 *base = &D_80083160;
    void *output_base = output;
    register void *next ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    do {
        void *item = node;
        void *outp;
        s32 i;
        u32 result;
        s32 half_width;
        u16 initial_value;

        input[0] = ((S_81988C1C_0 *)item)->unk_1E;
        input[1] = ((S_81988C1C_0 *)item)->unk_22;
        initial_value = ((S_81988C1C_0 *)item)->unk_26;
        input[2] = initial_value;
        input[2] = initial_value - ((s32)(((S_81988C1C_0 *)item)->unk_4E << 16) >> 17);

        i = 0;
        outp = output_base;
        do {
            result = func_80065420(input, outp, &work, &work) - 8;
            outp = (u8 *)outp + 4;
            i++;
            input[2] += ((S_81988C1C_0 *)item)->unk_4E;
        } while (i < 2);

        half_width = (((S_81988C1C_1 *)output)->unk_02.s - ((S_81988C1C_1 *)output)->unk_06.s) >> 1;
        if (result < 0x1E0U) {
            void *pool;
            void *packet;
            register u8 c1;
            u8 c0;
            register u8 delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u16 packet_value;
            register u32 index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u32 mask_lo;
            register u32 mask_hi ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            mask_hi = 0xA00000;
            pool = ((S_81988C1C_2 *)base)->unk_00.s;
            packet = ((S_81988C1C_3 *)pool)->unk_8D0;
            mask_hi |= 0xA0A0;
            ((S_81988C1C_3 *)pool)->unk_8D0 = (u8 *)packet + 0x34;
            ((S_81988C1C_4 *)packet)->unk_04 = mask_hi;
            func_800666F4(packet, mask_hi);
            func_80066640(packet, 1);

            ((S_81988C1C_4 *)packet)->unk_16 = ((S_81988C1C_0 *)item)->unk_50;
            (*(u16 *)((u8 *)packet + 0x0E)) = ((S_81988C1C_0 *)item)->unk_52;
            packet_value = ((S_81988C1C_1 *)output)->unk_00 + half_width;
            (*(u16 *)((u8 *)packet + 0x10)) = packet_value;
            (*(u16 *)((u8 *)packet + 0x08)) = packet_value;
            packet_value = *(volatile u16 *)&output[0] - half_width;
            (*(u16 *)((u8 *)packet + 0x20)) = packet_value;
            (*(u16 *)((u8 *)packet + 0x18)) = packet_value;
            packet_value = ((S_81988C1C_1 *)output)->unk_02.u;
            ((S_81988C1C_4 *)packet)->unk_1A = packet_value;
            ((S_81988C1C_4 *)packet)->unk_0A = packet_value;
            packet_value = ((S_81988C1C_1 *)output)->unk_06.u;
            ((S_81988C1C_4 *)packet)->unk_22 = packet_value;
            ((S_81988C1C_4 *)packet)->unk_12 = packet_value;

            c0 = ((S_81988C1C_0 *)item)->unk_40;
            mask_lo = 0xFFFFFF;
            ((S_81988C1C_4 *)packet)->unk_14 = c0;
            ((S_81988C1C_4 *)packet)->unk_0C = c0;
            delta = ((S_81988C1C_0 *)item)->unk_44;
            c0 += delta;
            ((S_81988C1C_4 *)packet)->unk_24 = c0;
            ((S_81988C1C_4 *)packet)->unk_1C = c0;
            c1 = ((S_81988C1C_0 *)item)->unk_42;
            index = result * 4;
            ((S_81988C1C_4 *)packet)->unk_1D = c1;
            ((S_81988C1C_4 *)packet)->unk_0D = c1;
            c1 += ((S_81988C1C_0 *)item)->unk_46;
            mask_hi = 0xFF000000;
            ((S_81988C1C_4 *)packet)->unk_25 = c1;
            ((S_81988C1C_4 *)packet)->unk_15 = c1;

            ((S_81988C1C_4 *)packet)->unk_00 =
                (((S_81988C1C_4 *)packet)->unk_00 & mask_hi) |
                (((S_81988C1C_7 *)((u8 *)(index + ((S_81988C1C_2 *)base)->unk_00.u)))->unk_B0 & mask_lo);
            index += (u32)((S_81988C1C_2 *)base)->unk_00.s;
            ((S_81988C1C_5 *)((u8 *)index))->unk_B0 =
                (((S_81988C1C_5 *)((u8 *)index))->unk_B0 & mask_hi) |
                ((u32)packet & mask_lo);
            ASM_KEEP(mask_lo);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        }

        next = ((S_81988C1C_6_pre *)node)[-1].unk_00;
        node = (u8 *)next + 0x20;
    } while (next != 0);

    {
        register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        register s32 ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        READ_ZERO(zero);
        ret = zero;
        ASM_KEEP(ret);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        return ret;
    }
}
