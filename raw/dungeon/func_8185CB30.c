#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8002421C();
extern M2C_UNK func_8003DB94();
extern M2C_UNK func_800478B8();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s16 D_80083160[];
extern u8 D_800DEAE0[];

void func_8185CB30(void *arg0, void *arg1, void *arg2)
{
    s16 temp_v0_2;
    u16 temp_a0;
    u16 temp_v0;
    s16 *temp_s3;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) =
        (u16)(M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    temp_s3 = D_80083160;
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x22);
    temp_v0 = temp_a0 + 1;
    M2C_FIELD(arg0, u16 *, 0x22) = temp_v0;
    if ((s16)temp_v0 >= 8) {
        M2C_FIELD(arg0, u16 *, 0x22) = (u16)(temp_a0 - 7);
    }
    if ((s16)M2C_FIELD(arg0, u16 *, 0x22) ==
        M2C_FIELD(arg0, s16 *, 0x24)) {
        func_8002421C(M2C_FIELD(arg0, void **, 0), arg1);
    }
    if (M2C_FIELD(arg0, s16 *, 0x1E) < 0xC1) {
        M2C_FIELD(arg0, s16 *, 0x1E) =
            (s16)((u16)M2C_FIELD(arg0, s16 *, 0x1E) + 8);
    }
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x1C) +
        (u16)M2C_FIELD(arg0, s16 *, 0x1E);
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16)temp_v0_2;
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16)(temp_v0_2 % 0x1000);
    M2C_FIELD(arg0, u16 *, 0x20) =
        (u16)(M2C_FIELD(arg0, u16 *, 0x20) + 4);
    M2C_FIELD(arg1, s16 *, 2) =
        (s16)(M2C_FIELD(arg0, u16 *, 6) +
        ((s32)((func_800644B8((s16)M2C_FIELD(arg0, u16 *, 0x1C)) >> 4) *
        (s16)M2C_FIELD(arg0, u16 *, 0x20)) >> 8));
    M2C_FIELD(arg1, s16 *, 6) =
        (s16)(M2C_FIELD(arg0, u16 *, 0xA) +
        ((s32)((func_80064584((s16)M2C_FIELD(arg0, u16 *, 0x1C)) >> 4) *
        (s16)M2C_FIELD(arg0, u16 *, 0x20)) >> 8));
    M2C_FIELD(arg2, s16 *, 0x1A) =
        (s16)((s32)(0 - ((func_80064584(
        (s16)M2C_FIELD(arg0, u16 *, 0x1C) -
        temp_s3[100]) >> 4) << 8)) >> 8);
    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_8003DB94(arg2, D_800DEAE0, 0);
    }
}
