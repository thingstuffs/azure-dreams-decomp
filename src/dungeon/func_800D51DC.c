#include "common.h"

typedef struct S_800DA93C_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800DA93C_0;   /* base->unk0 in func_800DA93C */

typedef struct S_800DA93C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_800DA93C_1_pre;   /* the 0x8 bytes before walker in func_800DA93C, addressed as walker[-1] */

typedef struct S_800DA93C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800DA93C_1;   /* walker in func_800DA93C */

typedef struct S_800DA93C_2 {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    u16 unk_0E;
    u8 pad_10[0x4];
    s8 unk_14;
    s8 unk_15;
    u16 unk_16;
    u8 pad_18[0x4];
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800DA93C_2;   /* record in func_800DA93C */

typedef struct S_800DA93C_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_800DA93C_3;   /* (u8 *)((u32)work + (u32)base->unk0) in func_800DA93C */

typedef struct S_800DA93C_4 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_800DA93C_4;   /* (u8 *)work in func_800DA93C */


typedef struct {
    void *unk0;
    u8 pad[0x1F8];
    s32 unk1FC;
} S_800A1600_D80083160;


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
        record = ((S_800DA93C_0 *)(base->unk0))->unk_8D0;
        ((S_800DA93C_0 *)(base->unk0))->unk_8D0 = (u8 *)record + 0x28;

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
            scratch = 0xFF - ((S_800DA93C_1 *)walker)->unk_02;
            ((S_800DA93C_2 *)record)->unk_04 = (*(s32 *)((u8 *)walker + 0x10));
            func_800666F4(record);
            func_80066640(record, 1);

            ((S_800DA93C_2 *)record)->unk_16 = ((S_800DA93C_1 *)walker)->unk_04;
            ((S_800DA93C_2 *)record)->unk_0E = ((S_800DA93C_1 *)walker)->unk_06;

            value = (s16)(((S_800DA93C_1 *)walker)->unk_02 % 8);
            scratch = value;

            quotient = (value % 4) << 5;
            byte_lo = quotient - 0x80;
            byte_hi = quotient - 0x61;
            ((S_800DA93C_2 *)record)->unk_14 = byte_lo;
            ((S_800DA93C_2 *)record)->unk_0C = byte_lo;
            ((S_800DA93C_2 *)record)->unk_24 = byte_hi;
            ((S_800DA93C_2 *)record)->unk_1C = byte_hi;

            quotient2 = (scratch / 4) << 5;
            byte_lo2 = quotient2 + 0x40;
            byte_hi2 = quotient2 + 0x5F;
            ((S_800DA93C_2 *)record)->unk_1D = byte_lo2;
            ((S_800DA93C_2 *)record)->unk_0D = byte_lo2;
            ((S_800DA93C_2 *)record)->unk_25 = byte_hi2;
            ((S_800DA93C_2 *)record)->unk_15 = byte_hi2;

            work = sum << 2;
            ((S_800DA93C_2 *)record)->unk_00 =
                (((S_800DA93C_2 *)record)->unk_00 & mask_hi) |
                (((S_800DA93C_3 *)((u8 *)((u32)work + (u32)base->unk0)))->unk_B0 & mask_lo);
            work += (s32)base->unk0;
            ((S_800DA93C_4 *)((u8 *)work))->unk_B0 =
                (((S_800DA93C_4 *)((u8 *)work))->unk_B0 & mask_hi) |
                ((u32)record & mask_lo);
        }

        work = ((S_800DA93C_1_pre *)walker)[-1].unk_00;
        walker = (void *)(work + 0x20);
    } while (work != 0);

    return 0;
}
