#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u8 pad_4[8];
    s32 field_C;
} Unk83780;

extern s32 func_800C2AE8(void *);
extern void func_80093CEC(void *);

extern u16 D_80026F24[];
extern s16 D_800272C8;
extern s16 D_800272CA;
extern u16 D_80082E94;
extern u8 D_80083160[];
extern Unk83780 D_80083780;
extern s32 D_8008378C;
extern u8 D_800D00C0[];
extern u8 D_800D0128[];

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80023994(void *arg0, void *arg1)
{
    u8 *button_base;
    s32 result;

    button_base = D_80083160;
    result = (s16)func_800C2AE8(arg1);
    if (D_800272CA > 0) {
        D_800272CA--;
        D_80083780.field_C -= D_80083780.field_C >> 1;
        goto tail;
    }

    {
        s16 index;
        u16 selected;
        s32 buttons;
        u8 *record_base;

        record_base = (u8 *)&D_80083780;
        index = D_800272C8;
        selected = D_80026F24[index];
        buttons = FIELD(button_base, s32, 0x10);

        FIELD(record_base, s32, 0xC) = 0;
        FIELD(record_base, u16, 0x2) = selected;
        if ((buttons & 0x8000) && index != 0) {
            D_800272C8--;
            FIELD(record_base, s32, 0xC) = (s32)0xFFD00000;
            D_800272CA = 3;
            func_80093CEC(D_800D00C0);
            goto tail;
        }
    }
    if ((FIELD(button_base, s32, 0x10) & 0x2000) && D_800272C8 < 2) {
        D_800272C8++;
        D_8008378C = 0x300000;
        D_800272CA = 3;
        func_80093CEC(D_800D00C0);
        goto tail;
    }
    if (D_80082E94 & 0x6000) {
        func_80093CEC(D_800D0128);
    }

tail:
    FIELD(arg1, s32, 0x14) += 0x1D000;
    if (result < FIELD(arg1, s16, 0xA)) {
        FIELD(arg1, s16, 0xA) = result;
        FIELD(arg1, s32, 0x14) = 0;
    }
}
