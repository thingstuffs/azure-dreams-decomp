#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_800A5D3C(void);
extern u16 D_80013714;
extern u8 D_80082E80[];
extern s32 D_800E296C[];
extern void *D_800E3D7C;

s32 func_800A5C70(void) {
    u16 buttons;
    u8 *coords;
    void **cursor_addr;
    void *cursor;
    void *start;
    void *other;

    cursor_addr = &D_800E3D7C;
    do {
        buttons = D_80013714;
    } while (0);
    cursor = *cursor_addr;
    if (buttons & 2) {
        return 1;
    }
    if (buttons & 9) {
        func_800A5D3C();
        return 0;
    }
    if (D_800E296C[0] & 0x200000) {
        return 0;
    }

    coords = D_80082E80;
    start = cursor;
    do {
        if (!(FIELD(cursor, s32, 0x1C) & 0x2208)) {
            register s32 delta ASM_REG("$2");

            other = FIELD(cursor, void *, -0x14);
            ASM_KEEP(other);
            delta = FIELD(coords, u8, 0x24);
            ASM_KEEP(delta);
            delta -= FIELD(other, u8, 0x24);
            if (delta < 0) {
                delta = -delta;
            }
            if (delta < 5) {
                delta = FIELD(coords, u8, 0x25);
                ASM_KEEP(delta);
                delta -= FIELD(other, u8, 0x25);
                if (delta < 0) {
                    delta = -delta;
                }
                if (delta < 5) {
                    return 0;
                }
            }
        }
        cursor = (u8 *)FIELD(cursor, void *, 0x5C) + 0x20;
    } while (cursor != start);

    return 1;
}
