#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

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
    void *position;
    Sub *sub;
    M2C_UNK *callback;
} Node;

M2C_UNK func_8003DB94();
Node *func_8003FC64();
M2C_UNK func_8004491C();

extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DE870[3];
extern M2C_UNK D_800DEDB0[3];
extern M2C_UNK D_80170D60[3];

void func_80172CC8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Sub *temp_a0;
    Sub *temp_a0_2;
    Node *temp_v0;
    void *temp_v1;
    s32 word_08;
    u16 x;
    u16 y;
    u16 z;
    register s32 flag ASM_REG("$21");

    flag = arg4;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v0->callback = D_80170D60;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = temp_v0->sub;
        temp_a0->field_10 = 0x20;
        temp_a0->field_06 = 6;
        temp_a0->flags_14 |= 0xC;
        temp_v1 = temp_v0->position;
        M2C_FIELD(temp_v1, s32 *, 0) = M2C_FIELD(arg0, s32 *, 0);
        M2C_FIELD(temp_v1, volatile s32 *, 4) = M2C_FIELD(arg0, s32 *, 4);
        x = M2C_FIELD(temp_v1, u16 *, 2);
        word_08 = M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16)(x + arg1);
        y = M2C_FIELD(temp_v1, u16 *, 6);
        M2C_FIELD(temp_v1, s32 *, 8) = word_08;
        z = M2C_FIELD(temp_v1, u16 *, 0xA);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16)(y + arg2);
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16)(z + arg3);
        temp_a0_2 = temp_v0->sub;
        temp_a0_2->field_1E = 0x1400;
        temp_a0_2->field_1C = 0x1400;
        temp_a0_2->field_0E = 0x80;
        temp_a0_2->field_0D = 0x80;
        temp_a0_2->field_0C = 0x80;
        if ((flag << 0x10) == 0) {
            func_8003DB94(temp_a0_2, D_800DE870, 0);
        } else {
            func_8003DB94(temp_a0_2, D_800DEDB0, 0);
        }
        ASM_KEEP(flag);
    }
}
