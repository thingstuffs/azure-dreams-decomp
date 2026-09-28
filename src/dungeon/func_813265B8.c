#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern s32 D_80174704[3];

extern void func_8009FAC4(void);
extern void func_8016E264(void);

/* Leave the map screen: clear the three display flags and tear the screen down. */
void func_8016DDB8(void) {
    u8 *ptr;
    u16 *h = ((u16 *)&D_80013714);

    ptr = (u8 *)(D_80174704[0] + 0x20);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    D_800E296C &= 0xF7FFFFFF;
    h[0] &= 0xFFF6;
    func_8009FAC4();
    func_8016E264();
}
