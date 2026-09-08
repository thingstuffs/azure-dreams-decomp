#include "common.h"

/* D_80083D08: array of 6 8-byte elements (see src/code2.c D8Elem: two shorts unk0/unk2 form
 * the first 4-byte word this function tests). Declared >8 bytes total to force hi/lo
 * addressing on the base, matching the target's lui/addiu access pattern. */
typedef struct {
    s32 unk0; /* covers D8Elem.unk0/unk2 (two shorts) as a combined 32-bit test-for-zero */
    s32 unk4; /* covers D8Elem.flags4/id6 */
} S_80047B80;

extern S_80047B80 D_80083D08[6];

/* Returns the first free slot index in D_80083D08, or -1 if all slots are occupied. */
s32 func_80047B80(void)
{
    s32 free_index = -1;
    s32 slot_index = 0;
    S_80047B80 *slot = D_80083D08;

    for (; slot_index < 6; slot_index++, slot++) {
        if (slot->unk0 == 0) {
            free_index = slot_index;
            break;
        }
    }
    return free_index;
}
