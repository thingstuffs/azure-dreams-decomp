#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    u8 unk00[6];
    s16 field_06;
    u8 unk08[4];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 unk0F;
    s16 field_10;
    u8 unk12[2];
    u16 flags_14;
    u8 unk16[6];
    s16 field_1C;
    s16 field_1E;
} Sub;

typedef struct {
    u8 unk00[8];
    Vec3 *position;
    Sub *sub;
    M2C_UNK *callback;
} Node;

extern void func_8003DB94(Sub *, M2C_UNK *, s32);
extern Node *func_8003FC64(s32);
extern void func_8004491C(Node *, M2C_UNK *);
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80170D60;

void func_80170DCC(void *unused, void *arg1) {
    Node *temp_v0;
    Sub *temp_a0;
    Vec3 *temp_a0_2;
    Sub *temp_a0_3;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v0->callback = &D_80170D60;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = temp_v0->sub;
        temp_a0->field_10 = 0x20;
        temp_a0->field_06 = 6;
        temp_a0->flags_14 |= 0xC;
        temp_a0_2 = temp_v0->position;
        temp_a0_2->x = ((Vec3 *)arg1)->x + 0x180000;
        temp_a0_2->y = ((Vec3 *)arg1)->y;
        temp_a0_2->z = ((Vec3 *)arg1)->z + 0xFFF00000;
        temp_a0_3 = temp_v0->sub;
        temp_a0_3->field_1E = 0x1400;
        temp_a0_3->field_1C = 0x1400;
        temp_a0_3->field_0E = 0x80;
        temp_a0_3->field_0D = 0x80;
        temp_a0_3->field_0C = 0x80;
        func_8003DB94(temp_a0_3, &D_800DE870, 0);
    }
}
