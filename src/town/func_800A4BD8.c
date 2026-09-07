#include "common.h"

typedef struct TownObject {
    void (*callback)(void);
    s8 pad_04[0x3C];
    u8 *field_40;
} TownObject;

extern s32 D_800814A0[];
extern u8 D_80083160[0xAB];
extern void func_800A23C0(void) __attribute__((noreturn));

void func_800A2338(TownObject *arg0, s32 arg1, u8 *arg2) {
    u8 *ptr;

    ptr = arg0->field_40;
    if (ptr != 0) {
        if (*ptr == 0) {
            ((u16 *)arg0)[-1] |= 0x8000;
            D_800814A0[0] |= 0x8000;
            func_800A23C0();
        }
    }

    arg2[0xC] = D_80083160[0xA8];
    arg2[0xD] = D_80083160[0xA9];
    arg2[0xE] = D_80083160[0xAA];
    arg0->callback();
}
