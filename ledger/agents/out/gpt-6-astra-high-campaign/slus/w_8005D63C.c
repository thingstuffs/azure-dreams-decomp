#include "common.h"

/* Table lookup with optional shift: reads a u16 from D_80079958.ptr[a0]; if a1==-1
 * returns it unshifted, otherwise left-shifts it by the global D_80079980[0]. */
typedef struct {
    u16 *ptr;
    u32 pad2[2]; /* keep total size > 8 bytes so hi/lo addressing (not gp_rel) is used */
} D_80079958_t_8005D63C;

extern D_80079958_t_8005D63C D_80079958;

extern s32 D_80079980[3]; /* index 0 only used; array padding forces hi/lo codegen */

/* Read a table value and apply the global left shift unless shift mode is -1. */
s32 func_8005D63C(s32 index, s32 shift_mode)
{
    u16 value = D_80079958.ptr[index];

    if (shift_mode == -1) {
        return (s32)value;
    }
    return (s32)value << D_80079980[0];
}
