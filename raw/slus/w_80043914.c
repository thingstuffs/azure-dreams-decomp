#include "common.h"

typedef struct {
    u8 pad_0x00[0x48];
    u8 field_0x48;
    u8 pad_0x49[0x8C - 0x49];
} S_800E3E48;

typedef struct {
    u8 field_0x00;
    u8 pad_0x01[2];
    u8 field_0x03;
} S_80043914_Arg;

extern S_800E3E48 D_800E3E48[];
extern u8 D_800E2968[16];

void func_80043914(S_80043914_Arg *a0)
{
    register S_80043914_Arg *a1 ASM_REG("$5") = a0;

    if (a1->field_0x00 == 0x16) {
        S_800E3E48 *base = D_800E3E48;
        u8 v = base[a1->field_0x03 & 0x1F].field_0x48;
        register u8 out ASM_REG("$2");

        if (v == 0xD) {
            out = 0xF;
        } else if (v == 0xF) {
            out = 0xA;
        } else {
            return;
        }
        D_800E2968[0] = out;
    }
}
