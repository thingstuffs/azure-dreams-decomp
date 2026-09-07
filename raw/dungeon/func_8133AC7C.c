#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern s32 D_80083780[3];
extern s32 D_801717A8;
extern PackedVec D_80173B40;
extern void *D_80175D60;

void func_80171C7C(void) {
    s32 *temp_v1;
    void *temp_a0;
    void *temp_a3;
    void *temp_v0;
    u16 temp_flags;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != 0) {
        FIELD(temp_v0, s16, 0x38) = 0;
        FIELD(temp_v0, s32 *, 0x10) = &D_801717A8;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a3, s16, 6) = 0;
        temp_a0 = FIELD(temp_v0, void *, 8);
        temp_v1 = D_80083780;
        FIELD(temp_a0, s32, 0) = FIELD(temp_v1, s32, 0);
        FIELD(temp_a0, s32, 4) = FIELD(temp_v1, s32, 4);
        FIELD(temp_a0, s32, 8) = FIELD(temp_v1, s32, 8);
        temp_a3 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a3, s16, 0x1E) = 0x1000;
        FIELD(temp_a3, s16, 0x1C) = 0x1000;
        FIELD(temp_a3, u8, 0xE) = 0x80;
        FIELD(temp_a3, u8, 0xD) = 0x80;
        FIELD(temp_a3, u8, 0xC) = 0x80;
        temp_flags = FIELD(temp_a3, u16, 0x14);
        D_80175D60 = temp_v0;
        FIELD(temp_a3, u16, 0x14) = temp_flags | 0x80;
        FIELD(temp_v0, PackedVec, 0x48) = D_80173B40;
        FIELD(temp_a3, void *, 8) = (u8 *)temp_v0 + 0x48;
    }
}
