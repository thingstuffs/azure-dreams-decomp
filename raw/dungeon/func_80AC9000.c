#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_8009C93C();

void func_80174800(void *arg0, s32 arg1, s32 arg2, s16 arg3)
{
    register s32 match_x ASM_REG("$22") = arg1;
    register s32 match_y ASM_REG("$21") = arg2;
    void *head = arg0;
    void *actor = head;
    void *owner;

    arg0 = (u8 *)FIELD(head, void *, 0x5C) + 0x20;
    owner = FIELD(head, void *, -0x14);
    while (arg0 != head) {
        void *tile = FIELD(arg0, void *, -0x14);
        void *data = FIELD(arg0, void *, -0x18);
        s16 height;

        if ((FIELD(tile, u8, 0x24) == (match_x & 0xFFFF)) &&
            (FIELD(tile, u8, 0x25) == (match_y & 0xFFFF)) &&
            (height = FIELD(data, s16, 0xA), height <= arg3 + 0x38) &&
            (height > arg3 - 0x38) &&
            ((u32)(FIELD(arg0, u8, 0x13) - 0x33) >= 4U)) {
            FIELD(actor, s8, 0x84) = 0x7C;
            FIELD(actor, s8, 0x85) =
                (s8)((s32)(FIELD(actor, u8, 0x26) * 3) >> 1);
            func_8009C93C(actor, owner,
                          FIELD(actor, s16, 0x2A), 1, 0);
            }
        arg0 = (u8 *)FIELD(arg0, void *, 0x5C) + 0x20;
    }
}
