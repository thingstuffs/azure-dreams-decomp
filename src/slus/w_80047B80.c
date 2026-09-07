#include "common.h"

/* D_80083D08: array of 6 8-byte elements (see src/code2.c D8Elem: two shorts unk0/unk2 form
 * the first 4-byte word this function tests). Declared >8 bytes total to force hi/lo
 * addressing on the base, matching the target's lui/addiu access pattern. */
typedef struct {
    s32 unk0; /* covers D8Elem.unk0/unk2 (two shorts) as a combined 32-bit test-for-zero */
    s32 unk4; /* covers D8Elem.flags4/id6 */
} S_80047B80;

extern S_80047B80 D_80083D08[6];

/* Returns the index of the first D_80083D08 slot whose first word is 0 (free slot), or -1 if none free. */
s32 func_80047B80(void)
{
    s32 result = -1;
    s32 i = 0;
    S_80047B80 *p = D_80083D08;

    for (; i < 6; i++, p++) {
        if (p->unk0 == 0) {
            result = i;
            break;
        }
    }
    return result;
}
