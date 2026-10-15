#include "modules/dungeon_ovl_188298c.h"

void func_80024060(s32 x, s32 y, void *kind, s32 flags) {
    u8 *actor = D_800E3D7C;
    x = (s16)x;
    y = (s16)y;
    flags = ((u8)flags >> 2) + 0x10;
    do {
        if ((s16)func_800A2CB8(kind, actor) != 0) {
            u8 *header = *(u8 **)(actor - 0x14);
            if (abs(header[0x24] - x) < 3 && abs(header[0x25] - y) < 3 && (s16)func_800A41F0(actor) != 0) {
                s32 amount = flags + (func_800A6D30() & 3);
                s32 mode = 0x10;
                if (D_800E3D68 == 0xFF) mode = 0xFF;
                func_800C87C4(actor, mode, amount);
            }
        }
        actor = *(u8 **)(actor + 0x5C) + 0x20;
    } while (actor != D_800E3D7C);
}
