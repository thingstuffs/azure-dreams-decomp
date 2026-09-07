#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

extern s32 func_80033BC0();
extern void *func_8003FC64();
extern M2C_UNK func_80041284();
extern M2C_UNK func_8004491C();
extern s16 func_800BCA68();
extern u8 D_80045C34[]; /* overlays/dungeon/first_pass_matched/func_80D403A8.c */
extern M2C_UNK D_800F62BC;
extern M2C_UNK D_800F6F28;
extern M2C_UNK D_800F6F30;

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))
#define VFIELD(expr, type, offset) (*(volatile type *)((s8 *)(expr) + (offset)))

void func_800F63D0(void) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    if (func_80033BC0(0xA2) == 0) {
        func_80041284(&D_800F6F28);
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            FIELD(temp_v0, M2C_UNK *, 0x10) = &D_800F62BC;
            func_8004491C(temp_v0, &D_80045C34);
            temp_s0 = FIELD(temp_v0, void *, 8);
            FIELD(temp_s0, u16, 2) = 0x820;
            FIELD(temp_s0, s16, 6) = 0x820;
            FIELD(temp_s0, s16, 0xA) = func_800BCA68(VFIELD(temp_s0, u16, 2), 0x820);
            temp_v1 = FIELD(temp_v0, void *, 0xC);
            FIELD(temp_v1, s16, 0x1E) = 0x1000;
            FIELD(temp_v1, s16, 0x1C) = 0x1000;
            FIELD(temp_v1, M2C_UNK *, 8) = &D_800F6F30;
            FIELD(temp_v1, s16, 0x10) = 0x20;
            FIELD(temp_v1, s16, 0x14) = 0xC;
            FIELD(temp_v1, s16, 6) = 6;
        }
    }
}
