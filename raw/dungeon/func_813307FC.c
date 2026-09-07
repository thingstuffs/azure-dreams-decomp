#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef struct {
    s32 words[8];
} __attribute__((packed)) LocalTable;

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340;
extern u8 D_800DEAE0[];
extern LocalTable D_8016482C;
extern M2C_UNK D_80167540[3];
extern s32 D_80175D50;

void func_801677FC(void)
{
    LocalTable table;
    s32 temp_v1_2;
    s32 var_s1;
    u8 *pb;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_s2;
    void *temp_s3;
    void *temp_v0;
    void *temp_v1;

    table = D_8016482C;
    var_s1 = 0;
    temp_s3 = (void *)D_80175D50 + 0x20;
    temp_s2 = M2C_FIELD((void *)D_80175D50, void **, 8);
    do {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            temp_v1 = temp_v0 + 0x20;
            M2C_FIELD(temp_v1, s16 *, 0x18) = 0xE;
            M2C_FIELD(temp_v1, s16 *, 0x1A) = 0xE;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = D_80167540;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x10) = 0x60;
            M2C_FIELD(temp_a0, u16 *, 0x14) =
                (u16)(M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
            temp_a0_2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_a0_2, s32 *, 0) = M2C_FIELD(temp_s2, s32 *, 0);
            M2C_FIELD(temp_a0_2, s32 *, 4) = M2C_FIELD(temp_s2, s32 *, 4);
            M2C_FIELD(temp_a0_2, s32 *, 8) =
                M2C_FIELD(temp_s2, s32 *, 8) + (s32)0xFFCE0000;
            M2C_FIELD(temp_a0_2, u16 *, 2) =
                (u16)(M2C_FIELD(temp_a0_2, u16 *, 2) +
                (M2C_FIELD(&table, s16 *,
                    ((M2C_FIELD(temp_s3, u16 *, 0x2A) >> 7) & 0x1C)) * 0x14));
            temp_v1_2 = var_s1 << 9;
            pb = (u8 *)&table + ((M2C_FIELD(temp_s3, u16 *, 0x2A) >> 7) & 0x1C);
            M2C_FIELD(temp_a0_2, u16 *, 6) =
                (u16)(M2C_FIELD(temp_a0_2, u16 *, 6) +
                ((s16)*(u16 *)(pb + 2) * 0x14));
            temp_a0_3 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0_3, s16 *, 0x1C) = (s16)(temp_v1_2 + 0x1C00);
            M2C_FIELD(temp_a0_3, s16 *, 0x1E) = (s16)(temp_v1_2 + 0x1400);
            M2C_FIELD(temp_a0_3, s8 *, 0xE) = 0;
            M2C_FIELD(temp_a0_3, s8 *, 0xD) = 0;
            M2C_FIELD(temp_a0_3, s8 *, 0xC) = 0;
            M2C_FIELD(temp_a0_3, s16 *, 6) = 0;
            M2C_FIELD(temp_a0_3, s16 *, 0x12) = 0x7DCF;
            M2C_FIELD(temp_a0_3, u16 *, 0x14) =
                (u16)(M2C_FIELD(temp_a0_3, u16 *, 0x14) | 0x100);
            func_8003DB94(temp_a0_3, D_800DEAE0, 0);
        }
        var_s1 += 1;
    } while (var_s1 < 0x10);
}
