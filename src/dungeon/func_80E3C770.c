#include "common.h"

typedef s32 M2C_UNK;

#define U8_AT(p, off)  (*(u8 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))

extern s32 D_80045340;
extern s32 D_800814A0;
extern M2C_UNK D_800C6AEC;

extern void func_8004491C();
extern void func_80044A50();
extern void func_800478B8();
extern void func_800BC318();

void func_80175F70(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 *base;

    switch (S16_AT(arg0, 0x1E)) {
    case 0:
        U8_AT(arg2, 0xF)++;
        U8_AT(arg2, 0xC) += (0x80 - U8_AT(arg2, 0xC)) / U8_AT(arg2, 0xF);
        U8_AT(arg2, 0xD) += (0x80 - U8_AT(arg2, 0xD)) / U8_AT(arg2, 0xF);
        U8_AT(arg2, 0xE) += (0x80 - U8_AT(arg2, 0xE)) / U8_AT(arg2, 0xF);
        if (U8_AT(arg2, 0xF) < 8) {
            break;
        }
        U32_AT(arg2, 0xC) = 0x00808080;
        goto advance_state;

    case 1:
        U8_AT(arg2, 0xF)--;
        if (U8_AT(arg2, 0xF) != 0) {
            break;
        }
        base = arg0 - 0x20;
        func_80044A50(base);
        U16_AT(arg2, 0x12) += 0x80;
        U16_AT(arg2, 0x14) &= 0xFFF3;
        func_8004491C(base, &D_80045340);
        goto advance_state;

    case 2:
        if (**(u8 **)(arg0 + 4) != 0x14) {
            break;
        }
        base = arg0 - 0x20;
        func_80044A50(base);
        U16_AT(arg2, 0x12) -= 0x80;
        U16_AT(arg2, 0x14) |= 0xC;
        func_8004491C(base, &D_800C6AEC);
        U8_AT(arg2, 0xF) = 0;
advance_state:
        U16_AT(arg0, 0x1E)++;
        break;

    case 3:
        if (U8_AT(arg2, 0xF) < 8) {
            U8_AT(arg2, 0xF)++;
            U8_AT(arg2, 0xC) = U8_AT(arg2, 0xD) =
                U8_AT(arg2, 0xE) += -U8_AT(arg2, 0xE) / U8_AT(arg2, 0xF);
        } else {
            U16_AT(arg0, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_800BC318(arg0 - 0x20);
        }
        break;
    }

    func_800478B8(arg2);
}
