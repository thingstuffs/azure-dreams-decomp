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

/* Store a value into the table D_80079958.ptr[a0]; if a2 is nonzero, the
 * stored value is first logically shifted right by the global shift amount
 * D_80079980[0]. */
void storeU16TableEntry(s32 a0, u32 a1, s32 a2)
{
    if (a2 == 0) {
        D_80079958.ptr[a0] = (u16)a1;
    } else {
        D_80079958.ptr[a0] = (u16)(a1 >> D_80079980[0]);
    }
}
