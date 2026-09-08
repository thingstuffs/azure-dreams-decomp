#include "common.h"
#include "m2c_compat.h"

typedef struct S_80702110_0 {
    u8 pad_00[0x1DFE];
    u16 unk_1DFE;
} S_80702110_0;   /* (D_80700000 + (arg0 * 4)) in func_80702110 */
s32 func_80702714();                             /* extern */
extern u8 D_80700000[8];

/* Skips entries accepted by func_80702714 and checks whether the next entry is zero. */
s32 func_80702110(s32 list_index) {
    s16 *entry;

    entry = (*(s16 **)((u8 *)((D_80700000 + (((S_80702110_0 *)((D_80700000 + (list_index * 4))))->unk_1DFE * 4))) + 0x1DEC));
    while (func_80702714(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
