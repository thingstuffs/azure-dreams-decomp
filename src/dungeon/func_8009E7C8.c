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

/* Finds the first eligible entry with a matching nonnegative lookup ID or within one tile of (x, y). */
void *func_800A3F28(s32 x, s32 y, void *end, void *owner)
{
    s32 x_or_radius;
    s32 target_y;
    void *sentinel;
    void *current;
    register s32 lookup_id ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 target_x;
    register s32 scratch ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *entry_data;
    s32 distance_x;
    s32 distance_y;

    x_or_radius = x;
       /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    target_y = y;
    sentinel = end;
    current = owner;
    scratch = func_8009FB34((u16)x_or_radius, (u16)target_y);
    entry_data = (u8 *)((S_800A3F28_0 *)current)->unk_5C;
    current = entry_data + 0x20;
    if (current == sentinel) {
        goto not_found;
    }

    lookup_id = (s16)scratch;
    scratch = x_or_radius << 16;
    target_x = scratch >> 16;
    x_or_radius = 1;
    scratch = target_y << 16;
    target_y = scratch >> 16;
loop:
    if ((func_800A41F0(current) << 16) != 0) {
        entry_data = ((S_800A3F28_0_pre *)current)[-1].unk_00;
        if (lookup_id == ((S_800A3F28_1 *)entry_data)->unk_26) {
            if (lookup_id >= 0) {
                return current;
            }
        }

        distance_x = target_x - ((S_800A3F28_1 *)entry_data)->unk_24;
        if (distance_x < 0) {
            distance_x = -distance_x;
        }
        if (x_or_radius < distance_x) {
            goto next;
        }

        distance_y = target_y - ((S_800A3F28_1 *)entry_data)->unk_25;
        if (distance_y < 0) {
            distance_y = -distance_y;
        }
        if (x_or_radius < distance_y) {
            goto next;
        }
        return current;
    }

next:
    scratch = ((S_800A3F28_0 *)current)->unk_5C;
    current = (void *)(scratch + 0x20);
    if (current != sentinel) {
        goto loop;
    }

not_found:
    return NULL;
}
