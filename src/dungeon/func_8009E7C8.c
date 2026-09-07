#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A3F28_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800A3F28_0_pre;   /* the 0x14 bytes before current in func_800A3F28, addressed as current[-1] */

typedef struct S_800A3F28_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800A3F28_0;   /* current in func_800A3F28 */

typedef struct S_800A3F28_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3F28_1;   /* data in func_800A3F28 */



extern s32 func_8009FB34(u16, u16);
extern s32 func_800A41F0(void *);

void *func_800A3F28(s32 x, s32 y, void *end, void *owner)
{
    s32 x_hold;
    s32 y_hold;
    void *end_hold;
    void *current;
    register s32 lookup ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 x_coord;
    register s32 shifted ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *data;
    s32 dx;
    s32 dy;

    x_hold = x;
    ASM_KEEP_NV(x_hold);   /* MATCH pin: keeps a statement from moving across a call/branch */
    y_hold = y;
    end_hold = end;
    current = owner;
    shifted = func_8009FB34((u16)x_hold, (u16)y_hold);
    data = (u8 *)((S_800A3F28_0 *)current)->unk_5C;
    current = data + 0x20;
    if (current == end_hold) {
        goto not_found;
    }

    lookup = (s16)shifted;
    shifted = x_hold << 16;
    x_coord = shifted >> 16;
    x_hold = 1;
    shifted = y_hold << 16;
    y_hold = shifted >> 16;
loop:
    if ((func_800A41F0(current) << 16) != 0) {
        data = ((S_800A3F28_0_pre *)current)[-1].unk_00;
        if (lookup == ((S_800A3F28_1 *)data)->unk_26) {
            if (lookup >= 0) {
                return current;
            }
        }

        dx = x_coord - ((S_800A3F28_1 *)data)->unk_24;
        if (dx < 0) {
            dx = -dx;
        }
        if (x_hold < dx) {
            goto next;
        }

        dy = y_hold - ((S_800A3F28_1 *)data)->unk_25;
        if (dy < 0) {
            dy = -dy;
        }
        if (x_hold < dy) {
            goto next;
        }
        return current;
    }

next:
    shifted = ((S_800A3F28_0 *)current)->unk_5C;
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
