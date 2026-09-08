#include "common.h"

/* D_80079958 is a struct whose first field is a u16* table pointer; padded
 * so its total size exceeds 8 bytes and forces %hi/%lo (not gp_rel) addressing,
 * matching sibling func_8005D63C's view of the same global. */
typedef struct {
    volatile u16 *ptr;
    u32 pad2[2];
} D_80079958_t_8005D550;

extern D_80079958_t_8005D550 D_80079958;
extern s32 D_80079980[3]; /* index 0 only used; array padding forces hi/lo codegen */

/* Store a table entry, optionally shifting the value right by the global shift amount. */
void storeU16TableEntry(s32 index, u32 value, s32 apply_shift)
{
    if (apply_shift == 0) {
        D_80079958.ptr[index] = (u16)value;
    } else {
        D_80079958.ptr[index] = (u16)(value >> D_80079980[0]);
    }
}
