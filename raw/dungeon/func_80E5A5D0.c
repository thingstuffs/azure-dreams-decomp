#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, s16);         /* extern */
void *func_8003FD64(M2C_UNK, s32);                  /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK, void *); /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80157C60;
extern M2C_UNK D_80157D74;

void func_80157DD0(void *arg0, void *arg1, void *arg2, s16 arg3) {
    u16 sp10;
    s16 temp_v1_2;
    s32 temp_v1;
    void *temp_a3;
    void *temp_s1;
    void *temp_v0;

    if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp10, arg3) != 0) {
        temp_v0 = func_8003FD64(0x300, arg0 - 0x20);
        if ((temp_v0 != NULL) && ((temp_s1 = M2C_FIELD(temp_v0, void **, 0xC), temp_a3 = M2C_FIELD(temp_v0, void **, 8), M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80157C60, M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x400, M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x400, M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080, M2C_FIELD(temp_s1, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28), M2C_FIELD(temp_a3, s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 2) + sp10), M2C_FIELD(temp_a3, s16 *, 6) = (s16) (M2C_FIELD(arg1, u16 *, 6) + sp12), M2C_FIELD(temp_a3, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) + sp14), temp_v1 = ((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 8) & 0xE, M2C_FIELD(temp_a3, u16 *, 0xE) = (u16) *(temp_v1 + &D_8006CCD8), M2C_FIELD(temp_a3, u16 *, 0x12) = (u16) *(temp_v1 + &D_8006CCE8), M2C_FIELD(temp_v0, s16 *, 0x40) = 0x10, M2C_FIELD(temp_v0, s16 **, 0x20) = (s16 *) (arg0 + 0x2A), func_80047784(temp_s1, 0x45, 0, temp_a3), func_8004491C(temp_v0, &D_80157D74), temp_v1_2 = ((((s32) (*(s16 *)0x80083228 + *M2C_FIELD(temp_v0, s16 **, 0x20) + 0x100) >> 9) & 7) + 2) << 9, M2C_FIELD(temp_s1, s16 *, 0x18) = temp_v1_2, (temp_v1_2 == 0x400)) || (temp_v1_2 == 0xC00))) {
            M2C_FIELD(temp_s1, s16 *, 0x18) = (s16) (temp_v1_2 + 0x100);
        }
    }
}
