#include "common.h"

typedef struct {
    void *unk0;
    u8 pad[0x1F8];
    s32 unk1FC;
} S_800A1600_D80083160;

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern S_800A1600_D80083160 D_80083160;
extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

s32 func_800DA93C(void *arg0) {
    void *walker;
    void *record;
    S_800A1600_D80083160 *base;
    s32 scratch;
    s32 sum;
    register s32 work;
    s32 value;
    s32 quotient;
    s8 byte_lo;
    s8 byte_hi;
    s32 quotient2;
    s8 byte_lo2;
    s8 byte_hi2;
    u32 mask_lo;
    u32 mask_hi;

    walker = arg0;
    base = &D_80083160;
    mask_lo = 0x00FFFFFF;
    mask_hi = 0xFF000000;

    do {
        record = FIELD(base->unk0, void *, 0x8D0);
        FIELD(base->unk0, void *, 0x8D0) = (u8 *)record + 0x28;

        sum = func_80065420((u8 *)walker + 0x28,
                           (u8 *)record + 8, &scratch, &scratch);
        sum += func_80065420((u8 *)walker + 0x30,
                            (u8 *)record + 0x10, &scratch, &scratch);
        sum += func_80065420((u8 *)walker + 0x38,
                            (u8 *)record + 0x18, &scratch, &scratch);
        sum += func_80065420((u8 *)walker + 0x40,
                            (u8 *)record + 0x20, &scratch, &scratch);
        sum = (sum >> 2) - 8;

        if ((u32)sum < 0x1E0U) {
            scratch = 0xFF - FIELD(walker, s16, 2);
            FIELD(record, s32, 4) = FIELD(walker, s32, 0x10);
            func_800666F4(record);
            func_80066640(record, 1);

            FIELD(record, u16, 0x16) = FIELD(walker, u16, 4);
            FIELD(record, u16, 0x0E) = FIELD(walker, u16, 6);

            value = (s16)(FIELD(walker, s16, 2) % 8);
            scratch = value;

            quotient = (value % 4) << 5;
            byte_lo = quotient - 0x80;
            byte_hi = quotient - 0x61;
            FIELD(record, s8, 0x14) = byte_lo;
            FIELD(record, s8, 0x0C) = byte_lo;
            FIELD(record, s8, 0x24) = byte_hi;
            FIELD(record, s8, 0x1C) = byte_hi;

            quotient2 = (scratch / 4) << 5;
            byte_lo2 = quotient2 + 0x40;
            byte_hi2 = quotient2 + 0x5F;
            FIELD(record, s8, 0x1D) = byte_lo2;
            FIELD(record, s8, 0x0D) = byte_lo2;
            FIELD(record, s8, 0x25) = byte_hi2;
            FIELD(record, s8, 0x15) = byte_hi2;

            work = sum << 2;
            FIELD(record, u32, 0) =
                (FIELD(record, u32, 0) & mask_hi) |
                (FIELD((u8 *)((u32)work + (u32)base->unk0), u32, 0xB0) & mask_lo);
            work += (s32)base->unk0;
            FIELD((u8 *)work, u32, 0xB0) =
                (FIELD((u8 *)work, u32, 0xB0) & mask_hi) |
                ((u32)record & mask_lo);
        }

        work = FIELD(walker, s32, -8);
        walker = (void *)(work + 0x20);
    } while (work != 0);

    return 0;
}
