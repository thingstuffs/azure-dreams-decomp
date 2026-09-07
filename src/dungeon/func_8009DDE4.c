#include "common.h"

typedef struct {
    u8 pad0[0x11];
    u8 kind;
    u8 pad12[2];
} DungeonEntry;

extern DungeonEntry D_8006DE24[];

s16 func_800A3544(u8 *arg0, u8 arg1) {
    s32 i = 0;
    DungeonEntry *base = D_8006DE24;

    for (; i < 3; i++, arg0 += 3) {
        u8 index = arg0[8];

        if (index != 0) {
            u32 offset = index * sizeof(DungeonEntry);
            register DungeonEntry *entry ASM_REG("$3") =
                (DungeonEntry *)(offset + (u32)base);

            if (entry->kind == arg1) {
                return i;
            }
        }
    }
    return -1;
}
