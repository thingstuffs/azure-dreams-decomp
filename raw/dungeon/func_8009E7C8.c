#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8009FB34(u16, u16);
extern s32 func_800A41F0(void *);

void *func_800A3F28(s32 x, s32 y, void *end, void *owner)
{
    register s32 x_hold ASM_REG("$18");
    register s32 y_hold ASM_REG("$19");
    register void *end_hold ASM_REG("$21");
    register void *current ASM_REG("$16");
    register s32 lookup ASM_REG("$17");
    register s32 x_coord ASM_REG("$20");
    register s32 shifted ASM_REG("$2");
    register u8 *data ASM_REG("$3");
    s32 dx;
    s32 dy;

    x_hold = x;
    ASM_KEEP_NV(x_hold);
    y_hold = y;
    ASM_KEEP_NV(y_hold);
    end_hold = end;
    ASM_KEEP_NV(end_hold);
    current = owner;
    ASM_KEEP_NV(current);
    shifted = func_8009FB34((u16)x_hold, (u16)y_hold);
    ASM_KEEP_NV(shifted);
    data = (u8 *)FIELD(current, s32, 0x5C);
    ASM_KEEP_NV(data);
    current = data + 0x20;
    if (current == end_hold) {
        goto not_found;
    }

    lookup = (s16)shifted;
    ASM_KEEP_NV(lookup);
    shifted = x_hold << 16;
    x_coord = shifted >> 16;
    ASM_KEEP_NV(x_coord);
    x_hold = 1;
    shifted = y_hold << 16;
    y_hold = shifted >> 16;
loop:
    if ((func_800A41F0(current) << 16) != 0) {
        data = FIELD(current, u8 *, -0x14);
        if (lookup == FIELD(data, s8, 0x26)) {
            if (lookup >= 0) {
                return current;
            }
        }

        dx = x_coord - FIELD(data, u8, 0x24);
        if (dx < 0) {
            dx = -dx;
        }
        if (x_hold < dx) {
            goto next;
        }

        dy = y_hold - FIELD(data, u8, 0x25);
        if (dy < 0) {
            dy = -dy;
        }
        if (x_hold < dy) {
            goto next;
        }
        return current;
    }

next:
    shifted = FIELD(current, s32, 0x5C);
    current = (void *)(shifted + 0x20);
    if (current != end_hold) {
        goto loop;
    }

not_found:
    return NULL;
}

/* MECHANISM: The call result stays in v0 across the list-head load; owner then
   becomes current in s0, while held coordinates/sentinel fill s2-s5 exactly.
   Hoisted sign conversions reuse x's live range for radius; direct returns
   merge to retail's epilogue and leave v0 free for the second delta chain. */
