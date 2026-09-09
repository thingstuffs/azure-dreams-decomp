#include "common.h"

extern void func_8009EEAC(s32, s32, s32, s32);
extern void func_8009F3D4(u8, u8, s32, s32, s32);

extern u8 *D_800E3D7C[3];

/* Create red markers at the owner positions of active list entries. */
void func_8009F0B4(s32 setup_arg_0, s32 setup_arg_1, s32 setup_arg_2, s32 setup_arg_3)
{
    u8 *node;
    u8 *owner;
    s32 marker_count;

    node = D_800E3D7C[0];
    func_8009EEAC(setup_arg_0, setup_arg_1, setup_arg_2, setup_arg_3);
    marker_count = 0;
    while ((node = *(u8 **)(node + 0x5C) + 0x20) != D_800E3D7C[0]) {
        if (*(s8 *)(node + 0x13) > 0) {
            owner = *(u8 **)(node - 0x14);
            func_8009F3D4(owner[0x24], owner[0x25], 0x202080, 4,
                          marker_count++);
        }
    }
}
