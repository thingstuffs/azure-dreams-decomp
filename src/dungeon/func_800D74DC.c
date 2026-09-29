#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

extern Template0 D_8002E5D8;
extern Vec3 D_8002E5E8;

/* Initialize nine records and vectors from templates, setting each record's last byte to 4. */
void func_800DCC3C(u8 *object) {
    s32 i;

    for (i = 0; i < 9; i++) {
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4)) = D_8002E5D8.unk0;
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4) + 4) = D_8002E5D8.unk4;
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4) + 8) = D_8002E5D8.unk8;
        *(s32 *)(i * 0x10 + *(s32 *)(object + 4) + 0xC) = D_8002E5D8.unkC;
        *(u8 *)(i * 0x10 + *(s32 *)(object + 4) + 0xF) = 4;
        *(s32 *)(i * 0xC + *(s32 *)(object + 8)) = D_8002E5E8.x;
        *(s32 *)(i * 0xC + *(s32 *)(object + 8) + 4) = D_8002E5E8.y;
        *(s32 *)(i * 0xC + *(s32 *)(object + 8) + 8) = D_8002E5E8.z;
    }
}
