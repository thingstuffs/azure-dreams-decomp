#include "common.h"

typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} S_800A1600_D80083160;

#define FIELD(x, t, o) (*(t *)((u8 *)(x) + (o)))
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
    register void *next ASM_REG("$4");

    do {
        void *item = node;
        void *outp;
        s32 i;
        u32 result;
        s32 half_width;
        u16 initial_value;

        input[0] = FIELD(item, u16, 0x1E);
        input[1] = FIELD(item, u16, 0x22);
        initial_value = FIELD(item, u16, 0x26);
        input[2] = initial_value;
        input[2] = initial_value - ((s32)(FIELD(item, u16, 0x4E) << 16) >> 17);

        i = 0;
        outp = output_base;
        do {
            result = func_80065420(input, outp, &work, &work) - 8;
            outp = (u8 *)outp + 4;
            i++;
            input[2] += FIELD(item, u16, 0x4E);
        } while (i < 2);

        half_width = (FIELD(output, s16, 2) - FIELD(output, s16, 6)) >> 1;
        if (result < 0x1E0U) {
            void *pool;
            void *packet;
            register u8 c1;
            u8 c0;
            register u8 delta ASM_REG("$2");
            u16 packet_value;
            register u32 index ASM_REG("$4");
            register u32 mask_lo ASM_REG("$6");
            register u32 mask_hi ASM_REG("$5");

            mask_hi = 0xA00000;
            ASM_KEEP(mask_hi);
            pool = FIELD(base, void *, 0);
            packet = FIELD(pool, void *, 0x8D0);
            ASM_KEEP(packet);
            mask_hi |= 0xA0A0;
            FIELD(pool, void *, 0x8D0) = (u8 *)packet + 0x34;
            FIELD(packet, s32, 4) = mask_hi;
            func_800666F4(packet, mask_hi);
            func_80066640(packet, 1);

            FIELD(packet, u16, 0x16) = FIELD(item, u16, 0x50);
            FIELD(packet, u16, 0x0E) = FIELD(item, u16, 0x52);
            packet_value = FIELD(output, u16, 0) + half_width;
            FIELD(packet, u16, 0x10) = packet_value;
            FIELD(packet, u16, 0x08) = packet_value;
            packet_value = *(volatile u16 *)&output[0] - half_width;
            FIELD(packet, u16, 0x20) = packet_value;
            FIELD(packet, u16, 0x18) = packet_value;
            packet_value = FIELD(output, u16, 2);
            FIELD(packet, u16, 0x1A) = packet_value;
            FIELD(packet, u16, 0x0A) = packet_value;
            packet_value = FIELD(output, u16, 6);
            FIELD(packet, u16, 0x22) = packet_value;
            FIELD(packet, u16, 0x12) = packet_value;

            c0 = FIELD(item, u8, 0x40);
            mask_lo = 0xFFFFFF;
            FIELD(packet, u8, 0x14) = c0;
            FIELD(packet, u8, 0x0C) = c0;
            delta = FIELD(item, u8, 0x44);
            c0 += delta;
            FIELD(packet, u8, 0x24) = c0;
            FIELD(packet, u8, 0x1C) = c0;
            c1 = FIELD(item, u8, 0x42);
            index = result * 4;
            FIELD(packet, u8, 0x1D) = c1;
            FIELD(packet, u8, 0x0D) = c1;
            c1 += FIELD(item, u8, 0x46);
            mask_hi = 0xFF000000;
            FIELD(packet, u8, 0x25) = c1;
            FIELD(packet, u8, 0x15) = c1;

            FIELD(packet, u32, 0) =
                (FIELD(packet, u32, 0) & mask_hi) |
                (FIELD((u8 *)(index + FIELD(base, u32, 0)), u32, 0xB0) & mask_lo);
            index += (u32)FIELD(base, void *, 0);
            FIELD((u8 *)index, u32, 0xB0) =
                (FIELD((u8 *)index, u32, 0xB0) & mask_hi) |
                ((u32)packet & mask_lo);
            ASM_KEEP(mask_lo);
            ASM_KEEP(mask_hi);
        }

        next = FIELD(node, void *, -8);
        node = (u8 *)next + 0x20;
    } while (next != 0);

    {
        register s32 zero ASM_REG("$0");
        register s32 ret ASM_REG("$2");
        READ_ZERO(zero);
        ret = zero;
        ASM_KEEP(ret);
        return ret;
    }
}
