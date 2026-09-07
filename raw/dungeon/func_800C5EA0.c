#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 fieldA;
    void *fieldC;
    void *field10;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_8008346C;
extern s32 D_800814A0[3];

void func_8009A028(void *arg0);
void func_800CB818(void);

void func_800CB600(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    s8 value;
    s32 product;
    s32 phase;
    s16 temp_a0_value;
    s16 temp_v0_4;
    s16 temp_v0_5;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 temp_v1_4;
    void *temp_a0;
    D_80083460_t *state;

    temp_v0 = FIELD(arg0, u16, 0x94) + 1;
    FIELD(arg0, u16, 0x94) = temp_v0;
    if ((s16)temp_v0 >= 0x41) {
        FIELD(arg0, u16, 0x94) = 0x40;
    }

    product = FIELD(arg0, s16, 0x94) * 2;
    product *= FIELD(arg0, u8, 0x9D) & 1;
    value = (u8)FIELD(arg0, u16, 0x94) + product;
    FIELD(arg2, s8, 0xC) = value;
    FIELD(arg2, s8, 0xE) = value;
    FIELD(arg2, s8, 0xD) = value;

    phase = FIELD(arg0, u8, 0x9A);
    FIELD(arg0, u8, 0x9D) = FIELD(arg0, u8, 0x9D) + 1;
    if (phase == 0) {
        temp_v0 = FIELD(arg0, u16, 0x8A) - 8;
        FIELD(arg0, u16, 0x8A) = temp_v0;
        if ((s16)temp_v0 < -0x80) {
            FIELD(arg0, s16, 0x8A) = -0x80;
        }

        FIELD(arg1, s16, 0xA) =
            (s16)(FIELD(arg0, u16, 0x92) + FIELD(arg0, u16, 0x8A));

        temp_v1_2 = FIELD(arg2, u16, 0x1C);
        temp_a0_value = FIELD(arg0, s16, 0x96);
        temp_v1_3 = temp_v1_2 + ((0x1000 - temp_v1_2) / temp_a0_value);
        FIELD(arg2, u16, 0x1C) = temp_v1_3;
        FIELD(arg2, u16, 0x1E) = temp_v1_3;

        temp_v0 = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = temp_v0;
        if ((s16)temp_v0 > 0) {
            return;
        }

        state = &D_80083460;
        FIELD(arg0, u16, 0x96) = 0;
        if (state->fieldC != 0) {
            return;
        }
        if (state->field10 != 0) {
            return;
        }
        if (state->flags & 8) {
            return;
        }

        state->fieldC = arg0;
        FIELD(arg0, u16, 0x98) |= 0x80;
        FIELD(arg0, u8, 0x9A)++;
        func_800CB818();
        return;
    }

    if (phase == 1) {
        if (D_8008346C != 0) {
            return;
        }

        func_8009A028(arg0);
        temp_a0 = (u8 *)arg0 - 0x20;
        FIELD(temp_a0, s32, 0x10) |= 0x80000000;
        FIELD(arg0, u16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9A)++;
        func_800CB818();
        return;
    }

    temp_v1_4 = FIELD(arg2, u16, 0x1C);
    temp_v0_4 = FIELD(arg0, s16, 0x96);
    temp_v0_5 = temp_v1_4 / temp_v0_4;
    temp_v1_4 -= temp_v0_5;
    FIELD(arg2, u16, 0x1C) = temp_v1_4;
    FIELD(arg2, u16, 0x1E) = temp_v1_4;

    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0;
    if ((s16)temp_v0 > 0) {
        return;
    }

    D_80083460.fieldA--;
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
