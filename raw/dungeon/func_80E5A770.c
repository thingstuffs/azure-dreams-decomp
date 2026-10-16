#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80044A50(void *);                      /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
M2C_UNK func_800BC318(void *);                      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800C6AEC;

void func_80157F70(void *arg0, void *arg2) {
    s16 temp_v1;
    u8 temp_a2;
    u8 temp_a3;
    u8 temp_t0;
    u8 temp_v0;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    void *temp_s0;
    void *temp_s0_2;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1E);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_t0 = M2C_FIELD(arg2, u8 *, 0xC);
        M2C_FIELD(arg2, u8 *, 0xF) = (u8) (M2C_FIELD(arg2, u8 *, 0xF) + 1);
        temp_a3 = M2C_FIELD(arg2, u8 *, 0xD);
        temp_a2 = M2C_FIELD(arg2, u8 *, 0xE);
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) (temp_t0 + ((s32) (0x80 - temp_t0) / (s32) M2C_FIELD(arg2, u8 *, 0xF)));
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_a3 + ((s32) (0x80 - temp_a3) / (s32) M2C_FIELD(arg2, u8 *, 0xF)));
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_a2 + ((s32) (0x80 - temp_a2) / (s32) M2C_FIELD(arg2, u8 *, 0xF)));
        if ((u8) M2C_FIELD(arg2, u8 *, 0xF) >= 8U) {
            M2C_FIELD(arg2, u8 *, 0xC) = 0x808080;
block_13:
            M2C_FIELD(arg0, s16 *, 0x1E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1E) + 1);
        }
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg2, u8 *, 0xF) - 1;
        M2C_FIELD(arg2, u8 *, 0xF) = temp_v0;
        temp_s0 = arg0 - 0x20;
        if (!(temp_v0 & 0xFF)) {
            func_80044A50(temp_s0);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) + 0x80);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFF3);
            func_8004491C(temp_s0, &D_80045340);
            goto block_13;
        }
        break;
    case 2:
        temp_s0_2 = arg0 - 0x20;
        if (*M2C_FIELD(arg0, u8 **, 4) == 0x14) {
            func_80044A50(temp_s0_2);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            func_8004491C(temp_s0_2, &D_800C6AEC);
            M2C_FIELD(arg2, u8 *, 0xF) = 0U;
            goto block_13;
        }
        break;
    case 3:
        temp_v1_2 = M2C_FIELD(arg2, u8 *, 0xF);
        if (temp_v1_2 < 8U) {
            temp_v1_3 = M2C_FIELD(arg2, u8 *, 0xE);
            M2C_FIELD(arg2, u8 *, 0xF) = (u8) (temp_v1_2 + 1);
            temp_v1_4 = temp_v1_3 + ((s32) -(s32) temp_v1_3 / (s32) M2C_FIELD(arg2, u8 *, 0xF));
            M2C_FIELD(arg2, u8 *, 0xE) = temp_v1_4;
            M2C_FIELD(arg2, u8 *, 0xD) = temp_v1_4;
            M2C_FIELD(arg2, u8 *, 0xC) = temp_v1_4;
        } else {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
            func_800BC318(arg0 - 0x20);
        }
        break;
    }
    func_800478B8(arg2);
}
