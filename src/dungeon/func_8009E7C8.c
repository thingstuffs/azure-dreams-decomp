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
    s32 lookup_id;
    s32 found_id;
    s32 target_x;
    void *current;
    u8 *entry_data;
    s32 distance;
    s32 radius;
    s32 target_y;

    found_id = func_8009FB34((u16)x, (u16)y);
    current = (u8 *)((S_800A3F28_0 *)owner)->unk_5C + 0x20;
    if (current != end) {
        lookup_id = (s16)found_id;
        target_x = (s16)x;
        radius = 1;
        target_y = (s16)y;
        do {
            if ((func_800A41F0(current) << 16) != 0) {
                entry_data = ((S_800A3F28_0_pre *)current)[-1].unk_00;
                if (lookup_id == ((S_800A3F28_1 *)entry_data)->unk_26 && lookup_id >= 0) {
                    return current;
                }
                distance = target_x - ((S_800A3F28_1 *)entry_data)->unk_24;
                if (distance < 0) {
                    distance = -distance;
                }
                if (radius >= distance) {
                    distance = target_y - ((S_800A3F28_1 *)entry_data)->unk_25;
                    if (distance < 0) {
                        distance = -distance;
                    }
                    if (radius >= distance) {
                        return current;
                    }
                }
            }
            current = (u8 *)((S_800A3F28_0 *)current)->unk_5C + 0x20;
        } while (current != end);
    }
    return NULL;
}
