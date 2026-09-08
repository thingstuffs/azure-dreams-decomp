#include "common.h"

extern void func_8001F354(s32, s32, s32, void *);
extern void func_8004E634(s16, u8 *);

extern s32 D_80012090[];
extern void *D_8001F5B4[];
extern u8 D_80077DE8[];
extern u8 D_80077E00[];
extern s16 D_8008146C;

void func_8001F450(void)
{
    u8 result[2];
    u8 *p;
    void *special;
    s32 mode;
    register s16 x ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    s32 y;
    s32 sentinel;
    u8 value;
    special = 0;
    if (*(s32 *)0x80012090 != 2) {
        if (D_8008146C == 0x28) {
            special = D_80077E00;
        }
        mode = 0;
    } else {
        mode = 1;
    }

    if (special != 0) {
        func_8001F354(0xAA, 0x78, 0, special);
        return;
    }

    func_8001F354(0xAA, 0x78, mode, D_80077DE8);
    p = result;
    func_8004E634(D_8008146C, p);

    x = 0xC8;
    if (result[1] == 0) {
        x = 0xDA;
    }

    if (result[0] != 0) {
        sentinel = 0x20;
        y = 0x780000;
        do {
            value = *p;
            if (value != sentinel) {
                func_8001F354(x, y >> 16, mode, D_8001F5B4[value]);
            }
            p++;
            x += 0x12;
        } while (*p != 0);
    }
}
