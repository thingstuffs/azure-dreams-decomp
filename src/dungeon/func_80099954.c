#include "common.h"

extern void func_8009EEAC(void);
extern void func_8009F3D4(u8, u8, s32, s32, s32);

extern u8 *D_800E3D7C[3];

void func_8009F0B4(void)
{
    u8 *node;
    u8 *owner;
    s32 count;

    node = D_800E3D7C[0];
    func_8009EEAC();
    count = 0;
    while ((node = *(u8 **)(node + 0x5C) + 0x20) != D_800E3D7C[0]) {
        if (*(s8 *)(node + 0x13) > 0) {
            owner = *(u8 **)(node - 0x14);
            func_8009F3D4(owner[0x24], owner[0x25], 0x202080, 4,
                          count++);
        }
    }
}
