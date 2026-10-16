#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FC64(M2C_UNK, s16 *, s32, s32);      /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80169978;

void *func_80169F60(void *arg0, void *arg1, void *arg2) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    u16 sp28;
    u16 sp2A;
    u16 sp2C;
    s16 *temp_a1_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    void *temp_a0;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_a2 = M2C_FIELD(arg1, s32 *, 8);
    temp_a3 = M2C_FIELD(arg1, s32 *, 0xC);
    sp10 = M2C_FIELD(arg1, s32 *, 0);
    sp14 = M2C_FIELD(arg1, s32 *, 4);
    sp18 = temp_a2;
    sp1C = temp_a3;
    sp20 = M2C_FIELD(arg1, s32 *, 0x10);
    sp24 = M2C_FIELD(arg1, s32 *, 0x14);
    temp_a1 = ((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 8) & 0xE;
    unksp12 += (*(temp_a1 + &D_8006CCD8) * M2C_FIELD(arg0, s16 *, 0xB2)) << 6;
    temp_a1_2 = temp_a1 + &D_8006CCE8;
    unksp16 += (*temp_a1_2 * M2C_FIELD(arg0, s16 *, 0xB2)) << 6;
    temp_v0 = func_8003FC64(0x312, temp_a1_2, temp_a2, temp_a3);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80169978;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x10) | 0x20);
        func_80047784(temp_a0, 0x47, 0);
        temp_s2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v0, s32 *, 0x24) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_v0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v0, s32 *, 0x34) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(temp_v0, s32 *, 0x38) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        temp_s0 = temp_v0 + 0x20;
        sp2C = 0;
        sp2A = 0;
        sp28 = 0;
        if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp28, 1) != 0) {
            temp_v0_2 = M2C_FIELD(temp_s0, u16 *, 6) + sp28;
            M2C_FIELD(temp_s0, u16 *, 6) = temp_v0_2;
            M2C_FIELD(temp_s2, u16 *, 2) = temp_v0_2;
            temp_v0_3 = M2C_FIELD(temp_s0, u16 *, 0xA) + sp2A;
            M2C_FIELD(temp_s0, u16 *, 0xA) = temp_v0_3;
            M2C_FIELD(temp_s2, u16 *, 6) = temp_v0_3;
            temp_v0_4 = M2C_FIELD(temp_s0, u16 *, 0xE) + sp2C;
            M2C_FIELD(temp_s0, u16 *, 0xE) = temp_v0_4;
            M2C_FIELD(temp_s2, u16 *, 0xA) = temp_v0_4;
        }
        M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) ((s32) (sp10 - M2C_FIELD(temp_s0, s32 *, 4)) / 32);
        M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) ((s32) (sp14 - M2C_FIELD(temp_s0, s32 *, 8)) / 32);
        return temp_v0;
    }
    return NULL;
}
