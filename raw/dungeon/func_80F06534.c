#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800AAA54(void *, void *, void *, M2C_UNK); /* extern */
M2C_UNK func_800AD4D0(void *);                      /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_8014DCE8;

void func_8014FD34(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u16 var_v1;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800AD4D0(arg3);
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        if (M2C_FIELD(arg3, u8 *, 0x28) != 0) {
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0U;
                M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
                return;
            }
            var_v1 = -1U;
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x228) {
                var_v1 = 8;
            }
            M2C_FIELD(arg0, u16 *, 0x96) = var_v1;
        case 1:
            if ((s16) M2C_FIELD(arg0, u16 *, 0x96) > 0) {
                M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
            } else if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            }
            if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0) {
                if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
                    goto block_18;
                }
                M2C_FIELD(arg0, u16 *, 0x96) = 1U;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                return;
            }
            return;
        }
block_18:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800AAA54(arg0, arg1, arg2, 0);
        return;
    case 2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
                M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
            }
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014DCE8;
        }
        break;
    }
}
