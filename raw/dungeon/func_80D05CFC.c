#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, M2C_UNK *, M2C_UNK); /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, void *, void *); /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DDC40;
extern M2C_UNK D_80152DC4;
extern M2C_UNK D_80157EB4;
extern M2C_UNK D_80157EBC;

void func_801534FC(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp10;
    s32 temp_t0;
    u16 var_v0;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v1;
    void *var_a2;
    void *var_a3;

    if (((M2C_FIELD(arg3, void **, 0x60) != NULL) || (M2C_FIELD(arg3, s8 *, 0x72) < 0)) && (temp_v0 = func_8003FD64(0x112, &D_80083498), temp_v1 = temp_v0 + 0x20, (temp_v0 != NULL))) {
        M2C_FIELD(temp_v1, s16 *, 0x96) = 0xA;
        M2C_FIELD(temp_v1, s16 *, 0x9E) = 0xA;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80152DC4;
        var_a2 = arg2;
        M2C_FIELD(temp_v1, u16 *, 0x94) = (u16) M2C_FIELD(arg3, u16 *, 0x2A);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_t0 = var_a2 + 0x30;
        var_a3 = temp_s0;
        do {
            M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
            M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
            M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
            M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != temp_t0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) & 0xFFF3);
        func_8004491C(temp_v0, &D_80045340, var_a2, var_a3);
        M2C_FIELD(temp_s0, M2C_UNK **, 0x2C) = &D_80157EB4;
        func_80047784(temp_s0, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157EB4), 0);
        temp_a1 = M2C_FIELD(arg3, void **, 0x60);
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
        if ((temp_a1 != NULL) && !(M2C_FIELD(arg3, s32 *, 0x14) & 0x04000000)) {
            temp_a1_2 = M2C_FIELD(temp_a1, void **, -0x18);
            M2C_FIELD(temp_s0_2, s16 *, 2) = (s16) (M2C_FIELD(temp_a1_2, u16 *, 2) - (*((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_80157EBC) * 0x10));
            M2C_FIELD(temp_s0_2, s16 *, 6) = (s16) (M2C_FIELD(temp_a1_2, u16 *, 6) - (M2C_FIELD(((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_80157EBC), s16 *, 2) * 0x10));
            M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a1_2, u16 *, 0xA) - ((u8) *(M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u8 *, 0x13) + &D_800DDC40) >> 1));
            return;
        }
        if (M2C_FIELD(arg3, s8 *, 0x72) < 0) {
            M2C_FIELD(arg3, s8 *, 0x72) = (s8) -(s8) (u8) M2C_FIELD(arg3, s8 *, 0x72);
            if (M2C_FIELD(arg3, s8 *, 0x73) < 0) {
                M2C_FIELD(arg3, s8 *, 0x73) = (s8) -(s8) (u8) M2C_FIELD(arg3, s8 *, 0x73);
            }
            M2C_FIELD(temp_s0_2, s16 *, 2) = (s16) ((M2C_FIELD(arg3, s8 *, 0x72) << 6) + 0x20);
            M2C_FIELD(temp_s0_2, s16 *, 6) = (s16) ((M2C_FIELD(arg3, s8 *, 0x73) << 6) + 0x20);
            M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
            temp_a1_3 = M2C_FIELD(arg0, void **, -0x14);
            if (func_8003DE58(M2C_FIELD(temp_a1_3, s32 *, 8), temp_a1_3, &sp10, 0) != 0) {
                var_v0 = M2C_FIELD(temp_s0_2, u16 *, 0xA) + sp14;
            } else {
                var_v0 = M2C_FIELD(temp_s0_2, u16 *, 0xA) - 0x28;
            }
            M2C_FIELD(temp_s0_2, u16 *, 0xA) = var_v0;
        }
    }
}
