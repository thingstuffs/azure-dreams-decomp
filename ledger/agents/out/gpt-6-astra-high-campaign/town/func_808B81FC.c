#include "common.h"

extern s32 D_00003F50[];
extern s32 D_00003FCC[];
extern s32 D_000045F8[];

extern s32 func_80003544(s32 arg0);
extern s32 func_800036D8(s32 arg0, s32 arg1);

/* Return the selected table value plus the global offset after mode-three calls. */
s32 func_808B81FC(void) {
    s32 entry_index;
    s32 entry_value;

    entry_index = D_00003F50[0];
    entry_value = D_00003FCC[entry_index * 8];
    func_800036D8(entry_index, 3);
    func_80003544(3);
    return entry_value + D_000045F8[0];
}

/* MECHANISM: Named overlay globals force the retail hi/lo address forms.
   The table is word-indexed by index*8, emitting the byte stride sll 5.
   Holding the table value across both calls naturally allocates only s0. */
