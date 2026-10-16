#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800AAA54(void *, void *, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AD4D0(void *);                      /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016C4BC;
extern M2C_UNK D_8016FE3C;
extern M2C_UNK D_8016FE44;
extern M2C_UNK D_8016FE4C;

void func_8016EC44(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a0_3;
    s16 temp_v0;
    u16 temp_v0_2;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_800AD4D0(arg3);
        M2C_FIELD(arg0, s16 *, 0x96) = 6;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            temp_a0 = M2C_FIELD(arg3, u8 *, 0x48);
            switch (temp_a0) {                      /* switch 2; irregular */
            case 15:                                /* switch 2 */
block_28:
                func_800AAA54(arg0, arg1, arg2, &D_8016FE4C);
                return;
            case 14:                                /* switch 2 */
            case 14:                                /* switch 3 */
                func_800AAA54(arg0, arg1, arg2, &D_8016FE44);
                return;
            }
        } else {
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                M2C_FIELD(arg0, s16 *, 0x96) = 0;
                M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
                return;
            }
            return;
        }
        break;
    case 1:                                         /* switch 1 */
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
        if (temp_v0 > 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCD8) << 0x12);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCE8) << 0x12);
            return;
        }
        if (temp_v0 == 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCD8) << 0x12);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCE8) << 0x12);
            M2C_FIELD(arg0, s16 *, 0x96) = 0xC;
block_33:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 2:                                         /* switch 1 */
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            temp_a0_2 = M2C_FIELD(arg3, u8 *, 0x48);
            switch (temp_a0_2) {                    /* switch 3; irregular */
            case 15:                                /* switch 3 */
                goto block_28;
            }
        } else {
            temp_a0_3 = M2C_FIELD(arg0, s16 *, 0x96);
            if (temp_a0_3 != 0) {
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / temp_a0_3);
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
            }
            temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96);
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) (temp_v0_2 - 1);
            if ((temp_v0_2 << 0x10) <= 0) {
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                goto block_33;
            }
        }
        break;
    case 3:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
            M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016C4BC;
        break;
    }
    /* bug: did not emit code for node #21; contents below: */
    /* bug: did not emit code for node #22; contents below: */
    /* bug: did not emit code for node #25; contents below: */
    func_800AAA54(arg0, arg1, arg2, &D_8016FE3C);
}
